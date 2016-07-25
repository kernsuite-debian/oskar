/*
 * Copyright (c) 2012-2014, The University of Oxford
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

#ifndef OSKAR_SETTINGS_OBSERVATION_H_
#define OSKAR_SETTINGS_OBSERVATION_H_

/**
 * @file oskar_SettingsObservation.h
 */

/**
 * @struct oskar_SettingsObservation
 *
 * @brief Structure to hold observation settings.
 *
 * @details
 * The structure holds observation parameters.
 */
struct oskar_SettingsObservation
{
    int num_pointing_levels;
    int phase_centre_coord_type;
    double* phase_centre_lon_rad;
    double* phase_centre_lat_rad;
    char* pointing_file;

    double start_frequency_hz;
    int num_channels;
    double frequency_inc_hz;

    int    num_time_steps;
    double start_mjd_utc;
    double length_sec;
    double length_days;
    double dt_dump_days;

    /* Advanced parameters. */
    double delta_tai_utc_sec;
    double delta_ut1_utc_sec;
    double pm_x_arcsec;
    double pm_y_arcsec;
};
typedef struct oskar_SettingsObservation oskar_SettingsObservation;

#endif /* OSKAR_SETTINGS_OBSERVATION_H_ */