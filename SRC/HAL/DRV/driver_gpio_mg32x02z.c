/**
******************************************************************************
* @file    driver_gpio_mg32x02z.c
* @author  KS
* @version 01.00
* @date    28-MAR-2015
* @brief   This file provides firmware functions to manage the following
  *        functionalities of the GPIO peripheral:
  *        + Initialization and Configuration functions
  *        + GPIO Read and Write functions
  *        + GPIO Alternate functions configuration functions
  *        + GPIO clock enable/ disable function
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

/*
*******************************************************************************
*                               PRIVATE INCLUDES
*******************************************************************************
*/
#include <driver_gpio_mg32x02z.h>

/*
*******************************************************************************
*                               PRIVATE MACROS
*******************************************************************************
*/
//None

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
//None

/*
*******************************************************************************
*                      PRIVATE FUNCTION DECLARATION
*******************************************************************************
*/
//None

/**
*******************************************************************************
* @fn void Gpio_EnableClkAllPort(void)
*******************************************************************************
* @brief   Enables clock for all ports
* @note    None
* @param   None
* @retval  None
*******************************************************************************
*/
void Gpio_EnableClkAllPort(void)
{
	Gpio_ClockEnable(GPIOA);
	Gpio_ClockEnable(GPIOB);
	Gpio_ClockEnable(GPIOC);
	Gpio_ClockEnable(GPIOD);
	Gpio_ClockEnable(GPIOE);

}// End of Gpio_EnableClkAllPort()

/**
******************************************************************************
* @fn void Gpio_ClockEnable(GPIO_Struct* GPIOx)
******************************************************************************
* @brief   enables clock for selected GPIO Port
* @note    None
* @param   GPIOx : Select Port for which clock to be enabled
* @retval  None
******************************************************************************
*/
void Gpio_ClockEnable(GPIO_Struct* GPIOx)
{
	
	// Unprotect CSC module
	CSC->KEY.MBIT.KEY = 0xA217;
	
	CSC->AHB.W = 0x0F;
	

	if(GPIOA == GPIOx)
	{
		CSC->AHB.W |= CSC_AHB_IOPA_EN_mask_w;
	}
	else if(GPIOB == GPIOx)
	{
		CSC->AHB.W |= CSC_AHB_IOPB_EN_mask_w;
	}
	else if(GPIOC == GPIOx)
	{
		CSC->AHB.W |= CSC_AHB_IOPC_EN_mask_w;
	}
	else if(GPIOD == GPIOx)
	{
		CSC->AHB.W |= CSC_AHB_IOPD_EN_mask_w;
	}
	else if(GPIOE == GPIOx)
	{
		CSC->AHB.W |= CSC_AHB_IOPE_EN_mask_w;
	}
	else
	{
		//Invalid argument
		while(1);//Error asm("bkpt");
	}
}//End of Gpio_ClockEnable()


/**
******************************************************************************
* @fn  void Gpio_SetAltFunctionPin(Pin_Struct* GPIOx,  gpio_alt_funct_t alt_function)
******************************************************************************
* @brief   Initialize the Port IO Peripherals as per required for
* 		   the Application.
* @note    None
* @param   GPIOx 		: The GPIO port for which pin alternate function is
* 						  to be set
* @param   gpio_pin_no 	: pin number on the specified port
* @param   alt_function : alternate function as selected for the pin
* @retval  None
******************************************************************************
*/
void Gpio_SetAltFunctionPin(Pin_Struct* GPIOx, gpio_alt_funct_t alt_function)
{
	//Clear the desired bits in the register
	GPIOx->CR.MBIT.AFS &= ~0x0F;
	GPIOx->CR.MBIT.AFS |= (uint32_t)(alt_function);

}//End of Gpio_SetAltFunctionPin

/**
******************************************************************************
* @fn  void Gpio_SetModePin(Pin_Struct* GPIOx, gpio_mode_t mode)
******************************************************************************
* @brief   Set the pin as input/output/alternate function/analog
* @note    None
* @param   GPIOx 		: The GPIO port for which pin mode is to be set
* @param   gpio_pin_no 	: pin number on the specified port
* @param   mode 	    : Select desired mode for the pin
* @retval  None
******************************************************************************
*/
void Gpio_SetModePin(Pin_Struct* GPIOx, gpio_mode_t mode)
{
	//Clear the respective pin
	GPIOx->CR.MBIT.IOM &= ~((uint32_t)3);

	switch (mode)
	{
		case DATA_DIR_IN :
			GPIOx->CR.MBIT.IOM = 3;
			break;

		case DATA_DIR_OUT_OD:
			GPIOx->CR.MBIT.IOM = 1 ;
			break;

		case DATA_DIR_OUT_PP :
			GPIOx->CR.MBIT.IOM = 2 ;
			break;

		case ANALOG_MODE:
			GPIOx->CR.MBIT.IOM = 0;
			break;
	}

}//End of Gpio_SetModePin()


