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

#ifndef OSKAR_SETTINGS_MACROS_H_
#define OSKAR_SETTINGS_MACROS_H_

#ifndef OSKAR_DECL_EXPORT
#    ifdef _MSC_VER
#        define OSKAR_DECL_EXPORT __declspec(dllexport)
#    elif __GNUC__ >= 4
#        define OSKAR_DECL_EXPORT __attribute__((visibility ("default")))
#    else
#        define OSKAR_DECL_EXPORT
#    endif
#endif
#ifndef OSKAR_DECL_IMPORT
#    ifdef _MSC_VER
#        define OSKAR_DECL_IMPORT __declspec(dllimport)
#    elif __GNUC__ >= 4
#        define OSKAR_DECL_IMPORT __attribute__((visibility ("default")))
#    else
#        define OSKAR_DECL_IMPORT
#    endif
#endif


#ifdef oskar_settings_EXPORTS
#    define OSKAR_SETTINGS_EXPORT OSKAR_DECL_EXPORT
#else
#    define OSKAR_SETTINGS_EXPORT OSKAR_DECL_IMPORT
#endif

enum OSKAR_SETTINGS_ERRORS
{
    OSKAR_ERR_SETTINGS_NO_VALUE = -200,
    OSKAR_ERR_SETTINGS_INT_CONVERSION_FAIL = -201,
    OSKAR_ERR_SETTINGS_UNSIGNED_INT_CONVERSION_FAIL = -202,
    OSKAR_ERR_SETTINGS_DOUBLE_CONVERSION_FAIL = -203,
    OSKAR_ERR_SETTINGS_INT_LIST_CONVERSION_FAIL = -204,
    OSKAR_ERR_SETTINGS_DOUBLE_LIST_CONVERSION_FAIL = -205,
    OSKAR_ERR_SETTINGS_STRING_LIST_CONVERSION_FAIL = -206
};

#endif /* OSKAR_SETTINGS_MACROS_H_ */
