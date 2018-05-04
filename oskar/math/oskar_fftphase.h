/*
 * Copyright (c) 2016, The University of Oxford
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

#ifndef OSKAR_FFTPHASE_H_
#define OSKAR_FFTPHASE_H_

/**
 * @file oskar_fftphase.h
 */

#include <oskar_global.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 * Provide fftshift() behaviour for complex gridded data (single precision).
 *
 * @details
 * Provide fftshift() behaviour for complex gridded data.
 * The data are multiplied by a checker-board pattern to achieve the same
 * result as fftshift(), without actually moving memory around.
 *
 * @param[in] num_x             Grid side length in x.
 * @param[in] num_y             Grid side length in y.
 * @param[in,out] complex_data  Pointer to complex grid.
 */
OSKAR_EXPORT
void oskar_fftphase_cf(const int num_x, const int num_y, float* complex_data);

/**
 * @brief
 * Provide fftshift() behaviour for gridded data (single precision).
 *
 * @details
 * Provide fftshift() behaviour for gridded data.
 * The data are multiplied by a checker-board pattern to achieve the same
 * result as fftshift(), without actually moving memory around.
 *
 * @param[in] num_x             Grid side length in x.
 * @param[in] num_y             Grid side length in y.
 * @param[in,out] data          Pointer to grid.
 */
OSKAR_EXPORT
void oskar_fftphase_f(const int num_x, const int num_y, float* data);

/**
 * @brief
 * Provide fftshift() behaviour for complex gridded data (double precision).
 *
 * @details
 * Provide fftshift() behaviour for complex gridded data.
 * The data are multiplied by a checker-board pattern to achieve the same
 * result as fftshift(), without actually moving memory around.
 *
 * @param[in] num_x             Grid side length in x.
 * @param[in] num_y             Grid side length in y.
 * @param[in,out] complex_data  Pointer to complex grid.
 */
OSKAR_EXPORT
void oskar_fftphase_cd(const int num_x, const int num_y, double* complex_data);

/**
 * @brief
 * Provide fftshift() behaviour for gridded data (double precision).
 *
 * @details
 * Provide fftshift() behaviour for gridded data.
 * The data are multiplied by a checker-board pattern to achieve the same
 * result as fftshift(), without actually moving memory around.
 *
 * @param[in] num_x             Grid side length in x.
 * @param[in] num_y             Grid side length in y.
 * @param[in,out] data          Pointer to grid.
 */
OSKAR_EXPORT
void oskar_fftphase_d(const int num_x, const int num_y, double* data);

#ifdef __cplusplus
}
#endif

#endif /* OSKAR_FFTPHASE_H_ */
