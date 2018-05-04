/*
 * Copyright (c) 2014-2016, The University of Oxford
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

#ifndef OSKAR_MEM_GET_ELEMENT_H_
#define OSKAR_MEM_GET_ELEMENT_H_

/**
 * @file oskar_mem_get_element.h
 */

#include <oskar_global.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 * Gets the value of one element in a scalar array, either from CPU or GPU
 * memory.
 *
 * @details
 * This function returns the value of one element in an array at the
 * specified index. The array may be either in CPU or GPU memory.
 *
 * The index is with respect to the precision of the base data type,
 * so this can also be used to return part of a complex number.
 *
 * @param[in] mem           Pointer to the memory block.
 * @param[in] index         Array index to return.
 * @param[in,out]  status   Status return code.
 */
OSKAR_EXPORT
double oskar_mem_get_element(const oskar_Mem* mem, size_t index, int* status);

/**
 * @brief
 * Gets the value of one element in a complex array, either from CPU or GPU
 * memory.
 *
 * @details
 * This function returns the value of one element in a complex array at the
 * specified index. The array may be either in CPU or GPU memory.
 *
 * @param[in] mem           Pointer to the memory block.
 * @param[in] index         Array index to return.
 * @param[in,out]  status   Status return code.
 */
OSKAR_EXPORT
double2 oskar_mem_get_element_complex(const oskar_Mem* mem, size_t index,
        int* status);

/**
 * @brief
 * Gets the value of one element in a matrix array, either from CPU or GPU
 * memory.
 *
 * @details
 * This function returns the value of one element in a matrix array at the
 * specified index. The array may be either in CPU or GPU memory.
 *
 * @param[in] mem           Pointer to the memory block.
 * @param[in] index         Array index to return.
 * @param[in,out]  status   Status return code.
 */
OSKAR_EXPORT
double4c oskar_mem_get_element_matrix(const oskar_Mem* mem, size_t index,
        int* status);

#ifdef __cplusplus
}
#endif

#endif /* OSKAR_MEM_GET_ELEMENT_H_ */
