/*
 * Copyright (c) 2011-2013, The University of Oxford
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

#ifndef OSKAR_JONES_SET_REAL_SCALAR_H_
#define OSKAR_JONES_SET_REAL_SCALAR_H_

/**
 * @file oskar_jones_set_real_scalar.h
 */

#include <oskar_global.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 * Fills an OSKAR Jones matrix structure with a real scalar.
 *
 * @details
 * This function fills an OSKAR Jones data structure with a real scalar.
 *
 * @param[in,out] jones Pointer to data structure.
 * @param[in] scalar The scalar value to use.
 * @param[in,out]  status   Status return code.
 */
OSKAR_EXPORT
void oskar_jones_set_real_scalar(oskar_Jones* jones, double scalar,
        int* status);

#ifdef __cplusplus
}
#endif

#endif /* OSKAR_JONES_SET_REAL_SCALAR_H_ */
