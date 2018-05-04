/*
 * Copyright (c) 2012-2013, The University of Oxford
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

#ifndef OSKAR_APPLY_ELEMENT_TAPER_GAUSSIAN_H_
#define OSKAR_APPLY_ELEMENT_TAPER_GAUSSIAN_H_

/**
 * @file oskar_apply_element_taper_gaussian.h
 */

#include <oskar_global.h>
#include <mem/oskar_mem.h>
#include <utility/oskar_vector_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 * Function to apply a Gaussian taper to the scalar element response
 * (single precision).
 *
 * @details
 * This function multiplies the scalar response of the element by a
 * Gaussian taper. The multiplication is performed in-place.
 *
 * @param[in,out] jones    Array of Jones scalars.
 * @param[in] num_sources  Number of source positions.
 * @param[in] fwhm         Full-width half-max of Gaussian, in radians.
 * @param[in] theta        Array of source theta values, in radians.
 */
OSKAR_EXPORT
void oskar_apply_element_taper_gaussian_scalar_f(float2* jones,
        const int num_sources, const float fwhm, const float* theta);

/**
 * @brief
 * Function to apply a Gaussian taper to the matrix element response
 * (single precision).
 *
 * @details
 * This function multiplies the matrix response of the element by a
 * Gaussian taper. The multiplication is performed in-place.
 *
 * @param[in,out] jones    Array of Jones matrices.
 * @param[in] num_sources  Number of source positions.
 * @param[in] fwhm         Full-width half-max of Gaussian, in radians.
 * @param[in] theta        Array of source theta values, in radians.
 */
OSKAR_EXPORT
void oskar_apply_element_taper_gaussian_matrix_f(float4c* jones,
        const int num_sources, const float fwhm, const float* theta);

/**
 * @brief
 * Function to apply a Gaussian taper to the scalar element response
 * (double precision).
 *
 * @details
 * This function multiplies the scalar response of the element by a
 * Gaussian taper. The multiplication is performed in-place.
 *
 * @param[in,out] jones    Array of Jones scalars.
 * @param[in] num_sources  Number of source positions.
 * @param[in] fwhm         Full-width half-max of Gaussian, in radians.
 * @param[in] theta        Array of source theta values, in radians.
 */
OSKAR_EXPORT
void oskar_apply_element_taper_gaussian_scalar_d(double2* jones,
        const int num_sources, const double fwhm, const double* theta);

/**
 * @brief
 * Function to apply a Gaussian taper to the matrix element response
 * (double precision).
 *
 * @details
 * This function multiplies the matrix response of the element by a
 * Gaussian taper. The multiplication is performed in-place.
 *
 * @param[in,out] jones    Array of Jones matrices.
 * @param[in] num_sources  Number of source positions.
 * @param[in] fwhm         Full-width half-max of Gaussian, in radians.
 * @param[in] theta        Array of source theta values, in radians.
 */
OSKAR_EXPORT
void oskar_apply_element_taper_gaussian_matrix_d(double4c* jones,
        const int num_sources, const double fwhm, const double* theta);

/**
 * @brief
 * Wrapper function to apply a Gaussian taper to the matrix element response.
 *
 * @details
 * This function multiplies the matrix response of the element by a
 * Gaussian taper. The multiplication is performed in-place.
 *
 * @param[in,out] jones    Array of Jones matrices.
 * @param[in] num_sources  Number of source positions.
 * @param[in] fwhm         Full-width half-max of Gaussian, in radians.
 * @param[in] theta        Array of source theta values, in radians.
 * @param[in,out] status   Status return code.
 */
OSKAR_EXPORT
void oskar_apply_element_taper_gaussian(oskar_Mem* jones, int num_sources,
        double fwhm, const oskar_Mem* theta, int* status);

#ifdef __cplusplus
}
#endif

#endif /* OSKAR_APPLY_ELEMENT_TAPER_GAUSSIAN_H_ */
