/**
******************************************************************************
* @file    driver_gpio_mg32x02z.h
* @author  KS
* @version 01.00
* @date    30-MARCH-2013
* @brief   This file contains all the functions prototypes for the GPIO
  *        firmware library.
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
* Date      : 28-MAR-2015
* Brief     : created file
*
*******************************************************************************
*/
#ifndef DRIVER_GPIO_STM32F0XX_H_
#define DRIVER_GPIO_STM32F0XX_H_

/*
*******************************************************************************
*                                PRIVATE INCLUDES
*******************************************************************************
*/
#include "driver_rcc_mg32x02z.h"
#include "std_data_types.h"
#include "MG32x02z_CSC.h"
#include "MG32x02z_GPIO.h"


/*
*******************************************************************************
*                         PUBLIC MACROS & CONSTANTS
*******************************************************************************
*/
#define GPIO_PIN_MASK						(31U)

/*
*******************************************************************************
*                         PUBLIC TYPEDEF DECLARATION
*******************************************************************************
*/
typedef enum
{
	ALT_FUNCTION_0,
	ALT_FUNCTION_1,
	ALT_FUNCTION_2,
	ALT_FUNCTION_3,
	ALT_FUNCTION_4,
	ALT_FUNCTION_5,
	ALT_FUNCTION_6,
	ALT_FUNCTION_7,
	ALT_FUNCTION_8,
	ALT_FUNCTION_9,
	ALT_FUNCTION_10,
	ALT_FUNCTION_11,
	ALT_FUNCTION_12,
	ALT_FUNCTION_13,
	ALT_FUNCTION_14,
	ALT_FUNCTION_15

}gpio_alt_funct_t;

typedef enum
{
	PIN_0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8,
	PIN_9,
	PIN_10,
	PIN_11,
	PIN_12,
	PIN_13,
	PIN_14,
	PIN_15
}pin_no_t;

typedef enum
{
	ANALOG_MODE,
	DATA_DIR_OUT_OD,
	DATA_DIR_OUT_PP,
	DATA_DIR_IN,
}gpio_mode_t;

typedef enum
{
	DATA_OUT_LOW,
	DATA_OUT_HIGH
}gpio_data_out_t;

typedef enum
{
	LOW_SPEED,
	HIGH_SPEED
}gpio_output_speed_t;

typedef enum
{
	NO_PULL,
	PULL_UP,
}gpio_pu_pd_t;

/*
*******************************************************************************
*                        PUBLIC VARIABLE DECLARATION
*******************************************************************************
*/

#define GPIO_PIN_HIGH(x,y)				Gpio_WriteOutPin(x, y, DATA_OUT_HIGH)
#define GPIO_PIN_LOW(x,y)				Gpio_WriteOutPin(x, y, DATA_OUT_LOW)
#define GPIO_PIN_OUT(x)					Gpio_SetModePin(x,DATA_DIR_OUT_PP)
#define GPIO_PIN_IN(x)					Gpio_SetModePin(x, DATA_DIR_IN);


/*
*******************************************************************************
*                        PUBLIC FUNCTION DECLARATION
*******************************************************************************
*/
//Routines to enable/disable port clock
extern void Gpio_EnableClkAllPort(void);

extern void Gpio_ClockEnable(GPIO_Struct* GPIOx);
extern void Gpio_ClockDisable(GPIO_Struct* GPIOx);

//Routines for MODER register
extern void Gpio_SetAltFunctionPin(Pin_Struct* GPIOx, gpio_alt_funct_t alt_function);

extern void Gpio_SetModePin(Pin_Struct* GPIOx,  gpio_mode_t mode);

//Routines for OSPEEDR  register
extern void Gpio_SetOutputSpeed(Pin_Struct* GPIOx, gpio_output_speed_t out_speed);

//Routines for PUPDR  register
extern void Gpio_SetPullValue(Pin_Struct* GPIOx, gpio_pu_pd_t gpio_pu_pd);

//Routines for ODR register
extern void Gpio_WriteOutPin(GPIO_Struct* GPIOx, pin_no_t pin_no, gpio_data_out_t out_val);
extern void Gpio_ToggleOutPin(GPIO_Struct* GPIOx, uint8_t pin_no);
extern void Gpio_WriteOutPort(GPIO_Struct* GPIOx,  uint16_t out_val);

//Routines for IDR register
extern uint8_t Gpio_ReadPortPin(GPIO_Struct* GPIOx, pin_no_t pin_no);
extern uint16_t Gpio_ReadPort(GPIO_Struct* GPIOx);

#endif // DRIVER_GPIO_STM32F0XX_H_

/*-------------------------------END OF FILE----------------------------------*/
