/* /////////////////////////////////////////////////////////////////////////
 * File:    torrenteol/torrenteol.h
 *
 * Purpose: Definition of the TorrentEOL API.
 *
 * Created: 5th October 2026
 * Updated: 5th October 2026
 *
 * Home:    https://github.com/synesissoftware/torrenteol/
 *
 * Copyright (c) 2026, Matthew Wilson and Synesis Information Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the names of Matthew Wilson and Synesis Information Systems nor
 *   the names of any contributors may be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file torrenteol/torrenteol.h Definition of the TorrentEOL API
 */

#ifndef TORRENTEOL_INCL_TORRENTEOL_H_TORRENTEOL
#define TORRENTEOL_INCL_TORRENTEOL_H_TORRENTEOL


/* /////////////////////////////////////////////////////////////////////////
 * version
 */

#ifndef TORRENTEOL_DOCUMENTATION_SKIP_SECTION
# define TORRENTEOL_VER_TORRENTEOL_H_TORRENTEOL_MAJOR       1
# define TORRENTEOL_VER_TORRENTEOL_H_TORRENTEOL_MINOR       0
# define TORRENTEOL_VER_TORRENTEOL_H_TORRENTEOL_REVISION    1
# define TORRENTEOL_VER_TORRENTEOL_H_TORRENTEOL_EDIT        1
#endif /* !TORRENTEOL_DOCUMENTATION_SKIP_SECTION */


#ifndef TORRENTEOL_DOCUMENTATION_SKIP_SECTION
# define TORRENTEOL_VER_0_1_0_A1                            0x00010041
#endif /* !TORRENTEOL_DOCUMENTATION_SKIP_SECTION */

/** \def TORRENTEOL_VER_MAJOR
 * The major version number of **TorrentEOL**
 */

/** \def TORRENTEOL_VER_MINOR
 * The minor version number of **TorrentEOL**
 */

/** \def TORRENTEOL_VER_PATCH
 * The patch version number of **TorrentEOL**
 */

/** \def TORRENTEOL_VER_ALPHABETA
 * The prerelease discriminator of **TorrentEOL**. `0xFF` is a release;
 * `0x41` is alpha 1.
 */

/** \def TORRENTEOL_VER
 * The current composite version number of **TorrentEOL**
 */

#define TORRENTEOL_VER_MAJOR                                0
#define TORRENTEOL_VER_MINOR                                1
#define TORRENTEOL_VER_PATCH                                0
#define TORRENTEOL_VER_ALPHABETA                            0x41

#define TORRENTEOL_VER \
    (0\
        |   (   TORRENTEOL_VER_MAJOR       << 24   ) \
        |   (   TORRENTEOL_VER_MINOR       << 16   ) \
        |   (   TORRENTEOL_VER_PATCH       <<  8   ) \
        |   (   TORRENTEOL_VER_ALPHABETA   <<  0   ) \
    )

#ifndef TORRENTEOL_DOCUMENTATION_SKIP_SECTION
# define TORRENTEOL_VER_REVISION                            TORRENTEOL_VER_PATCH
#endif /* !TORRENTEOL_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stdint.h>


/* /////////////////////////////////////////////////////////////////////////
 * documentation
 */

/** \defgroup group__torrenteol_api TorrentEOL API
 * \brief The TorrentEOL public API
 *
 * The types, constants, and functions that constitute the TorrentEOL API.
 * Line-reading entry points are not part of this skeleton.
 */


/* /////////////////////////////////////////////////////////////////////////
 * storage class
 */

#ifdef __cplusplus

# define TORRENTEOL_EXTERN_C                                extern "C"
#else /* ? __cplusplus */

# define TORRENTEOL_EXTERN_C                                extern
#endif /* ? __cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */

/** \brief The return code type of the TorrentEOL API
 * \ingroup group__torrenteol_api
 */
enum TORRENTEOL_RC
{
        TORRENTEOL_RC_SUCCESS               =   0  /*!< \brief operation completed successfully */
    ,   TORRENTEOL_RC_ALREADY_INITIALISED          /*!< \brief torrenteol_init() was called while the library was already initialised */
    ,   TORRENTEOL_RC_NOT_INITIALISED              /*!< \brief torrenteol_uninit() was called while the library was not initialised */
};
#ifndef TORRENTEOL_DOCUMENTATION_SKIP_SECTION
typedef enum TORRENTEOL_RC                                  TORRENTEOL_RC;
#endif /* !TORRENTEOL_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** \brief Obtains the composite version of the loaded TorrentEOL library.
 * \ingroup group__torrenteol_api
 *
 * \retval The value of TORRENTEOL_VER at the time this library was built.
 *
 * This call does not require torrenteol_init().
 */
TORRENTEOL_EXTERN_C
uint32_t
torrenteol_getVersion(void);

/** \brief Initialises the TorrentEOL library.
 * \ingroup group__torrenteol_api
 *
 * \retval TORRENTEOL_RC_SUCCESS The library is now initialised.
 * \retval TORRENTEOL_RC_ALREADY_INITIALISED The library was already
 *   initialised. The initialisation count is not increased.
 *
 * The skeleton keeps a process-wide flag. It is not thread-safe.
 */
TORRENTEOL_EXTERN_C
TORRENTEOL_RC
torrenteol_init(void);

/** \brief Uninitialises the TorrentEOL library.
 * \ingroup group__torrenteol_api
 *
 * \retval TORRENTEOL_RC_SUCCESS The library is now uninitialised.
 * \retval TORRENTEOL_RC_NOT_INITIALISED The library was not initialised.
 */
TORRENTEOL_EXTERN_C
TORRENTEOL_RC
torrenteol_uninit(void);


/* ////////////////////////////////////////////////////////////////////// */

#endif /* !TORRENTEOL_INCL_TORRENTEOL_H_TORRENTEOL */

/* ///////////////////////////// end of file //////////////////////////// */

