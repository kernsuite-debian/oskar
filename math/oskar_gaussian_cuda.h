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

#ifndef OSKAR_GAUSSIAN_CUDA_H_
#define OSKAR_GAUSSIAN_CUDA_H_

/**
 * @file oskar_gaussian_cuda.h
 */

#include <oskar_global.h>
#include <oskar_vector_types.h>

#ifdef __cplusplus
extern "C" {
#endif

OSKAR_EXPORT
void oskar_gaussian_cuda_f(float2* z, int n, const float* x,
        const float* y, float std);

OSKAR_EXPORT
void oskar_gaussian_cuda_mf(float4c* z, int n, const float* x,
        const float* y, float std);

OSKAR_EXPORT
void oskar_gaussian_cuda_d(double2* z, int n, const double* x,
        const double* y, double std);

OSKAR_EXPORT
void oskar_gaussian_cuda_md(double4c* z, int n, const double* x,
        const double* y, double std);

#ifdef __CUDACC__

__global__
void oskar_gaussian_cudak_f(float2* z, const int n, const float* x,
        const float* y, const float inv_2_var);

__global__
void oskar_gaussian_cudak_mf(float4c* z, const int n, const float* x,
        const float* y, const float inv_2_var);

__global__
void oskar_gaussian_cudak_d(double2* z, const int n, const double* x,
        const double* y, const double inv_2_var);

__global__
void oskar_gaussian_cudak_md(double4c* z, const int n, const double* x,
        const double* y, const double inv_2_var);

#endif /* __CUDACC__ */

#ifdef __cplusplus
}
#endif

#endif /* OSKAR_GAUSSIAN_CUDA_H_ */