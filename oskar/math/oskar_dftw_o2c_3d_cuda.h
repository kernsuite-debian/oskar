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

#ifndef OSKAR_DFTW_O2C_3D_CUDA_H_
#define OSKAR_DFTW_O2C_3D_CUDA_H_

/**
 * @file oskar_dftw_o2c_3d_cuda.h
 */

#include <oskar_global.h>
#include <utility/oskar_vector_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 * CUDA function to perform a 3D real-to-complex single-precision DFT using
 * supplied weights, where all input signals are implicitly of amplitude 1.0.
 *
 * @details
 * This CUDA function performs a 3D real-to-complex DFT, where all the input
 * signals are implicitly assumed to be of amplitude 1.0.
 *
 * The wavelength used to compute the supplied wavenumber must be in the
 * same units as the input positions.
 *
 * The computed points are returned in the \p d_output array, which must be
 * pre-sized to length n_out. The values in the \p d_output array are
 * the complex values for each output position.
 *
 * Note that all pointers refer to device memory.
 *
 * @param[in] n_in         Number of input points.
 * @param[in] wavenumber   Wavenumber (2 pi / wavelength).
 * @param[in] d_x_in       Array of input x positions.
 * @param[in] d_y_in       Array of input y positions.
 * @param[in] d_z_in       Array of input z positions.
 * @param[in] d_weights_in Array of complex DFT weights.
 * @param[in] n_out        Number of output points.
 * @param[in] d_x_out      Array of output 1/x positions.
 * @param[in] d_y_out      Array of output 1/y positions.
 * @param[in] d_z_out      Array of output 1/z positions.
 * @param[out] d_output    Array of computed output points (see note, above).
 */
OSKAR_EXPORT
void oskar_dftw_o2c_3d_cuda_f(int n_in, float wavenumber, const float* d_x_in,
        const float* d_y_in, const float* d_z_in, const float2* d_weights_in,
        int n_out, const float* d_x_out, const float* d_y_out,
        const float* d_z_out, float2* d_output);

/**
 * @brief
 * CUDA function to perform a 3D real-to-complex double-precision DFT using
 * supplied weights, where all input signals are implicitly of amplitude 1.0.
 *
 * @details
 * This CUDA function performs a 3D real-to-complex DFT, where all the input
 * signals are implicitly assumed to be of amplitude 1.0.
 *
 * The wavelength used to compute the supplied wavenumber must be in the
 * same units as the input positions.
 *
 * The computed points are returned in the \p d_output array, which must be
 * pre-sized to length n_out. The values in the \p d_output array are
 * the complex values for each output position.
 *
 * Note that all pointers refer to device memory.
 *
 * @param[in] n_in         Number of input points.
 * @param[in] wavenumber   Wavenumber (2 pi / wavelength).
 * @param[in] d_x_in       Array of input x positions.
 * @param[in] d_y_in       Array of input y positions.
 * @param[in] d_z_in       Array of input z positions.
 * @param[in] d_weights_in Array of complex DFT weights.
 * @param[in] n_out        Number of output points.
 * @param[in] d_x_out      Array of output 1/x positions.
 * @param[in] d_y_out      Array of output 1/y positions.
 * @param[in] d_z_out      Array of output 1/z positions.
 * @param[out] d_output    Array of computed output points (see note, above).
 */
OSKAR_EXPORT
void oskar_dftw_o2c_3d_cuda_d(int n_in, double wavenumber, const double* d_x_in,
        const double* d_y_in, const double* d_z_in, const double2* d_weights_in,
        int n_out, const double* d_x_out, const double* d_y_out,
        const double* d_z_out, double2* d_output);

#ifdef __cplusplus
}
#endif

#endif /* OSKAR_DFTW_O2C_3D_CUDA_H_ */
