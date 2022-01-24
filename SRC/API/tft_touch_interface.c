/**
 ******************************************************************************
 * @file    flash_interface.c
 * @author  KS
 * @version 01.00
 * @date    30-MAR-2015
 * @brief   This file provides routines write and read to EEPROM/Flash
 * 			Memory map for data to be stored and retrieved should be defined
 * 			in header.
 * 			+ EEPROMWriteData() can be called to write the desired data at
 * 			  location defined by memory map in the EEPROM/Flash
 * 			+ EEPROMReadData() can be used to read the data from the Flash.
 ******************************************************************************
 * @attention
 * @{
 * <h2><center>&copy; Copyright 2017 StuffBits Technologies LLP </center></h2>
 *			                All rights reserved.
 * An unpublished work by Petrotec  Limited . This material contains
 * CONFIDENTIAL INFORMATION that is the property of Petrotec  Limited .
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

#include "tft_touch_interface.h"

/*
 *******************************************************************************
 *                          PRIVATE MACROS & CONSTANTS
 *******************************************************************************
 */
#define	XM_PIN							(PIN_2)
#define	XM_PORT							(GPIOA)
#define	XM_PORT_PIN						(PINA(2))
#define Y_ANA_CHAN						(ADC_ExtAIN2)

#define	YP_PIN							(PIN_3)
#define	YP_PORT							(GPIOA)
#define	YP_PORT_PIN						(PINA(3))
#define X_ANA_CHAN						(ADC_ExtAIN3)

#define	XP_PIN							(PIN_6)
#define	XP_PORT							(GPIOB)
#define	XP_PORT_PIN						(PINB(6))

#define	YM_PIN							(PIN_5)
#define	YM_PORT							(GPIOB)
#define	YM_PORT_PIN						(PINB(5))



/*
 *******************************************************************************
 *                          PRIVATE VARIABLE DECLARATION
 *******************************************************************************
 */

static point_db_t touch_value;

/*
 *******************************************************************************
 *                          PRIVATE FUNCTION DECLARATION
 *******************************************************************************
 */

static void Set_GPIO_z(void);
static void Set_GPIO_x(void);
static void Set_GPIO_y(void);
static void Set_GPIO_tft(void);

/**
 ******************************************************************************
 * @fn
 ******************************************************************************
 * @brief  Routine to read touch value. Scaling done to match 12 bit ADC with
 * 		  pixel size 240x320 .
 * 		   Upper Left corner is 0 , 0.
 * 		   Lower Right Corner is 240 , 320
 *		   XOFFSET_ADC = min(xll , xlr)
 *		   X_SCALE_FACT = (max(Xlr, Xur) - XOFFSET_ADC) /240
 *		   Y_SCALE_FACT = (max(Yul  , Yur) - YOFFSET_ADC) /320
 *
 * @note   Touch ADC readings
 *				 x     y       z
 * 			LL  463  , 384  , 2696
 * 			LR  3258  , 394 , 3221
 * 			UL  375 , 3487  , 1312
 * 			UR  3210 , 3528 , 2166
 * 			No touch z >=  4000
 * @param
 * @retval touch_value mapped to pixels
 *
 ******************************************************************************
 */

