/**
******************************************************************************
* @file    sys_tick.h
* @author  Nasreen Shaikh
* @version 01.00
* @date    30-MAR-2018
* @brief   This file has function prototypes to use the SYSTICK timer of
* 			Cortex M0 Devices
******************************************************************************
* @attention
* @{
* <h2><center>&copy; Copyright 2017 Stuffbits Technologies </center></h2>
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
* Author    : Nasreen Shaikh
* Date      : 30-MAR-2018
* Brief     : created file
*
*******************************************************************************
*/

#ifndef SYS_TICK_H_
#define SYS_TICK_H_

                                                
/*
*******************************************************************************
*                          INCLUDES
*******************************************************************************
*/

#include "../HAL/DRV/driver_rcc_mg32x02z.h"
#include "std_data_types.h"
#include <driver_gpio_mg32x02z.h>

/*
*******************************************************************************
*                          PUBLIC MACROS & CONSTANTS                                
*******************************************************************************
*/

//None


/*
*******************************************************************************
*                         PUBLIC VARIABLE DECLARATION
*******************************************************************************
*/

// None


/*
*******************************************************************************
*                         PUBLIC FUNCTION DECLARATION
*******************************************************************************
*/

extern void SysTick_Init(void);

extern uint32_t SysTick_GetFreeRunningTimer(void);
extern bool_t SysTick_IsTimeOutOccurred(uint32_t *prvs_timer_ptr, uint32_t timeout_period);

extern void SysTick_SetErrLEDTimeout(uint16_t error_led_timeout);

extern void SysTick_ResetCommTimer(void);
extern bool_t SysTick_IsCommTimeout(void);

extern void SysTickDelayMsec(uint16_t msec);

#endif /* SYS_TICK_H_ */
/*-------------------------------END OF FILE----------------------------------*/
