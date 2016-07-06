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

#ifndef OSKAR_STATION_OVERRIDE_ELEMENT_XY_POSITION_ERRORS_H_
#define OSKAR_STATION_OVERRIDE_ELEMENT_XY_POSITION_ERRORS_H_

/**
 * @file oskar_station_override_element_xy_position_errors.h
 */

#include <oskar_global.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 * Overrides element xy-position errors in a station model.
 *
 * @details
 * This function overrides the element xy-position errors in a station model
 * using the supplied standard deviation.
 *
 * It applies an offset to the xy-"signal"-positions in the station model
 * using the currently set xy-"weights"-positions.
 *
 * Only the positions at the deepest (element) level are set.
 *
 * The station model must be in CPU-accessible memory.
 *
 * @param[in,out] s                Station model structure to modify.
 * @param[in] seed                 Random generator seed.
 * @param[in] position_error_xy_m  Standard deviation of xy-position, in metres.
 * @param[in,out] status           Status return code.
 */
OSKAR_EXPORT
void oskar_station_override_element_xy_position_errors(oskar_Station* s,
        unsigned int seed, double position_error_xy_m, int* status);

#ifdef __cplusplus
}
#endif

#endif /* OSKAR_STATION_OVERRIDE_ELEMENT_XY_POSITION_ERRORS_H_ */
