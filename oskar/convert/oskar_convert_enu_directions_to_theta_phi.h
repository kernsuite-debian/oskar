/*
 * Copyright (c) 2014, The University of Oxford
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

#ifndef OSKAR_CONVERT_ENU_DIRECTIONS_TO_THETA_PHI_H_
#define OSKAR_CONVERT_ENU_DIRECTIONS_TO_THETA_PHI_H_

/**
 * @file oskar_convert_enu_directions_to_theta_phi.h
 */

#include <oskar_global.h>
#include <mem/oskar_mem.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 * Function to compute theta and phi angles from horizontal direction
 * cosines (single precision).
 *
 * @details
 * Computes the angles theta and phi from the given horizontal direction
 * cosines.
 *
 * The directions are:
 * - x: pointing East,
 * - y: pointing North,
 * - z: pointing to the zenith.
 *
 * Theta is the polar angle from the z-axis to the xy-plane, and phi is the
 * azimuthal angle from the x-axis to the y-axis.
 *
 * @param[in]  num_points  The number of points.
 * @param[in]  x           The x-direction-cosines.
 * @param[in]  y           The y-direction-cosines.
 * @param[in]  z           The z-direction-cosines.
 * @param[in]  delta_phi   Angle to add to computed values of phi.
 * @param[out] theta       The theta angles, in radians.
 * @param[out] phi         The phi angles, in radians.
 */
OSKAR_EXPORT
void oskar_convert_enu_directions_to_theta_phi_f(
        const int num_points, const float* x, const float* y,
        const float* z, const float delta_phi, float* theta, float* phi);

/**
 * @brief
 * Function to compute azimuth and elevation from horizontal direction
 * cosines (double precision).
 *
 * @details
 * Computes the angles theta and phi from the given horizontal direction
 * cosines.
 *
 * The directions are:
 * - x: pointing East,
 * - y: pointing North,
 * - z: pointing to the zenith.
 *
 * Theta is the polar angle from the z-axis to the xy-plane, and phi is the
 * azimuthal angle from the x-axis to the y-axis.
 *
 * @param[in]  num_points  The number of points.
 * @param[in]  x           The x-direction-cosines.
 * @param[in]  y           The y-direction-cosines.
 * @param[in]  z           The z-direction-cosines.
 * @param[in]  delta_phi   Angle to add to computed values of phi.
 * @param[out] theta       The theta angles, in radians.
 * @param[out] phi         The phi angles, in radians.
 */
OSKAR_EXPORT
void oskar_convert_enu_directions_to_theta_phi_d(
        const int num_points, const double* x, const double* y,
        const double* z, const double delta_phi, double* theta, double* phi);

/**
 * @brief
 * Wrapper function to compute azimuth and elevation from horizontal direction
 * cosines.
 *
 * @details
 * Computes the angles theta and phi from the given horizontal direction
 * cosines.
 *
 * The directions are:
 * - x: pointing East,
 * - y: pointing North,
 * - z: pointing to the zenith.
 *
 * Theta is the polar angle from the z-axis to the xy-plane, and phi is the
 * azimuthal angle from the x-axis to the y-axis.
 *
 * @param[in]  num_points  The number of points.
 * @param[in]  x           The x-direction-cosines.
 * @param[in]  y           The y-direction-cosines.
 * @param[in]  z           The z-direction-cosines.
 * @param[in]  delta_phi   Angle to add to computed values of phi.
 * @param[out] theta       The theta angles, in radians.
 * @param[out] phi         The phi angles, in radians.
 * @param[in,out] status   Status return code.
 */
OSKAR_EXPORT
void oskar_convert_enu_directions_to_theta_phi(int num_points,
        const oskar_Mem* x, const oskar_Mem* y, const oskar_Mem* z,
        double delta_phi, oskar_Mem* theta, oskar_Mem* phi, int* status);

#ifdef __cplusplus
}
#endif

#endif /* OSKAR_CONVERT_ENU_DIRECTIONS_TO_THETA_PHI_H_ */