/**
******************************************************************************
* @fn void Gpio_WriteOutPin(GPIO_Struct* GPIOx, pin_no_t pin_no,
* 													 gpio_data_out_t out_val)
******************************************************************************
* @brief   Set the output pin as high or low
* @note    None
* @param   GPIOx   : The GPIO port for which pin output to be changed
* @param   pin_no  : pin number on the specified port
* @param   out_val : Set output pin as high or low
* @retval  None
******************************************************************************
*/
void Gpio_WriteOutPin(GPIO_Struct* GPIOx, pin_no_t pin_no, gpio_data_out_t out_val)
{

	if(DATA_OUT_LOW == out_val)
	{
		GPIOx->SC.H[1] = (1 << pin_no);
	}
	else
	{
		 GPIOx->SC.H[0] = (1 << pin_no);
	}

}//End of Gpio_WriteOutPin()

/**
******************************************************************************
* @fn  void Gpio_ToggleOutPin(GPIO_Struct* GPIOx, pin_no_t pin_no)
******************************************************************************
* @brief   Toggle the output pin
* @note    None
* @param   GPIOx  : The GPIO port for which pin to be toggled
* @param   pin_no : pin number on the specified port
* @retval  None
******************************************************************************
*/
void Gpio_ToggleOutPin(GPIO_Struct* GPIOx, pin_no_t pin_no)
{
	GPIOx->OUT.W ^= (1 << pin_no);

}//End of Gpio_ToggleOutPin()

/**
******************************************************************************
* @fn  void Gpio_WriteOutPort(GPIO_Struct* GPIOx, uint16_t out_val)
******************************************************************************
* @brief   Set the output port as given value
* @note    None
* @param   GPIOx   : Port for which output value to be changed
* @param   out_val : Port value as high or low
* @retval  None
******************************************************************************
*/
void Gpio_WriteOutPort(GPIO_Struct* GPIOx, uint16_t out_val)
{
	GPIOx->OUT.W  = out_val;

}//End of Gpio_WriteOutPort()


/**
******************************************************************************
* @fn  void Gpio_SetOutputSpeed(GPIO_Struct* GPIOx, pin_no_t pin_no,
* 												gpio_output_speed_t out_speed)
******************************************************************************
* @brief   Set the output port with  selected speed
* @note    Setting Port for lower speed helps consume less power
* @param   GPIOx      : The GPIO port for which pin speed to be changed
* @param  gpio_pin_no : pin number on the specified port
* @param  out_speed   : LOW_SPEED/MEDIUM_SPEED/HIGH_SPEED
* @retval None
******************************************************************************
*/
void Gpio_SetOutputSpeed(Pin_Struct* GPIOx, gpio_output_speed_t out_speed)
{
	GPIOx->CR.MBIT.HS |= (out_speed);

}//End of Gpio_SetOutputSpeed()

/**
******************************************************************************
* @fn void Gpio_SetPullValue(GPIO_Struct* GPIOx, pin_no_t pin_no,
* 													 gpio_pu_pd_t gpio_pu_pd)
******************************************************************************
* @brief   Set the input pin with Given configuration of Pull-up or Pull-Down
* @note    None
* @param   GPIOx      : The GPIO port for which pin alternate function is
* 						to be set
* @param  gpio_pin_no : pin number on the specified port
* @param  gpio_pu_pd  : No pull up/pull up/ pull down
* @retval None
******************************************************************************
*/
void Gpio_SetPullValue(Pin_Struct* GPIOx, gpio_pu_pd_t gpio_pu_pd)
{
	GPIOx->CR.MBIT.PU |= (gpio_pu_pd);
}//End of Gpio_SetPullValue()

/**
******************************************************************************
* @fn  uint8_t Gpio_ReadPortPin(GPIO_Struct* GPIOx, pin_no_t pin_no)
******************************************************************************
* @brief   Routine to read the pin input value
* @note    None
* @param   GPIOx     : GPIOx : The GPIO port for which pin is to be read
* @param   pin_no    : pin number on the specified port
* @retval  bit_value :  0 => if the selected pin is low
* 					    1 => if the selected pin is high
******************************************************************************
*/
uint8_t Gpio_ReadPortPin(GPIO_Struct* GPIOx, pin_no_t pin_no)
{
	uint8_t bit_value = 0;

	if(0 == (GPIOx->IN.W & (1 << pin_no )))
	{
		bit_value = 0;
	}
	else
	{
		bit_value = 1;
	}
	return(bit_value);

}//End of Gpio_ReadPortPin()

/**
******************************************************************************
* @fn uint16_t Gpio_ReadPort(GPIO_Struct* GPIOx)
******************************************************************************
* @brief   Routine to read the entire port
* @note    None
* @param   GPIOx : The GPIO port to be read
* @retval  None
******************************************************************************
*/
uint16_t Gpio_ReadPort(GPIO_Struct* GPIOx)
{
	return ((uint16_t)GPIOx->IN.W);

}//End of Gpio_ReadPort()

/*-------------------------------END OF FILE----------------------------------*/
