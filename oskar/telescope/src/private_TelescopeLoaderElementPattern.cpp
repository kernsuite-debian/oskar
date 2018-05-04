/*
 * Copyright (c) 2013-2016, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "telescope/private_TelescopeLoaderElementPattern.h"
#include "utility/oskar_dir.h"
#include "utility/oskar_file_exists.h"

#include <sstream>
#include <cstring>

using std::vector;
using std::map;
using std::string;

static const string root_name("element_pattern");

TelescopeLoaderElementPattern::TelescopeLoaderElementPattern()
{
    telescope_ = 0;
    wildcard = root_name + "*";
    fit_root_x = root_name + "_fit_x_";
    fit_root_y = root_name + "_fit_y_";
    fit_root_scalar = root_name + "_fit_scalar_";
    root_x = root_name + "_x_";
    root_y = root_name + "_y_";
}

TelescopeLoaderElementPattern::~TelescopeLoaderElementPattern()
{
}

void TelescopeLoaderElementPattern::load(oskar_Telescope* telescope,
        const string& cwd, int num_subdirs, map<string, string>& filemap,
        int* status)
{
    telescope_ = telescope;
    update_map(filemap, cwd);

    // Load element pattern data for stations only at the deepest level!
    if (num_subdirs == 0)
    {
        int num_stations = oskar_telescope_num_stations(telescope);
        for (int i = 0; i < num_stations; ++i)
        {
            oskar_Station* s = oskar_telescope_station(telescope, i);
            oskar_station_resize_element_types(s, 1, status);
            load_element_patterns(s, filemap, status);
        }
    }
}

void TelescopeLoaderElementPattern::load(oskar_Station* station,
        const string& cwd, int num_subdirs, int /*depth*/,
        map<string, string>& filemap, int* status)
{
    update_map(filemap, cwd);

    // Load element pattern data for stations only at the deepest level!
    if (num_subdirs == 0)
    {
        oskar_station_resize_element_types(station, 1, status);
        load_element_patterns(station, filemap, status);
    }
}

string TelescopeLoaderElementPattern::name() const
{
    return string("element pattern loader");
}

void TelescopeLoaderElementPattern::load_element_patterns(
        oskar_Station* station, const map<string, string>& filemap, int* status)
{
    // Check if safe to proceed.
    if (*status) return;

    // FIXME(FD) Return if element patterns are disabled.
    if (!oskar_telescope_enable_numerical_patterns(telescope_))
        return;

    // Get lists of all paths in the map that have keys starting with the
    // right root name.
    vector<string> keys_fit_x, keys_fit_y, keys_fit_scalar;
    vector<string> paths_fit_x, paths_fit_y, paths_fit_scalar;
    vector<string> keys_x, keys_y, paths_x, paths_y;
    for (map<string, string>::const_iterator i = filemap.begin();
            i != filemap.end(); ++i)
    {
        string key = i->first;
        if (key.compare(0, fit_root_x.size(), fit_root_x) == 0)
        {
            keys_fit_x.push_back(key);
            paths_fit_x.push_back(i->second);
        }
        else if (key.compare(0, fit_root_y.size(), fit_root_y) == 0)
        {
            keys_fit_y.push_back(key);
            paths_fit_y.push_back(i->second);
        }
        else if (key.compare(0, fit_root_scalar.size(), fit_root_scalar) == 0)
        {
            keys_fit_scalar.push_back(key);
            paths_fit_scalar.push_back(i->second);
        }
        else if (key.compare(0, root_x.size(), root_x) == 0)
        {
            keys_x.push_back(key);
            paths_x.push_back(i->second);
        }
        else if (key.compare(0, root_y.size(), root_y) == 0)
        {
            keys_y.push_back(key);
            paths_y.push_back(i->second);
        }

        // Check against bare root name last: extended root names will have
        // been caught first, and in those cases we won't get here due to
        // all the else clauses.
        else if (key.compare(0, root_name.size(), root_name) == 0)
        {
            // Use same parameters for both X and Y.
            keys_x.push_back(key);
            keys_y.push_back(key);
            paths_x.push_back(i->second);
            paths_y.push_back(i->second);
        }
    }

    // Load fitted X, Y or scalar data.
    if (oskar_telescope_pol_mode(telescope_) == OSKAR_POL_MODE_FULL)
    {
        load_fitted_data(1, station, keys_fit_x, paths_fit_x, status);
        load_fitted_data(2, station, keys_fit_y, paths_fit_y, status);
    }
    else
        load_fitted_data(0, station, keys_fit_scalar, paths_fit_scalar, status);

    // Load functional data.
    load_functional_data(1, station, keys_x, paths_x, status);
    load_functional_data(2, station, keys_y, paths_y, status);
}

