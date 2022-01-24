/**
 ******************************************************************************
 * @file    driver_delay_mg32x02z.c
 * @author  KS
 * @version 01.00
 * @date    31-MAR-2015
 * @brief   Routine for 10microsec and 10millisec delay
 *  		   + This routine is not dependent on the microcontroller.
 *  		   + It is Common for all ARM controllers with CortexM0 core
 *  		   + The syntax is GCC compliant. And can be compiled using
 *  		   any IDE with GCC compiler.
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

/*
 *******************************************************************************
 *                                PRIVATE INCLUDES
 *******************************************************************************
 */
#include <driver_delay_mg32x02z.h>

/*
 *******************************************************************************
 *                               PRIVATE MACROS
 *******************************************************************************
 */
//NONE

/*
 *******************************************************************************
 *                       PRIVATE TYPEDEFS DECLARATION
 *******************************************************************************
 */
//None

/*
 *******************************************************************************
 *                       PRIVATE VARIABLE DECLARATION
 *******************************************************************************
 */

static uint32_t delay_count_us = 0;
static uint32_t delay_count_ms = 0;

/*
 *******************************************************************************
 *                      PRIVATE FUNCTION DECLARATION
 *******************************************************************************
 */
//None

/**
 ******************************************************************************
 * @fn  void Delay_Init(void)
 ******************************************************************************
 * @brief   This routine calculates cycle count required for delay of us and ms .
 * @note    None
 * @param   None
 * @retval  None
 ******************************************************************************
 */
void Delay_Init(void)
{
#define MEGAHERTZ_CONV_FACT    			(1000000U)
	uint32_t sys_core_clk_mhz=48;

	sys_core_clk_mhz =( SystemCoreClock/MEGAHERTZ_CONV_FACT);
	delay_count_us = (sys_core_clk_mhz * 10 )/4;
	delay_count_ms = (delay_count_us * 1000);

}//End of Delay_Init()


/**
 ******************************************************************************
 * @fn  void Delay_10us(const volatile uint16_t us10)
 ******************************************************************************
 * @brief   The delay_count_us has been calculated as follows
 * 		   Time_period of one cycle = 1/core_clk_freq
 *   	   10microsec=[delay_count(3+1)*Time_period]+(3+1+1+1)*Time_period
 * @note    The overall delay used should be less than the Watchdog Timeout.
 * 		   Do Not remove the Volatile qualifier
 * @param   us10 : Multiple count of 10 micro second
 * @retval  None
 ******************************************************************************
 */
void Delay_10us(const volatile uint16_t us10)
{
	uint32_t ctr = 0;
	uint32_t ctr1 = 0;

	for(ctr1 = 0 ; ctr1 < us10 ; ctr1++)
	{
		for(ctr = 0 ; ctr < delay_count_us ; ctr++)
		{
			__NOP();
		}
	}

}//End of Delay_10us()


/**
 ******************************************************************************
 * @fn  void Delay_10ms(const volatile uint16_t ms10)
 ******************************************************************************
 * @brief   The delay_count_us has been calculated as follows
 * 		   Time_period of one cycle = 1/core_clk_freq
 *   	   10milisec=[delay_count(2+1)*Time_period]+(2+1+1+1)*Time_period
 * @note    The overall delay used should be less than the Watchdog Timeout.
 * 		   Do Not remove the Volatile qualifier
 * @param   ms10 : Multiple count of 10 milli second
 * @retval  None
 ******************************************************************************
 */

void Delay_10ms(const volatile uint16_t ms10)
{
	uint32_t ctr = 0;
	uint32_t ctr1 = 0;

	for(ctr1 = 0 ; ctr1 < ms10 ; ctr1++)
	{
		for(ctr = 0 ; ctr < delay_count_ms ; ctr++)
		{
			__NOP();
		}
	}

}// End of Delay_10ms()

/*-------------------------------END OF FILE----------------------------------*/
