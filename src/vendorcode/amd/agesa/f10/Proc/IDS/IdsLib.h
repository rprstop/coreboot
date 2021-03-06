/**
 * @file
 *
 * AMD IDS Routines
 *
 * Contains AMD AGESA Integrated Debug Macros
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  IDS
 * @e \$Revision:  $   @e \$Date: 2008-04-07 15:08:45 -0500 (Mon, 07 Apr 2008) $
 */
/*****************************************************************************
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
 *
 ***************************************************************************/

#ifndef _IDS_LIB_H_
#define _IDS_LIB_H_
#include "OptionsIds.h"
#include "cpuRegisters.h"
#include "cpuApicUtilities.h"

///Specific time stamp performance analysis which need ids control support
#if IDSOPT_CONTROL_ENABLED == TRUE
  #define PERF_SPEC_TS_ANALYSE(StdHeader)  IdsPerfSpecTsAnalyse(StdHeader)
#else
  #define PERF_SPEC_TS_ANALYSE(StdHeader)
#endif


#define IDS_NV_READ_SKIP(NvValue, Nvid, NvPtr)\
  if (((NvValue) = AmdIdsNvReader ((Nvid), (NvPtr))) != IDS_UNSUPPORTED)


#define IDS_MAX_MEM_ITEMS   80     ///< Maximum IDS Mem Table Size in Heap.


// TYPEDEFS, STRUCTURES, ENUMS
//


///Structure define for MSR register
typedef struct _REG_MSR {
  UINT32 msraddr;                      ///< Address of MSR Register
  UINT32 andmaskhi;                   ///< And Mask Bit63:32
  UINT32 andmasklo;                   ///< And Mask Bit31:0
  UINT32 ormaskhi;                    ///< Or Mask Bit63:32
  UINT32 ormasklo;                    ///< Or Mask Bit31:0
} REG_MSR;

typedef AGESA_STATUS (*PF_IDS_AP_TASK) (VOID *AptaskPara, AMD_CONFIG_PARAMS *StdHeader);

///Structure define for IdsAgesaRunFcnOnApLate
typedef struct _IDSAPLATETASK {
  PF_IDS_AP_TASK  ApTask; ///< Point function which AP need to do
  VOID *ApTaskPara; ///< Point to Ap function parameter1
} IDSAPLATETASK;

/// Data Structure defining IDS Data in HEAP
/// This data structure contains information that is stored in HEAP and will be
/// used in IDS backend function. It includes the size of memory to be allocated
/// for IDS, the relative offsets of the mapping table IDS setup options, the GRA
/// table and the register table to override mem setting. It also includes a base
/// address of IDS override image which will be used to control the behavior of
/// AGESA testpoint if this feature is enabled.
typedef struct {
  UINT64 IdsImageBase;                 ///< IDS Override Image Base Address
  UINT32 IdsHeapMemSize;              ///< IDS Total Memory Size in Heap
  UINT32 IdsNvTableOffset;            ///< Offset of IDS NV Table
  UINT32 IdsMemTableOffset;           ///< Offset of IDS Mem Table
  UINT32 IdsExtendOffset;                ///< Offset of Ids extend heap
} IDS_CONTROL_STRUCT;


/// Data Structure of Parameters for TestPoint_TSC.
typedef struct {
  UINT8 TestPoint;                    ///< The TestPoint of TestPoint_TSC
  UINT64 StartTsc;                  ///< The StartTimer of TestPoint_TSC
} TestPoint_TSC;

/// Data Structure of Parameters for TP_Perf_STRUCT.
typedef struct {
  UINT8 Index;                    ///< The Index of TP_Perf_STRUCT
  UINT32 TscInMhz;            ///< Tsc counter in 1 mhz
  TestPoint_TSC TP[EndAgesaTps];       ///< The TP of TP_Perf_STRUCT
} TP_Perf_STRUCT;




/*----------------------------------------------------------------------------------------
 *                        F U N C T I O N    P R O T O T Y P E
 *----------------------------------------------------------------------------------------
 */

IDS_STATUS
IdsSubUCode (
  IN OUT  VOID *DataPtr,
  IN OUT  AMD_CONFIG_PARAMS *StdHeader,
  IN      IDS_NV_ITEM *IdsNvPtr
  );

