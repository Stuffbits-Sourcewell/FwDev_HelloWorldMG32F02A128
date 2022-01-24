/**
******************************************************************************
* @file    sys_tick.c
* @author  Nasreen Shaikh
* @version 01.00
* @date    30-MAR-2018
* @brief   This is a peripheral interface for Cortex M0 SysTick timer.
* 			+ SysTick_Init initializes this inbuilt timer to generate an interrupt
* 			  every 1 milisecond
* 			+ A free running timer is included which can be used as a generic
* 			  timer for time crucial functions.
*
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

/*
*******************************************************************************
*                           PRIVATE INCLUDES
*******************************************************************************
*/

#include "sys_tick.h"


/*
*******************************************************************************
*                          PRIVATE MACROS                                
*******************************************************************************
*/

#define FREE_TIMER_MAX_COUNT        	(0xFFFFFFFFUL)

//--> 3sec
#define COMM_TIMEOUT              		(50U)
#define HB_LED_TIMEOUT					(500U)

/*
*******************************************************************************
*                         PRIVATE VARIABLE DECLARATION
*******************************************************************************
*/

uint16_t hb_led_timer = HB_LED_TIMEOUT;

uint16_t communication_timer		 	= COMM_TIMEOUT;
bool_t is_communication_timeout	    	= FALSE;

static uint32_t free_running_timer = 0;

/*
*******************************************************************************
*                         PRIVATE FUNCTION DECLARATION
*******************************************************************************
*/

// None

/**
******************************************************************************
* @fn void SysTick_Init(void)
******************************************************************************
* @brief  Initialize the Hardware timer for the 1msec interval.
* @note   None
* @param  None
* @retval None
******************************************************************************
*/

void SysTick_Init(void) 
{
	uint32_t sys_clock_khz = Rcc_GetSysClkValKhz();
	(void)SysTick_Config (sys_clock_khz);
	Gpio_WriteOutPin(GPIOE ,PIN_13,DATA_OUT_LOW);
	Gpio_SetModePin(PINE(13),DATA_DIR_OUT_PP);
}// End of SysTick_Init

/**
******************************************************************************
* @fn uint32_t SysTick_GetFreeRunningTimer(void)
******************************************************************************
* @brief  Return the current value of timer.
* @note   None
* @param  None
* @retval free_running_timer: Current value of timer
******************************************************************************
*/

uint32_t SysTick_GetFreeRunningTimer(void)
{
	return(free_running_timer);
}// End of SysTick_GetFreeRunningTimer


/**
******************************************************************************
* @fn bool_t SysTick_IsTimeOutOccurred(uint32_t *prvs_timer_ptr, uint32_t timeout_period)
******************************************************************************
* @brief  This routine checks the timer variable with current timer and the updates
* 		  the status of timeout flag. In case of timer the ui_prcs timer
* 		  variable is updated with current timer for next interval.
* @note   None
* @param  None
* @retval is_time_out_occured: TRUE => If timeout occurred
  	  	  	       	   	   	   FALSE=> If no Timeout
******************************************************************************
*/

bool_t SysTick_IsTimeOutOccurred(uint32_t *prvs_timer_ptr, uint32_t timeout_period)
{
	uint32_t timer_difference = 0;
	bool_t is_time_out_occured = FALSE;
	
	timer_difference = (free_running_timer - *prvs_timer_ptr);

	if(timer_difference > timeout_period)
	{
		is_time_out_occured = TRUE;
		*prvs_timer_ptr = free_running_timer;
	}
	else
	{
		is_time_out_occured = FALSE;
	}
	
	return(is_time_out_occured);
} // End of SysTick_IsTimeOutOccurred

/**
******************************************************************************
* @fn void SysTick_Handler(void)
******************************************************************************
* @brief  SysTick_Handler of module.
*	   	  Increments the free running timer on each timer interrupt.
* @note   None
* @param  None
* @retval None
******************************************************************************
*/

void SysTick_Handler(void)
{
	//--> Increment free running timer
	free_running_timer++;

	if (0 == hb_led_timer)
	{
		hb_led_timer = HB_LED_TIMEOUT;
		Gpio_ToggleOutPin(GPIOE ,PIN_13);
	}
	else
	{
		hb_led_timer--;
	}



	if (FALSE == is_communication_timeout)
	{
		if (0 == communication_timer)
		{
			is_communication_timeout = TRUE;
		}
		else
		{
			communication_timer--;
		}
	}
}// End of Sys_TickHandler


/**
******************************************************************************
* void SysTick_ResetCommTimer(void)
******************************************************************************
* @brief   SysTick_ResetCommTimer.Called when any message is received...
* 				  by CAN.
* @note   None
* @param  None
* @retval None
******************************************************************************
*/

void SysTickDelayMsec(uint16_t msec)
{
	uint32_t timer_delay = SysTick_GetFreeRunningTimer();
	while(FALSE == SysTick_IsTimeOutOccurred(&timer_delay,msec));
}// End of SysTick_ResetCommTimer


/**
******************************************************************************
* void SysTick_ResetCommTimer(void)
******************************************************************************
* @brief   SysTick_ResetCommTimer.Called when any message is received...
* 				  by CAN.
* @note   None
* @param  None
* @retval None
******************************************************************************
*/

void SysTick_ResetCommTimer(void)
{
	is_communication_timeout = FALSE;
	communication_timer = COMM_TIMEOUT;
}// End of SysTick_ResetCommTimer


/**
******************************************************************************
* bool_t SysTick_IsCommTimeout(void)
******************************************************************************
* @brief  Getter to check timeout.
* @note   None
* @param  None
* @retval bool_t
******************************************************************************
*/

bool_t SysTick_IsCommTimeout(void)
{
	return(is_communication_timeout);
}// End of SysTick_IsCommTimeout

/*-------------------------------END OF FILE----------------------------------*/
