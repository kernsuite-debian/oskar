/*
 * Copyright (c) 2011-2014, The University of Oxford
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

#ifndef OSKAR_SKY_HORIZON_CLIP_H_
#define OSKAR_SKY_HORIZON_CLIP_H_

/**
 * @file oskar_sky_horizon_clip.h
 */

#include <oskar_global.h>
#include <oskar_telescope.h>
#include <oskar_station_work.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 * Compacts a sky model into another one by removing sources below the
 * horizon of all stations.
 *
 * @details
 * Copies sources into another sky model that are above the horizon of
 * stations.
 *
 * @param[out] out          The output sky model.
 * @param[in]  in           The input sky model.
 * @param[in]  telescope    The telescope model.
 * @param[in]  work         Work arrays.
 * @param[in,out]  status   Status return code.
 */
OSKAR_EXPORT
void oskar_sky_horizon_clip(oskar_Sky* out, const oskar_Sky* in,
        const oskar_Telescope* telescope, double gast,
        oskar_StationWork* work, int* status);

#ifdef __cplusplus
}
#endif

#endif /* OSKAR_SKY_HORIZON_CLIP_H_ */