IDS_STATUS
IdsSubEccSymbolSize (
  IN OUT   VOID *DataPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader,
  IN       IDS_NV_ITEM *IdsNvPtr
  );

IDS_STATUS
IdsSubGangingMode (
  IN OUT   VOID *DataPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader,
  IN       IDS_NV_ITEM *IdsNvPtr
  );

IDS_STATUS
IdsSubPowerDownMode (
  IN OUT   VOID *DataPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader,
  IN       IDS_NV_ITEM *IdsNvPtr
  );

IDS_STATUS
IdsSubBurstLength32 (
  IN OUT   VOID *DataPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader,
  IN       IDS_NV_ITEM *IdsNvPtr
  );


IDS_STATUS
IdsSubAllMemClkEn (
  IN OUT   VOID *DataPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader,
  IN       IDS_NV_ITEM *IdsNvPtr
  );

IDS_STATUS
IdsSubDllShutDownSR (
  IN OUT   VOID *DataPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader,
  IN       IDS_NV_ITEM *IdsNvPtr
  );

IDS_STATUS
IdsSubHtLinkControl (
     OUT   VOID  *Data,
  IN       AMD_CONFIG_PARAMS *StdHeader,
  IN       IDS_NV_ITEM *IdsNvPtr
  );

IDS_STATUS
IdsSubPostPState (
  IN OUT   VOID *DataPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader,
  IN       IDS_NV_ITEM *IdsNvPtr
  );

IDS_STATUS
IdsSubProbeFilter (
  IN OUT   VOID *DataPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader,
  IN       IDS_NV_ITEM *IdsNvPtr
  );

AGESA_STATUS
AmdIdsCtrlInitialize (
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

IDS_STATUS
AmdIdsNvReader (
  IN      UINT16 IdsNvId,
  IN      IDS_NV_ITEM *NvTablePtr
  );

AGESA_STATUS
AmdGetIdsNvTable (
  IN OUT   VOID  **IdsNvTable,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );


AGESA_STATUS
AgesaGetIdsData  (
  IN       UINTN              Data,
  IN OUT   IDS_CALLOUT_STRUCT *IdsCalloutData
  );


AGESA_STATUS
IdsPerfTimestamp (
  IN OUT   AMD_CONFIG_PARAMS *StdHeader,
  IN       AGESA_TP TestPoint
   );

IDS_STATUS
IdsCommonReturn (
  IN OUT   VOID *DataPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader,
  IN       IDS_NV_ITEM *IdsNvPtr
  );

AGESA_STATUS
AMDSetAPMsr (
  IN       REG_MSR  *PRegMsr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

AGESA_STATUS
IdsAgesaRunFcnOnApLate  (
  IN       UINTN               ApicIdOfCore,
  IN         IDSAPLATETASK  *ApLateTaskPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

AGESA_STATUS
IdsAgesaRunFcnOnAllCoresLate  (
  IN         IDSAPLATETASK  *ApLateTaskPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

AGESA_STATUS
IdsPerfAnalyseTimestamp (
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

IDS_STATUS
IdsParseFeatTbl (
  IN       AGESA_IDS_OPTION IdsOption,
  IN       CONST IDS_FEAT_STRUCT * PIdsFeatTbl[],
  IN OUT   VOID *DataPtr,
  IN       IDS_NV_ITEM *IdsNvPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

IDS_STATUS
IdsSubPowerDownCtrl (
  IN OUT   VOID *DataPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader,
  IN       IDS_NV_ITEM *IdsNvPtr
  );

IDS_STATUS
IdsSubHdtOut (
  IN OUT   VOID *DataPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader,
  IN       IDS_NV_ITEM *IdsNvPtr
  );

UINT8
IdsGetNumPstatesFamCommon (
  IN OUT   AMD_CONFIG_PARAMS  *StdHeader
  );

VOID
IdsApRunCodeOnAllLocalCores (
  IN       AP_TASK *TaskPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );
IDS_STATUS
IdsSubTargetPstate (
  IN OUT   VOID *DataPtr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader,
  IN       IDS_NV_ITEM *IdsNvPtr
  );
#endif //_IDS_LIB_H_

