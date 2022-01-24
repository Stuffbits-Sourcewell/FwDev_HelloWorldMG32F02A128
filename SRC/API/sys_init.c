/**
******************************************************************************
* @file    sys_init.c
* @author  KS
* @version 01.00
* @date    30-MAR-2015
* @brief   System Initialization file
*  	       + Initialization / configuration of all hardware modules is done
*  	     	 in this file.
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


/*
*******************************************************************************
*                                INCLUDE FILES
*******************************************************************************
*/

#include "sys_init.h"


/*
*******************************************************************************
*                          PRIVATE MACROS & CONSTANTS
*******************************************************************************
*/
// None


/*
*******************************************************************************
*                         PRIVATE VARIABLE DECLARATION
*******************************************************************************
*/
// None


/*
*******************************************************************************
*                         PRIVATE FUNCTION DECLARATION
*******************************************************************************
*/

/**
 ******************************************************************************
 * @fn
 ******************************************************************************
 * @brief :
 * @NOTE  :
 * @param : void
 * @retval: void
 ******************************************************************************
 */

void Ui_Init(void)
{
	TFT_Init();

	Adc_Init();

	Set_ScreenDir(VERTICAL_SCREEN);//VERTICAL_1_SCREEN

	fillRect(0, 0, Get_Width(), Get_Height(), COLOUR_BLACK);

}//End of Ui_Init

/**
******************************************************************************
* @fn void Sys_Init(void)
******************************************************************************
* @brief  System initialisation function.
* @note   None
* @param  None
* @retval None
******************************************************************************
*/
void Sys_Init(void)
{
	Rcc_ClockInit();

	Gpio_EnableClkAllPort();

	Delay_Init();

	Delay_10ms(1);

	SysTick_Init();

	Ui_Init();

}// End of Sys_Init



/*-------------------------------END OF FILE----------------------------------*/
