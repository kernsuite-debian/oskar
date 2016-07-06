/*
 * Copyright (c) 2013-2015, The University of Oxford
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

#include <private_jones.h>
#include <oskar_jones.h>

#ifdef __cplusplus
extern "C" {
#endif

oskar_Jones* oskar_jones_create_copy(const oskar_Jones* src, int location,
        int* status)
{
    oskar_Jones* jones = 0;

    /* Check if safe to proceed. */
    if (*status) return 0;

    /* Create the new structure. */
    jones = oskar_jones_create(oskar_jones_type(src), location,
            oskar_jones_num_stations(src), oskar_jones_num_sources(src),
            status);

    /* Copy the existing data to the new structure. */
    jones->num_stations = src->num_stations;
    jones->num_sources = src->num_sources;
    jones->cap_stations = src->cap_stations;
    jones->cap_sources = src->cap_sources;
    oskar_mem_copy(jones->data, src->data, status);

    /* Return pointer to the new structure. */
    return jones;
}

#ifdef __cplusplus
}
#endif
