/*
 * Copyright (c) 2015, The University of Oxford
 * All rights reserved.
 *
 * This file is part of the OSKAR package.
 * Contact: oskar at oerc.ox.ac.uk
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

#include "settings/oskar_settings_utility_string.h"
#include "settings/types/oskar_DoubleRangeExt.h"
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
using ttl::var::get;

namespace oskar {

enum value_types { DOUBLE, STRING };

bool compare(const DoubleRangeExt::Value& a, const DoubleRangeExt::Value& b)
{
    if (a.is_singular() || b.is_singular()) return false;
    if (a.which() != b.which()) return false;
    if (a.which() == DOUBLE)
        return (fabs(get<double>(a) - get<double>(b)) < DBL_MIN);
    if (a.which() == STRING)
        return get<string>(a) == get<string>(b);
    return false;
}

DoubleRangeExt::DoubleRangeExt()
{
    (void) init("");
}

DoubleRangeExt::~DoubleRangeExt()
{
}

bool DoubleRangeExt::init(const char* s)
{
    // Reset the value.
    ext_min_.clear();
    ext_max_.clear();
    value_ = 0.0;
    default_ = 0.0;
    str_default_ = "0.0";
    str_value_ = "0.0";

    // Extract range from the parameter CSV string.
    // Parameters, p, for DoubleRangeExt should be length 3 or 4.
    //  - With 3 entries the range is (p[0] to p[1]) with an extended minimum
    //    value of p[2]
    //  - With 4 entries the range is (p[0] to p[1]) with an extended minimum
    //    value of p[2] and an extended maximum value of p[3]
    //  - For the double range parameters, p[0] and p[1], special values
    //    of 'MIN' and 'MAX' map to -DBL_MAX and DBL_MIN respectively.
    bool ok = true;
    vector<string> p = oskar_settings_utility_string_get_type_params(s);
    if (p.size() < 3u || p.size() > 4u) return false;
    if (p[0] == "-DBL_MAX" || p[0] == "-MAX")
        min_ = -DBL_MAX;
    else if (p[0] == "DBL_MIN" || p[0] == "-DBL_MIN"
                    || p[0] == "MIN" || p[0] == "-MIN")
        min_ = -DBL_MIN;
    else
        min_ = oskar_settings_utility_string_to_double(p[0], &ok);
    if (!ok) return false;
    if (p[1] == "DBL_MAX" || p[1] == "MAX")
        max_ =  DBL_MAX;
    else
        max_ = oskar_settings_utility_string_to_double(p[1], &ok);
    ext_min_ = p[2];
    if (p.size() == 4u) {
        ext_max_ = p[3];
    }
    return ok;
}

bool DoubleRangeExt::set_default(const char* value)
{
    string v(value);
    bool ok = from_string_(default_, v);
    if (default_.which() == DOUBLE)
        format_ = (v.find_first_of('e') != string::npos) ? EXPONENT : AUTO;
    str_default_ = to_string_(default_);
    if (ok)
        set_value(value);
    return ok;
}

bool DoubleRangeExt::set_value(const char* value)
{
    string v(value);
    bool ok = from_string_(value_, v);
    if (value_.which() == DOUBLE)
        format_ = (v.find_first_of('e') != string::npos) ? EXPONENT : AUTO;
    str_value_ = to_string_(value_);
    return ok;
}

bool DoubleRangeExt::is_default() const
{
    return compare(value_, default_);
}

double DoubleRangeExt::value() const
{
    if (value_.which() == STRING && get<string>(value_) == ext_max_)
        return max_;
    if (value_.which() == STRING && get<string>(value_) == ext_min_)
        return min_;
    return get<double>(value_);
}

double DoubleRangeExt::min() const
{
    return min_;
}

double DoubleRangeExt::max() const
{
    return max_;
}

const char* DoubleRangeExt::ext_min() const
{
    return ext_min_.c_str();
}

const char* DoubleRangeExt::ext_max() const
{
    return ext_max_.c_str();
}

bool DoubleRangeExt::operator==(const DoubleRangeExt& other) const
{
    return compare(value_, other.value_);
}

bool DoubleRangeExt::operator>(const DoubleRangeExt& other) const
{
    if (value_.is_singular() || other.value_.is_singular()) return false;
    if (value_.which() != other.value_.which()) return false;
    if (value_.which() == DOUBLE)
        return get<double>(value_) > get<double>(other.value_);
    return false;
}

bool DoubleRangeExt::from_string_(Value& value, const string& s) const
{
    if (s.empty()) return false;

    if (s == ext_min_)
        value = ext_min_;
    else if (s == ext_max_)
        value = ext_max_;
    else {
        bool ok = true;
        double v = oskar_settings_utility_string_to_double(s, &ok);
        if (!ok) return false;
        if (v < min_ && !ext_min_.empty())
            value = ext_min_;
        else if (v > max_ && !ext_max_.empty())
            value = ext_max_;
        else {
            if (v >= max_) value = max_;
            else if (v <= min_) value = min_;
            else value = v;
        }
    }
    return true;
}

string DoubleRangeExt::to_string_(const Value& value) const
{
    if (value.is_singular()) return string();
    if (value.which() == DOUBLE) {
        double v = get<double>(value);
        int n = 16;
        if (v != 0.0 && v > 1.0) {
            n -= (floor(log10(v)) + 1);
        }
        string s = oskar_settings_utility_double_to_string_2(v,
                format_ == AUTO ? 'g' : 'e');
        return s;
    }
    else if (value.which() == STRING) {
        return get<string>(value);
    }
    return string();
}

} // namespace oskar