void Touch_Read(void)
{

#define XOFFSET_ADC			(450U)
#define YOFFSET_ADC			(0U)

#define X_SCALE_FACT		(11.5f)
#define Y_SCALE_FACT		(9.93f)

//#define XOFFSET_ADC			(0U)
//#define YOFFSET_ADC			(0U)
//
//#define X_SCALE_FACT		(1.0f)
//#define Y_SCALE_FACT		(1.0f)

#define Y_MAX_VALUE			(3500U)

#define KEY_DEBOUNCE_TO		(5U)
#define SAMPLING_DELAY		(500U)

	typedef enum
	{
		TOUCH_READ_INIT,
		CHK_SW_PRESSED,
		SCAN_Y_AXIS,
		SCAN_X_AXIS,
		CHK_KEY_RELEASE
	}touch_read_state_t;

	static touch_read_state_t touch_read_state = TOUCH_READ_INIT;
	uint16_t z;

	static uint8_t debounce_ctr = 0;
	static uint32_t touch_timer = 0;

	if(TRUE == SysTick_IsTimeOutOccurred(&touch_timer, 1))

	{
		switch(touch_read_state)
		{
		case TOUCH_READ_INIT:

//			Set_GPIO_z();

			touch_read_state = CHK_SW_PRESSED;

			break;

		case CHK_SW_PRESSED:

			Set_GPIO_z();
			touch_value.z = Adc_CalcChannelValue(X_ANA_CHAN);
			z = Adc_CalcChannelValue(Y_ANA_CHAN);
			touch_value.z -= z;

			if((touch_value.z < 3600) && (touch_value.z > 0))
			{
				touch_read_state = SCAN_X_AXIS;
			}
			Set_GPIO_tft();
			break;

		case SCAN_X_AXIS:
			Set_GPIO_x();
			touch_value.x = Adc_CalcChannelValue(X_ANA_CHAN) - XOFFSET_ADC;
			touch_value.x = touch_value.x/X_SCALE_FACT;
			touch_read_state = SCAN_Y_AXIS;
			Set_GPIO_tft();
			break;

		case SCAN_Y_AXIS:
			Set_GPIO_y();
			touch_value.y = Adc_CalcChannelValue(Y_ANA_CHAN) - YOFFSET_ADC;
			touch_value.y = (Y_MAX_VALUE - touch_value.y)/Y_SCALE_FACT;

			touch_read_state = CHK_KEY_RELEASE;
			Set_GPIO_tft();

			break;

		case CHK_KEY_RELEASE:
			Set_GPIO_z();
			touch_value.z = Adc_CalcChannelValue(X_ANA_CHAN);
			z = Adc_CalcChannelValue(Y_ANA_CHAN);
			touch_value.z -= z;

			if(touch_value.z < 3600)
			{
				debounce_ctr++;
			}
			else
			{
				Set_GPIO_tft();
				touch_read_state = TOUCH_READ_INIT;

				debounce_ctr = 0;
			}

			if( debounce_ctr > KEY_DEBOUNCE_TO )
			{
				touch_read_state = TOUCH_READ_INIT;
				debounce_ctr = 0;
				touch_value.key_sense = TRUE;
			}
			Set_GPIO_tft();
			break;
		}
	}
}//End of

void Set_GPIO_z(void)
{
	GPIO_PIN_OUT(XP_PORT_PIN);
	GPIO_PIN_LOW(XP_PORT, XP_PIN);

	GPIO_PIN_OUT(YM_PORT_PIN);
	GPIO_PIN_HIGH(YM_PORT, YM_PIN);

	Gpio_SetModePin(XM_PORT_PIN, ANALOG_MODE);
	Gpio_SetModePin(YP_PORT_PIN, ANALOG_MODE);
	Gpio_SetAltFunctionPin(YP_PORT_PIN , 0);
	Gpio_SetAltFunctionPin(XM_PORT_PIN , 0);

	GPIO_PIN_LOW(XM_PORT, XM_PIN);
	GPIO_PIN_LOW(YP_PORT, YP_PIN);
}

void Set_GPIO_x(void)
{
	//Set GPIO to get X axis reading.
	Gpio_SetModePin(YP_PORT_PIN, ANALOG_MODE);
	Gpio_SetAltFunctionPin(YP_PORT_PIN , 15);
	Gpio_SetAltFunctionPin(XM_PORT_PIN , 0);

	GPIO_PIN_IN(YM_PORT_PIN);
	GPIO_PIN_OUT(XM_PORT_PIN);
	GPIO_PIN_OUT(XP_PORT_PIN);
//	Gpio_SetPullValue(XP_PORT_PIN, PULL_UP);

	GPIO_PIN_HIGH(XP_PORT, XP_PIN);
	GPIO_PIN_LOW(XM_PORT, XM_PIN);

	Delay_10us(1);
}

void Set_GPIO_y(void)
{
	//Set GPIO to get Y axis reading.

	Gpio_SetModePin(XM_PORT_PIN, ANALOG_MODE);
	Gpio_SetAltFunctionPin(XM_PORT_PIN , 15);
	Gpio_SetAltFunctionPin(YP_PORT_PIN , 0);

	GPIO_PIN_IN(XP_PORT_PIN);
	GPIO_PIN_OUT(YP_PORT_PIN);
	GPIO_PIN_OUT(YM_PORT_PIN);


	GPIO_PIN_HIGH(YP_PORT, YP_PIN);
	GPIO_PIN_LOW(YM_PORT, YM_PIN);

	Delay_10us(1);
}

void Set_GPIO_tft(void)
{
	GPIO_PIN_OUT(XM_PORT_PIN);
	GPIO_PIN_OUT(XP_PORT_PIN);
	GPIO_PIN_OUT(YP_PORT_PIN);
	GPIO_PIN_OUT(YM_PORT_PIN);

	Gpio_SetAltFunctionPin(XM_PORT_PIN , 0);
	Gpio_SetAltFunctionPin(YP_PORT_PIN , 0);

}


/**
 *******************************************************************************
 * @fn  point_db_t *GetTouchValue(void)
 *******************************************************************************
 * @brief     GetTouchValue()
 * @param     None
 * @retval    None
 ********************************************************************************
 */

point_db_t *GetTouchValue(void)
{
	return(&touch_value);
}//End of GetTouchValue

/*-------------------------------END OF FILE----------------------------------*/
