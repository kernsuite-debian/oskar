/*
 * Copyright (c) 2016-2017, The University of Oxford
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

#include "imager/oskar_grid_correction.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void oskar_grid_correction_d(const int image_size,
        const double* corr_func, double* complex_image)
{
    int i, j;
    for (j = 0; j < image_size; ++j)
    {
        size_t k;
        const double cj = corr_func[j];
        k = j;
        k *= image_size; /* Tested to avoid int overflow. */
        for (i = 0; i < image_size; ++i)
        {
            const size_t m = (k + i) << 1;
            const double t = corr_func[i] * cj;
            complex_image[m] *= t;
            complex_image[m + 1] *= t;
        }
    }
}


void oskar_grid_correction_f(const int image_size,
        const double* corr_func, float* complex_image)
{
    int i, j;
    for (j = 0; j < image_size; ++j)
    {
        size_t k;
        const double cj = corr_func[j];
        k = j;
        k *= image_size; /* Tested to avoid int overflow. */
        for (i = 0; i < image_size; ++i)
        {
            const size_t m = (k + i) << 1;
            const double t = corr_func[i] * cj;
            complex_image[m] *= t;
            complex_image[m + 1] *= t;
        }
    }
}

#ifdef __cplusplus
}
#endif
