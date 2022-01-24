/**
******************************************************************************
* @file    driver_rcc_mg32x02z.h
* @author  KS
* @version 01.00
* @date    28-MAR-2015
* @brief   This file contains all the functions prototypes of RCC module
******************************************************************************
* @attention
* @{
* <h2><center>&copy; Copyright 2017 StuffBits Technologies LLP </center></h2>
*			                All rights reserved.
* An unpublished work by Stuffbits Technologies . This material contains
* CONFIDENTIAL INFORMATION that is the property of Stuffbits Technologies .
* Any unauthorized use, duplication or disclosure is prohibited.
* @}
******************************************************************************
*/

/*
*******************************************************************************
*                               FILE HISTORY
*******************************************************************************
* Change    : 01
* Author    : KS
* Date      : 27-MAR-2015
* Brief     : created file
*
*******************************************************************************
*/
#ifndef DRIVER_RCC_STM32F0XX_H_
#define DRIVER_RCC_STM32F0XX_H_

/*
*******************************************************************************
*                              	   INCLUDES
*******************************************************************************
*/

#include <MG32x02z.h>
#include "std_data_types.h"
#include "MG32x02z_CSC.h"
#include "MG32x02z_MEM.h"
#include "MG32x02z_GPIO.h"

/*
*******************************************************************************
*                         PUBLIC MACROS & CONSTANTS
*******************************************************************************
*/
///--> XTAL Macro for XTAL_OPT selection & Don't Change the value
#define XTAL4_MHZ						(4U)
#define XTAL8_MHZ						(8U)
#define XTAL10_MHZ						(10U)
#define XTAL12_MHZ						(12U)
#define XTAL16_MHZ						(16U)

//--> PLL Macro for CLOCK_OPT selection & Don't Change the value
#define PLL12_MHZ						(12U)
#define PLL16_MHZ						(16U)
#define PLL24_MHZ						(24U)
#define PLL32_MHZ						(32U)
#define PLL40_MHZ						(40U)
#define PLL48_MHZ						(48U)

//-->> LSE 	External crystal oscillator & Don't Change the value
#define EXTAL32_KHZ						(32U)

//-->> LSI 	Internal oscillator frequency  & Don't Change the value
#define LSI40_KHZ						(40U)

//-->> HSI high speed internal oscillator & dont change the value
#define HSI8_MHZ                        (8U)


//-->> HSI high speed internal oscillator & dont change the value
#define HSI48_MHZ                        (48U)

//--> BUS Divisor Macros & Don't Change the value
#define DIVIDE_BUS_BY_1					(0U)
#define DIVIDE_BUS_BY_2					(1U)
#define DIVIDE_BUS_BY_4					(2U)
#define DIVIDE_BUS_BY_8					(3U)
#define DIVIDE_BUS_BY_16				(4U)
#define DIVIDE_BUS_BY_64				(5U)
#define DIVIDE_BUS_BY_128				(6U)
#define DIVIDE_BUS_BY_256				(7U)
#define DIVIDE_BUS_BY_512				(8U)


//-----------------------------------------------------------------------------
//low speed external oscillator
//------------------------------------------------------------------------------
#define LSE_CRYSTAL_FREQ				(EXTAL32_KHZ)
#define LSE_CLK_KHZ						(EXTAL32_KHZ)

//-----------------------------------------------------------------------------
// high speed internal oscillator
// Internal high speed oscillator has fixed frequency of 8Mhz
//------------------------------------------------------------------------------

#define HSI_INTERNAL_OSC_FREQ			(HSI8_MHZ)
#define HSI_CLK_MHz					    (HSI_INTERNAL_OSC_FREQ)

//-----------------------------------------------------------------------------
// high speed internal oscillator2
// Internal high speed oscillator has fixed frequency of 48Mhz
//------------------------------------------------------------------------------

#define HSI2_INTERNAL_OSC_FREQ			(HSI48_MHZ)
#define HSI2_CLK_MHz					(HSI_INTERNAL_OSC_FREQ)


//-----------------------------------------------------------------------------
//high speed internal oscillator
// Internal high speed oscillator has fixed frequency of 40Khz
//------------------------------------------------------------------------------

#define LSI_INTERNAL_OSC_FREQ			(LSI40_KHZ)
#define LSI_CLK_KHZ						(LSI_INTERNAL_OSC_FREQ)


//=============================================================================
//					THE FOLLOWING PARAMETERS ARE CONFIGURABLE
//=============================================================================

//Select clock source & Don't Change the value
#define INTERNAL_CLOCK                  (0U)
#define EXTERNAL_CLOCK                  (1U)

///Select Clock source here (INTERNAL_CLOCK or EXTERNAL_CLOCK)
#define SELECT_CLOCK_SOURCE 			(INTERNAL_CLOCK)



//------------------------------------------------------------------------------
//  Select the External Crystal value to be used
//  from the XTAL VALUE MACRO's.
//  (E.g. The Macro XTAL8_MHZ represents External crystal of 8MHz)
//------------------------------------------------------------------------------
///Select Crystal Here
#define EXTERNAL_CRYSTAL_FREQ			(XTAL8_MHZ)


//------------------------------------------------------------------------------
//  Select the PLL Output/Core Clock to be generated
//  from the PLL VALUE MACRO's.
//  (E.g. The Macro PLL100 represents PLL Output to be 1000MHz)
//------------------------------------------------------------------------------

///Select PLL OUTPUT here
#define SYSTEM_CLOCK_MHZ				(PLL48_MHZ)

//------------------------------------------------------------------------------
// Select the AHB pre-scaler i.e Core/AHB  clock divisor to be used
// AHB clock = System clock / AHB_Prescaler
//------------------------------------------------------------------------------

//selects AHB clock divisor here
#define AHB_CLOCK_DIVISOR				(DIVIDE_BUS_BY_1)


//------------------------------------------------------------------------------
//  Select the APB_prescaler i.e Peripheral/ Bus clock divisor to be used
//  Peripheral clock = AHB clock/APB_prescaler
//  APB Bus Divisor range supports only Up to divide by 16
//------------------------------------------------------------------------------

//selects  APB clock divisor here
#define APB_CLOCK_DIVISOR				(DIVIDE_BUS_BY_1)


#define RCC_USBCLK_HSI48                 ((uint32_t)0x00000000)
#define RCC_USBCLK_PLLCLK                RCC_CFGR3_USBSW

/*
*******************************************************************************
*                         PUBLIC TYPEDEF DECLARATION
*******************************************************************************
*/
//None

/*
*******************************************************************************
*                        PUBLIC VARIABLE DECLARATION
*******************************************************************************
*/
//None

/*
*******************************************************************************
*                        PUBLIC FUNCTION DECLARATION
*******************************************************************************
*/
extern void Rcc_ClockInit(void);
extern void Rcc_RestoreClockPLL(void);

extern uint32_t Rcc_GetSysClkValKhz(void);
extern uint32_t Rcc_GetAhbClkValKhz(void);
extern uint32_t Rcc_GetPclkValKhz(void);

#endif //DRIVER_RCC_STM32F0XX_H_

/*-------------------------------END OF FILE----------------------------------*/
