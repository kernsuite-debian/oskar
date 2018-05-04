/*
 * Copyright (c) 2012-2015, The University of Oxford
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

#include "mem/oskar_mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

oskar_Mem* oskar_mem_read_binary_raw(const char* filename, int type,
        int location, int* status)
{
    size_t num_elements, element_size, size_bytes;
    oskar_Mem *mem = 0;
    FILE* stream;

    /* Check if safe to proceed. */
    if (*status) return 0;

    /* Open the input file. */
    stream = fopen(filename, "rb");
    if (!stream)
    {
        *status = OSKAR_ERR_FILE_IO;
        return 0;
    }

    /* Get the file size. */
    fseek(stream, 0, SEEK_END);
    size_bytes = ftell(stream);

    /* Create memory block of the right size. */
    element_size = oskar_mem_element_size(type);
    num_elements = (size_t)ceil(size_bytes / element_size);
    mem = oskar_mem_create(type, OSKAR_CPU, num_elements, status);
    if (*status)
    {
        oskar_mem_free(mem, status);
        fclose(stream);
        return 0;
    }

    /* Read the data. */
    fseek(stream, 0, SEEK_SET);
    if (fread(oskar_mem_void(mem), 1, size_bytes, stream) != size_bytes)
    {
        oskar_mem_free(mem, status);
        fclose(stream);
        *status = OSKAR_ERR_FILE_IO;
        return 0;
    }

    /* Close the input file. */
    fclose(stream);

    /* Copy to GPU memory if required. */
    if (location != OSKAR_CPU)
    {
        oskar_Mem* gpu;
        gpu = oskar_mem_create_copy(mem, location, status);
        oskar_mem_free(mem, status);
        return gpu;
    }

    return mem;
}

#ifdef __cplusplus
}
#endif
