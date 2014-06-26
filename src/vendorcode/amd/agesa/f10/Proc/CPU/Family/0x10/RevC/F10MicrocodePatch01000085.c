/**
 * @file
 *
 * AMD Family_10 Microcode patch.
 *
 * Fam10 Microcode Patch rev 01000085 for 1040 or equivalent.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  CPU/FAMILY/0x10/REVC
 * @e \$Revision: 5832 $   @e \$Date: 2008-04-15 16:30:24 -0700 (Tue, 15 Apr 2008) $
 *
 */
/*
 ******************************************************************************
 *
 * Copyright (c) 2011, Advanced Micro Devices, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the names of 
 *       its contributors may be used to endorse or promote products derived 
 *       from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 ******************************************************************************
 */
/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "AGESA.h"
#include "cpuRegisters.h"
#include "cpuEarlyInit.h"

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

// Patch code 01000085 for 1040 and equivalent
CONST MICROCODE_PATCHES ROMDATA CpuF10MicrocodePatch01000085 =
{
0x08,
0x20,
0x01,
0x05,
0x85,
0x00,
0x00,
0x01,
0x00,
0x80,
0x20,
0x00,
0xc1,
0xb9,
0x5d,
0x3d,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x40,
0x10,
0x00,
0x00,
0x00,
0xaa,
0xaa,
0xaa,
0x2f,
0x02,
0x00,
0x00,
0xa0,
0x09,
0x00,
0x00,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xff,
0xcf,
0xf8,
0xff,
0x2a,
0xc3,
0x3f,
0xd5,
0xfd,
0xbc,
0xff,
0xff,
0xb3,
0x0f,
0xff,
0x58,
0xd5,
0xf0,
0x35,
0x95,
0x03,
0x1d,
0xf8,
0x63,
0x7b,
0x40,
0x03,
0xd4,
0x00,
0x80,
0x77,
0xff,
0x7f,
0xfe,
0xe1,
0x98,
0x8a,
0x54,
0xfe,
0xaf,
0xff,
0xff,
0x87,
0x7f,
0xa9,
0x03,
0xf8,
0x0f,
0xfc,
0xfc,
0x1b,
0xfe,
0x01,
0x00,
0xe0,
0xff,
0x7b,
0x1f,
0xc0,
0x65,
0xf4,
0x0d,
0xf0,
0xe0,
0x8f,
0xfe,
0x04,
0xde,
0x04,
0x03,
0xad,
0xc3,
0x2f,
0xfe,
0xa9,
0xfc,
0x07,
0x00,
0x3f,
0x0f,
0xff,
0x15,
0x00,
0xb0,
0x00,
0xf8,
0xaf,
0xe4,
0x3f,
0x07,
0xf8,
0x79,
0xf8,
0xfe,
0xff,
0x97,
0xa7,
0x1f,
0xe0,
0xe7,
0xe1,
0xbf,
0xf1,
0x00,
0xfe,
0x7f,
0x6f,
0x80,
0x03,
0x4a,
0x1a,
0x00,
0xc8,
0x1f,
0xf8,
0x07,
0xf0,
0xfc,
0x03,
0xf8,
0x37,
0x7f,
0xe0,
0x1f,
0xc0,
0xf0,
0x0f,
0xe0,
0xdf,
0xff,
0x81,
0x7f,
0x00,
0xc3,
0x3f,
0x80,
0x7f,
0xfc,
0x7f,
0x0f,
0x00,
0xf8,
0x0f,
0xfc,
0x03,
0x1b,
0xfe,
0x01,
0xfc,
0xe0,
0x3f,
0xf0,
0x0f,
0x6f,
0xf8,
0x07,
0xf0,
0x80,
0xff,
0xc0,
0x3f,
0xbf,
0xe1,
0x1f,
0xc0,
0x00,
0xfe,
0xbf,
0x07,
0x01,
0xfc,
0x07,
0xfe,
0xfe,
0x0d,
0xff,
0x00,
0x07,
0xf0,
0x1f,
0xf8,
0xf8,
0x37,
0xfc,
0x03,
0x1f,
0xc0,
0x7f,
0xe0,
0xe0,
0xdf,
0xf0,
0x0f,
0x03,
0x00,
0xff,
0xdf,
0xff,
0x00,
0xfe,
0x03,
0x00,
0xff,
0x86,
0x7f,
0xfc,
0x03,
0xf8,
0x0f,
0x01,
0xfc,
0x1b,
0xfe,
0xf0,
0x0f,
0xe0,
0x3f,
0x07,
0xf0,
0x6f,
0xf8,
0xef,
0x01,
0x80,
0xff,
0x81,
0x7f,
0x00,
0xff,
0x3f,
0x80,
0x7f,
0xc3,
0x07,
0xfe,
0x01,
0xfc,
0xff,
0x00,
0xfe,
0x0d,
0x1f,
0xf8,
0x07,
0xf0,
0xfc,
0x03,
0xf8,
0x37,
0xff,
0xf7,
0x00,
0xc0,
0xff,
0xc0,
0x3f,
0x80,
0xe1,
0x1f,
0xc0,
0xbf,
0xfe,
0x03,
0xff,
0x00,
0x86,
0x7f,
0x00,
0xff,
0xf8,
0x0f,
0xfc,
0x03,
0x1b,
0xfe,
0x01,
0xfc,
0xe0,
0xff,
0x7b,
0x00,
0xc0,
0x7f,
0xe0,
0x1f,
0xdf,
0xf0,
0x0f,
0xe0,
0x00,
0xff,
0x81,
0x7f,
0x7f,
0xc3,
0x3f,
0x80,
0x01,
0xfc,
0x07,
0xfe,
0xfe,
0x0d,
0xff,
0x00,
0x00,
0xf0,
0xff,
0x3d,
0x0f,
0xe0,
0x3f,
0xf0,
0xf0,
0x6f,
0xf8,
0x07,
0x3f,
0x80,
0xff,
0xc0,
0xc0,
0xbf,
0xe1,
0x1f,
0xff,
0x00,
0xfe,
0x03,
0x00,
0xff,
0x86,
0x7f,
0x1e,
0x00,
0xf8,
0xff,
0xf8,
0x07,
0xf0,
0x1f,
0x03,
0xf8,
0x37,
0xfc,
0xe0,
0x1f,
0xc0,
0x7f,
0x0f,
0xe0,
0xdf,
0xf0,
0x81,
0x7f,
0x00,
0xff,
0x3f,
0x80,
0x7f,
0xc3,
0x7f,
0x0f,
0x00,
0xfc,
0x0f,
0xfc,
0x03,
0xf8,
0xfe,
0x01,
0xfc,
0x1b,
0x3f,
0xf0,
0x0f,
0xe0,
0xf8,
0x07,
0xf0,
0x6f,
0xff,
0xc0,
0x3f,
0x80,
0xe1,
0x1f,
0xc0,
0xbf,
0xfe,
0xbf,
0x07,
0x00,
0xfc,
0x07,
0xfe,
0x01,
0x0d,
0xff,
0x00,
0xfe,
0xf0,
0x1f,
0xf8,
0x07,
0x37,
0xfc,
0x03,
0xf8,
0xc0,
0x7f,
0xe0,
0x1f,
0xdf,
0xf0,
0x0f,
0xe0,
0x00,
0xff,
0xdf,
0x03,
0x00,
0xfe,
0x03,
0xff,
0xff,
0x86,
0x7f,
0x00,
0x03,
0xf8,
0x0f,
0xfc,
0xfc,
0x1b,
0xfe,
0x01,
0x0f,
0xe0,
0x3f,
0xf0,
0xf0,
0x6f,
0xf8,
0x07,
0x01,
0x80,
0xff,
0xef,
0x7f,
0x00,
0xff,
0x81,
0x80,
0x7f,
0xc3,
0x3f,
0xfe,
0x01,
0xfc,
0x07,
0x00,
0xfe,
0x0d,
0xff,
0xf8,
0x07,
0xf0,
0x1f,
0x03,
0xf8,
0x37,
0xfc,
0xd7,
0x00,
0x80,
0xfb,
0xc0,
0x3f,
0x80,
0xff,
0x1f,
0xc0,
0xbf,
0xe1,
0x03,
0xff,
0x00,
0xfe,
0x7f,
0x00,
0xff,
0x86,
0x0f,
0xfc,
0x03,
0xf8,
0xfe,
0x01,
0xfc,
0x1b,
0xfd,
0x6b,
0x00,
0xa0,
0xcf,
0x56,
0x0e,
0x80,
0xe0,
0x0f,
0xe8,
0x75,
0xf6,
0xff,
0xff,
0x00,
0xc3,
0xbb,
0x16,
0xf2,
0x04,
0x37,
0xf8,
0x13,
0x0e,
0x7f,
0x0c,
0xb8,
0xe0,
0xdc,
0x35,
0x00,
0x60,
0xff,
0xff,
0x1f,
0x7f,
0x78,
0xc7,
0xa2,
0x95,
0xff,
0xe9,
0x3f,
0xdf,
0xe0,
0xcf,
0x2a,
0x00,
0xfe,
0x03,
0xff,
0xff,
0x86,
0x7f,
0x00,
0x00,
0xf8,
0xff,
0x1e,
0xff,
0xf2,
0xbf,
0xff,
0xfd,
0x1f,
0xfc,
0x7b,
0x0f,
0xc0,
0x23,
0xd0,
0xed,
0xf5,
0xe0,
0xef,
0x7f,
0x00,
0xff,
0x81,
0x80,
0x7f,
0xc3,
0x3f,
0x0f,
0x00,
0xfc,
0x7f,
0xfe,
0x03,
0xf9,
0x5f,
0x01,
0x7e,
0x1e,
0xfe,
0xf0,
0x0f,
0xe0,
0x3f,
0x07,
0xf0,
0x6f,
0xf8,
0xc0,
0x3f,
0x80,
0xff,
0x1f,
0xc0,
0xbf,
0xe1,
0x4c,
0x06,
0x00,
0xbc,
0x07,
0xfe,
0x01,
0xfc,
0xff,
0x00,
0xfe,
0x0d,
0x1f,
0xf8,
0x07,
0xf0,
0xfc,
0x03,
0xf8,
0x37,
0x7f,
0xe0,
0x1f,
0xc0,
0xf0,
0x0f,
0xe0,
0xdf,
0xff,
0xdf,
0x03,
0x00,
0xfe,
0x03,
0xff,
0x00,
0x86,
0x7f,
0x00,
0xff,
0xf8,
0x0f,
0xfc,
0x03,
0x1b,
0xfe,
0x01,
0xfc,
0xe0,
0x3f,
0xf0,
0x0f,
0x6f,
0xf8,
0x07,
0xf0,
0x80,
0xff,
0xef,
0x01,
0x00,
0xff,
0x81,
0x7f,
0x7f,
0xc3,
0x3f,
0x80,
0x01,
0xfc,
0x07,
0xfe,
0xfe,
0x0d,
0xff,
0x00,
0x07,
0xf0,
0x1f,
0xf8,
0xf8,
0x37,
0xfc,
0x03,
0x00,
0xc0,
0xff,
0xf7,
0x3f,
0x80,
0xff,
0xc0,
0xc0,
0xbf,
0xe1,
0x1f,
0xff,
0x00,
0xfe,
0x03,
0x00,
0xff,
0x86,
0x7f,
0xfc,
0x03,
0xf8,
0x0f,
0x01,
0xfc,
0x1b,
0xfe,
0x7b,
0x00,
0xe0,
0xff,
0xe0,
0x1f,
0xc0,
0x7f,
0x0f,
0xe0,
0xdf,
0xf0,
0x81,
0x7f,
0x00,
0xff,
0x3f,
0x80,
0x7f,
0xc3,
0x07,
0xfe,
0x01,
0xfc,
0xff,
0x00,
0xfe,
0x0d,
0xff,
0x3d,
0x00,
0xf0,
0x3f,
0xf0,
0x0f,
0xe0,
0xf8,
0x07,
0xf0,
0x6f,
0xff,
0xc0,
0x3f,
0x80,
0xe1,
0x1f,
0xc0,
0xbf,
0xfe,
0x03,
0xff,
0x00,
0x86,
0x7f,
0x00,
0xff,
0xf8,
0xff,
0x1e,
0x00,
0xf0,
0x1f,
0xf8,
0x07,
0x37,
0xfc,
0x03,
0xf8,
0xc0,
0x7f,
0xe0,
0x1f,
0xdf,
0xf0,
0x0f,
0xe0,
0x00,
0xff,
0x81,
0x7f,
0x7f,
0xc3,
0x3f,
0x80,
0x00,
0xfc,
0x7f,
0x0f,
0x03,
0xf8,
0x0f,
0xfc,
0xfc,
0x1b,
0xfe,
0x01,
0x0f,
0xe0,
0x3f,
0xf0,
0xf0,
0x6f,
0xf8,
0x07,
0x3f,
0x80,
0xff,
0xc0,
0xc0,
0xbf,
0xe1,
0x1f,
0x07,
0x00,
0xfe,
0xbf,
0xfe,
0x01,
0xfc,
0x07,
0x00,
0xfe,
0x0d,
0xff,
0xf8,
0x07,
0xf0,
0x1f,
0x03,
0xf8,
0x37,
0xfc,
0xe0,
0x1f,
0xc0,
0x7f,
0x0f,
0xe0,
0xdf,
0xf0,
0xdf,
0x03,
0x00,
0xff,
0x03,
0xff,
0x00,
0xfe,
0x7f,
0x00,
0xff,
0x86,
0x0f,
0xfc,
0x03,
0xf8,
0xfe,
0x01,
0xfc,
0x1b,
0x3f,
0xf0,
0x0f,
0xe0,
0xf8,
0x07,
0xf0,
0x6f,
0xff,
0xef,
0x01,
0x80
};

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
