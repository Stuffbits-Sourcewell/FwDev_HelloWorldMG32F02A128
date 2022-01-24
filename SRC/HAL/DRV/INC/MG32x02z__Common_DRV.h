/**
 ******************************************************************************
 *
 * @file        MG32x02z__Common_DRV.h
 *
 * @brief       This is the C code format driver head file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.14
 * @date        2019/04/15
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par 		Disclaimer 
 *		The Demo software is provided "AS IS"  without any warranty, either 
 *		expressed or implied, including, but not limited to, the implied warranties 
 *		of merchantability and fitness for a particular purpose.  The author will 
 *		not be liable for any special, incidental, consequential or indirect 
 *		damages due to loss of data or any other reason. 
 *		These statements agree with the world wide and local dictated laws about 
 *		authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */ 



#ifndef _MG32x02z_Common_DRV_H
#define _MG32x02z_Common_DRV_H
#define _MG32x02z_Common_DRV_H_VER                            0.1      /*!< File Version */

#ifdef __cplusplus
 extern "C" {
#endif


#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "MG32x02z.h"



     // Debug Configuration Setting
#define MG_Debug	1				/*!< 0=Normal, 1=Debug for Test Chip    */


/**
 * @enum		DRV_Return
 * @brief		General Driver return status
 */
typedef enum 
{
    /* common status values */
    DRV_Logic0 = 0,             /*!<                                    */
    DRV_Logic1 = 1,             /*!< operation failed					*/
    DRV_Low = 0,                /*!< operation failed					*/
    DRV_High = 1,               /*!< operation failed					*/
    DRV_Normal = 0,             /*!< operation failed					*/
    DRV_UnHappened = 0,         /*!< operation failed					*/
    DRV_Happened = 1,           /*!< operation failed					*/
    DRV_Success = 0,            /*!< successful outcome					*/
    DRV_Failure = 1,            /*!< operation failed					*/
    DRV_False = 0,              /*!<                                    */
    DRV_True = !DRV_False,      /*!<                                    */
    DRV_Unready = 0,            /*!<                                    */
    DRV_Ready = !DRV_Unready,   /*!<                                    */

    /* For PW module */
    PW_HighThreshold = 0,
    PW_LowThreshold = 1,
    PW_None = 0,
    PW_Sleep = 1,
    PW_Stop = 2,    

    DRV_Completed,              /*!< operation failed					*/
    DRV_TimeOut,                /*!< operation failed					*/
    DRV_OverRange,
    DRV_OutsideLow,
    DRV_OutsideHigh,
    DRV_Inside,
    DRV_Busy,                   /*!<                                    */
    DRV_OverFlow,               /*!<                                    */
    DRV_UnderFlow,              /*!<                                    */
//	DRV_ERR_INVALID_HANDLE,		/*!< invalid handle						*/
//	DRV_ERR_INVALID_ID,			/*!< invalid identifier					*/
//	DRV_ERR_INVALID_PARAM,		/*!< invalid parameter					*/
//	DRV_ERR_INVALID_OP,			/*!< requested operation is invalid		*/
//	DRV_ERR_MEMORY_ALLOC,		/*!< problem allocating memory			*/
//	DRV_ERR_MEMORY_SIZE,		/*!< problem with the size of memory	*/
//	DRV_ERR_RESOURCE_UNAVAILABLE,
//	DRV_ERR_TIMEOUT,			/*!< timeout							*/
//	DRV_ERR_MAX					/*!< Max error number*/

//	DRV_WARN_NO_ACTION,			/* < the function completed successfully,*/
	                                /* < but no action was taken            */
//	DRV_WARN_PARAM_CLIPPED,		/*!< the function has completed			*/
//									/*!< successfully, though a parameter was	*/
//									/*!< clipped to within a valid range.		*/
//	DRV_WARN_BUFFER_EMPTY,
//	DRV_WARN_BUFFER_FULL,
//	DRV_WARN_UNINITED,			/*!< driver has not been initialized yet */
//	DRV_WARN_INITED,			/*!< driver has been initialized already */

}DRV_Return;           /*!< Driver Return Status Definitions */



/**
 * @enum		Protect_Type
 * @brief		TMx interrupt enable source  
 */
typedef enum { 
    RSTprotect = (uint32_t)0x4C00000C,
    CSCprotect = (uint32_t)0x4C01000C,  
    PWprotect = (uint32_t)0x4C02000C,
    MEMprotect = (uint32_t)0x4D00000C,  
    MEMsprotect = (uint32_t)0x4D00000E,
    CFGprotect = (uint32_t)0x4FF0000C,
    IWDTprotect = (uint32_t)0x5D00000C,  
    WWDTprotect = (uint32_t)0x5D01000C,  
    RTCprotect = (uint32_t)0x5D04000C,
}Protect_Type;          /*!< Definitions for protection function */




/**
 * @enum		Lock_Type
 * @brief		Lock Module. 
 */
typedef enum{
    RSTLock = (uint32_t)0x4C00000E,
    IWDTLock = (uint32_t)0x5D00000E,  
    RTCLock = (uint32_t)0x5D04000E,
}Lock_Type;             /*!< Definitions for locked function */



#if defined(IRQHandler_Middleware_Level_)
  #define InitTick(__TickClock__, __TickPriority__) MID_InitTick(__TickPriority__)
  #define Delay         MID_Delay
  #define GetTick       MID_GetTick
  #define SuspendTick   MID_SuspendTick
  #define ResumeTick    MID_ResumeTick
#else
  DRV_Return InitTick(uint32_t TickClock, uint32_t TickPriority);
  void IncTick(void);
  void Delay(__IO uint32_t DelayTime);
  uint32_t GetTick(void);
  void SuspendTick(void);
  void ResumeTick(void);
#endif

DRV_Return ProtectModuleReg(Protect_Type Module);             /*!< Protect Module Register Write */
DRV_Return UnProtectModuleReg(Protect_Type Module);           /*!< UnProtect Module Register Write */
DRV_Return LockModuleReg(Lock_Type Module);                   /*!< Lock Module Register Write until Chip Reset */

#ifdef __cplusplus
}
#endif

#endif


