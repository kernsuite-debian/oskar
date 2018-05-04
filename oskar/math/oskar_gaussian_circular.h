/*
 * Copyright (c) 2013-2017, The University of Oxford
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

#ifndef OSKAR_GAUSSIAN_CIRCULAR_H_
#define OSKAR_GAUSSIAN_CIRCULAR_H_

/**
 * @file oskar_gaussian_circular.h
 */

#include <oskar_global.h>
#include <mem/oskar_mem.h>

#ifdef __cplusplus
extern "C" {
#endif

OSKAR_EXPORT
void oskar_gaussian_circular_complex_f(int n, const float* x,
        const float* y, float std, float2* z);

OSKAR_EXPORT
void oskar_gaussian_circular_matrix_f(int n, const float* x,
        const float* y, float std, float4c* z);

OSKAR_EXPORT
void oskar_gaussian_circular_complex_d(int n, const double* x,
        const double* y, double std, double2* z);

OSKAR_EXPORT
void oskar_gaussian_circular_matrix_d(int n, const double* x,
        const double* y, double std, double4c* z);

OSKAR_EXPORT
void oskar_gaussian_circular(int num_points,
        const oskar_Mem* l, const oskar_Mem* m, double std,
        oskar_Mem* out, int* status);

#ifdef __cplusplus
}
#endif

#endif /* OSKAR_GAUSSIAN_CIRCULAR_H_ */