void TelescopeLoaderElementPattern::load_fitted_data(int port,
        oskar_Station* station, const vector<string>& keys,
        const vector<string>& paths, int* status)
{
    size_t buflen = 0;
    char* buffer = 0;
    if (*status) return;
    for (size_t i = 0; i < keys.size(); ++i)
    {
        int ind = 0;
        double freq = 0.0;
        string key = keys[i];
        string path = paths[i];

        // Get the element index and frequency from the key.
        parse_filename(key.c_str(), &buffer, &buflen, &ind, &freq);

        // Load the file.
        if (*status) break;
        if (oskar_station_num_element_types(station) < ind + 1)
            oskar_station_resize_element_types(station, ind + 1, status);
        oskar_element_read(oskar_station_element(station, ind), path.c_str(),
                port, freq, status);
    }
    free(buffer);
}

void TelescopeLoaderElementPattern::load_functional_data(int port,
        oskar_Station* station, const vector<string>& keys,
        const vector<string>& paths, int* status)
{
    size_t buflen = 0;
    char* buffer = 0;
    if (*status) return;
    for (size_t i = 0; i < keys.size(); ++i)
    {
        int ind = 0;
        string key = keys[i];
        string path = paths[i];

        // Get the element index from the key.
        parse_filename(key.c_str(), &buffer, &buflen, &ind, 0);

        // Load the file.
        if (*status) break;
        if (oskar_station_num_element_types(station) < ind + 1)
            oskar_station_resize_element_types(station, ind + 1, status);
        oskar_element_load(oskar_station_element(station, ind), path.c_str(),
                port == 1 ? 1 : 0, status);
    }
    free(buffer);
}

void TelescopeLoaderElementPattern::parse_filename(const char* s,
        char** buffer, size_t* buflen, int* index, double* freq)
{
    size_t i = 0, j = 1, length = 0;
    char* p;
    *index = 0;
    if (freq) *freq = 0.0;

    // Ensure buffer is big enough to make a copy of the input string.
    length = 1 + strlen(s);
    if (*buflen < length)
    {
        *buffer = (char*) realloc((void*)(*buffer), length);
        if (!*buffer) return;
        *buflen = length;
    }
    strcpy(*buffer, s);

    // Replace underscores with NULL and find out how many words there are.
    for (i = 0; i < length; ++i)
    {
        if ((*buffer)[i] == '_')
        {
            (*buffer)[i] = 0;
            j++;
        }
    }

    // Extract index and frequency as the first two numbers.
    // The frequency need not exist.
    p = *buffer;
    for (i = 0; i < j; ++i)
    {
        length = 1 + strlen(p);
        if (sscanf(p, "%d", index))
        {
            if ((i + 1 < j) && freq)
            {
                p += length;
                sscanf(p, "%lf", freq);
                *freq *= 1e6; // Convert from MHz to Hz.
            }
            return;
        }
        p += length;
    }
}

void TelescopeLoaderElementPattern::update_map(
        map<string, string>& filemap, const string& cwd)
{
    // Update the map of element files for the current directory.
    // The presence of fitted coefficients is sufficient to override ones
    // from a higher level.

    // Get a listing of the files in the current directory that start with
    // the fitted element data root name.
    // Store the full paths to these files in the persistent map, with the
    // local filename as the key.
    int num_items = 0;
    char** items = 0;
    oskar_dir_items(cwd.c_str(), wildcard.c_str(), 1, 0, &num_items, &items);
    for (int i = 0; i < num_items; ++i)
    {
        filemap[items[i]] = get_path(cwd, string(items[i]));
        free(items[i]);
    }
    free(items);
}
