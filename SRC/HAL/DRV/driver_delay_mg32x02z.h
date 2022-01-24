/**
******************************************************************************
* @file    driver_delay_mg32x02z.h
* @author  KS
* @version 01.00
* @date    31-MAR-2015
* @brief   This file contains all the functions prototypes for the
* 		   Microcontroller Delay.
*
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
* Date      : 31-MAR-2015
* Brief     : created file
*
*******************************************************************************
*/

#ifndef DRIVER_DELAY_STM32F0XX_H_
#define DRIVER_DELAY_STM32F0XX_H_


/**
*******************************************************************************
*                                PRIVATE INCLUDES                                   
*******************************************************************************
*/
#include "std_data_types.h"
#include "stdlib.h"

#include "driver_rcc_mg32x02z.h"
#include "system_MG32x02z.h"


/*
*******************************************************************************
*                         PUBLIC MACROS & CONSTANTS
*******************************************************************************
*/
#define DELAY_CORE_CLOCK               (SYSTEM_CLOCK_MHZ)


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
extern void Delay_Init(void);

extern void Delay_10us(uint16_t us10);
extern void Delay_10ms(uint16_t ms10);

#endif //DRIVER_DELAY_STM32F0XX_H_

/*-------------------------------END OF FILE----------------------------------*/
