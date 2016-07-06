/*
 * Copyright (c) 2013-2014, The University of Oxford
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

#ifndef OSKAR_CONVERT_ECEF_TO_GEODETIC_SPHERICAL_H_
#define OSKAR_CONVERT_ECEF_TO_GEODETIC_SPHERICAL_H_

/**
 * @file oskar_convert_ecef_to_geodetic_spherical.h
 */

#include <oskar_global.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 * Convert coordinates from a geocentric cartesian (ECEF) to geodetic spherical
 * system (single precision).
 *
 * @details
 * This function converts positions from the geocentric cartesian
 * (Earth-Centred-Earth-Fixed, or ECEF) to the geodetic spherical (longitude,
 * latitude, altitude above ellipsoid) system.
 *
 * WARNING: This function uses reduced floating-point precision!
 * Use the double-precision version of this function in preference.
 *
 * The function uses WGS84 ellipsoid parameters:
 * Equatorial radius: 6378137 metres.
 * Polar radius: 6356752.314 metres.
 *
 * The input coordinates are with respect to the origin at the centre of the
 * Earth, and have the x-axis pointing towards the meridian of zero longitude,
 * the y-axis to +90 degrees East, and the z-axis to the North Celestial Pole.
 *
 * The algorithm is from H. Vermeille (2002): Journal of Geodesy, 76, 451.
 * DOI 10.1007/s00190-002-0273-6
 *
 * @param[in]  num_points Number of points.
 * @param[in]  x       Vector of ECEF x-positions, in metres.
 * @param[in]  y       Vector of ECEF y-positions, in metres.
 * @param[in]  z       Vector of ECEF z-positions, in metres.
 * @param[out] lon_rad Vector of longitudes, in radians.
 * @param[out] lat_rad Vector of latitudes, in radians.
 * @param[out] alt_m   Vector of altitudes above ellipsoid, in metres.
 */
OSKAR_EXPORT
void oskar_convert_ecef_to_geodetic_spherical_f(int num_points,
        const float* x, const float* y, const float* z,
        float* lon_rad, float* lat_rad, float* alt_m);

/**
 * @brief
 * Convert coordinates from a geocentric cartesian (ECEF) to geodetic spherical
 * system (double precision).
 *
 * @details
 * This function converts positions from the geocentric cartesian
 * (Earth-Centred-Earth-Fixed, or ECEF) to the geodetic spherical (longitude,
 * latitude, altitude above ellipsoid) system.
 *
 * The function uses WGS84 ellipsoid parameters:
 * Equatorial radius: 6378137 metres.
 * Polar radius: 6356752.314 metres.
 *
 * The input coordinates are with respect to the origin at the centre of the
 * Earth, and have the x-axis pointing towards the meridian of zero longitude,
 * the y-axis to +90 degrees East, and the z-axis to the North Celestial Pole.
 *
 * The algorithm is from H. Vermeille (2002): Journal of Geodesy, 76, 451.
 * DOI 10.1007/s00190-002-0273-6
 *
 * @param[in]  num_points Number of points.
 * @param[in]  x          Vector of ECEF x-positions, in metres.
 * @param[in]  y          Vector of ECEF y-positions, in metres.
 * @param[in]  z          Vector of ECEF z-positions, in metres.
 * @param[out] lon_rad    Vector of longitudes, in radians.
 * @param[out] lat_rad    Vector of latitudes, in radians.
 * @param[out] alt_m      Vector of altitudes above ellipsoid, in metres.
 */
OSKAR_EXPORT
void oskar_convert_ecef_to_geodetic_spherical(int num_points,
        const double* x, const double* y, const double* z,
        double* lon_rad, double* lat_rad, double* alt_m);

#ifdef __cplusplus
}
#endif

#endif /* OSKAR_CONVERT_ECEF_TO_GEODETIC_SPHERICAL_H_ */
