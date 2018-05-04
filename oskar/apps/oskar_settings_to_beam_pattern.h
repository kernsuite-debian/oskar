/*
 * Copyright (c) 2017, The University of Oxford
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

#ifndef OSKAR_SETTINGS_TO_BEAM_PATTERN_H_
#define OSKAR_SETTINGS_TO_BEAM_PATTERN_H_

/**
 * @file oskar_settings_to_beam_pattern.h
 */

#include <oskar_global.h>
#include <beam_pattern/oskar_beam_pattern.h>
#include <log/oskar_log.h>

#ifdef __cplusplus

#include <settings/oskar_SettingsTree.h>

/**
 * @brief
 * Creates a beam pattern simulator from the supplied settings.
 *
 * @details
 * This function creates and returns a beam pattern simulator from the
 * given settings.
 *
 * @param[in] s           A pointer to the settings tree.
 * @param[in,out] log     A pointer to the log to use.
 * @param[in,out] status  Status return code.
 *
 * @return A handle to the new beam pattern simulator.
 */
OSKAR_APPS_EXPORT
oskar_BeamPattern* oskar_settings_to_beam_pattern(oskar::SettingsTree* s,
        oskar_Log* log, int* status);

#endif

#endif /* OSKAR_SETTINGS_TO_BEAM_PATTERN_H_ */
