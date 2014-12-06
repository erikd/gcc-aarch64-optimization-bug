/*
 * Copyright (c) 2011 Apple Inc. All rights reserved.
 *
 * @APPLE_APACHE_LICENSE_HEADER_START@
 *
 * Licensed under the Apache License, Version 2.0 (the "License") ;
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	 http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @APPLE_APACHE_LICENSE_HEADER_END@
 */

/*
	File:		aglib.h

	Copyright:	(C) 2001-2011 Apple, Inc.
*/

#ifndef AGLIB_H
#define AGLIB_H

#include <stdint.h>

#define QBSHIFT		9
#define QB			(1 << QBSHIFT)
#define PB0			40
#define MB0			10
#define KB0			14
#define MAX_RUN_DEFAULT 255

#define MMULSHIFT	2
#define MDENSHIFT	(QBSHIFT - MMULSHIFT - 1)
#define MOFF		((1 << (MDENSHIFT - 2)))

#define BITOFF 24

/* Max. prefix of 1's. */
#define MAX_PREFIX_16			9
#define MAX_PREFIX_TOLONG_16	15
#define MAX_PREFIX_32			9

/* Max. bits in 16-bit data type */
#define MAX_DATATYPE_BITS_16	16

enum
{
	kALAC_UnimplementedError	= -4,
	kALAC_FileNotFoundError		= -43,
	kALAC_ParamError			= -50,
	kALAC_MemFullError			= -108,
	fALAC_FrameLengthError		= -666,
} ;

static inline void
psf_put_be32 (uint8_t *ptr, int offset, int32_t value)
{
	ptr [offset] = value >> 24 ;
	ptr [offset + 1] = value >> 16 ;
	ptr [offset + 2] = value >> 8 ;
	ptr [offset + 3] = value ;
} /* psf_put_be32 */


static inline int32_t
psf_get_be32 (uint8_t *ptr, int offset)
{	int32_t value ;

	value = ((uint32_t) ptr [offset]) << 24 ;
	value += ptr [offset + 1] << 16 ;
	value += ptr [offset + 2] << 8 ;
	value += ptr [offset + 3] ;
	return value ;
} /* psf_get_be32 */

typedef struct AGParamRec
{
	uint32_t mb, mb0, pb, kb, wb, qb ;
	uint32_t fw, sw ;

	uint32_t maxrun ;

	// fw = 1, sw = 1 ;

} AGParamRec, *AGParamRecPtr ;

int32_t	dyn_comp (AGParamRecPtr params, int32_t * pc, unsigned char * out, uint32_t numSamples, int32_t bitSize, uint32_t * outNumBits) ;


#endif //#ifndef AGLIB_H
