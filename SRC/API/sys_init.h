/**
******************************************************************************
* @file    sys_init.h
* @author  KS
* @version 01.00
* @date    30-MAR-2015
* @brief   System Initialization file
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
* Date      : 30-MAR-2015
* Brief     : created file
*
*******************************************************************************
*/
#ifndef SYS_INIT_H_
#define SYS_INIT_H_
/*
*******************************************************************************
*                                INCLUDE FILES                                   
*******************************************************************************
*/
#include "../HAL/DRV/driver_rcc_mg32x02z.h"
#include <driver_delay_mg32x02z.h>
#include "sys_tick.h"
#include <hal_adc_mg32x02z.h>
#include <tft_interface_ST7789.h>
#include "tft_touch_interface.h"


/*
*******************************************************************************
*                          PUBLIC MACROS & CONSTANTS & CONSTANTS                                
*******************************************************************************
*/

/*
*******************************************************************************
*                         PUBLIC VARIABLE DECLARATION
*******************************************************************************
*/

/*
*******************************************************************************
*                         PUBLIC FUNCTION DECLARATION
*******************************************************************************
*/
extern void Sys_Init(void);

#endif /* SYS_INIT_H_ */
/*-------------------------------END OF FILE----------------------------------*/
