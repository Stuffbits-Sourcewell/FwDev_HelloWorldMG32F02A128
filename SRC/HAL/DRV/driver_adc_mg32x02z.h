/**
******************************************************************************
* @file    Driver_adc_mg32x02z.h
* @author  NGS
* @date    31-MAR-2015
* @brief   This file contains all the functions prototypes of ADC
* 		   Peripheral.
******************************************************************************
* @attention
* @{
* <h2><center>&copy; Copyright 2015 SpryLogic Technologies </center></h2>
*			                All rights reserved.
* An unpublished work by Sprylogic Technologies Limited. This material contains
* CONFIDENTIAL INFORMATION that is the property of Sprylogic Technologies Limited.
* Any unauthorized use, duplication or disclosure is prohibited.
* @}
******************************************************************************
*/

/*
*******************************************************************************
*                               FILE HISTORY
*******************************************************************************
* Change    : 01
* Author    : NGS
* Date      : 31-MAR-2015
* Brief     : created file
*
*******************************************************************************
*/
#ifndef DRIVER_ADC_SYM32F0XX_H_
#define DRIVER_ADC_SYM32F0XX_H_

/*
*******************************************************************************
*                              	   INCLUDES
*******************************************************************************
*/
#include <MG32x02z.h>
#include "stdlib.h"
#include "std_data_types.h"
#include "MG32x02z_CSC.h"
#include "MG32x02z_ADC.h"

/*
*******************************************************************************
*                               PUBLIC DEFINES
*******************************************************************************
*/
#define ADC_RESOLUTION					(4096U)

/*
*******************************************************************************
*                               PUBLIC MACROS
*******************************************************************************
*/

/* Temperature sensor calibration value address */
#define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7B8))
#define AVG_SLOPE (5.336f) //AVG_SLOPE in ADC conversion step (@3.3V)/�C multiplied by 1000 for precision on the division


/*
*******************************************************************************
*                         PUBLIC TYPEDEF DECLARATION
*******************************************************************************
*/
typedef enum
{
	ADC_CHANNEL_0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
	ADC_CHANNEL_8,
	ADC_CHANNEL_9,
	ADC_CHANNEL_10,
	ADC_CHANNEL_11,
	ADC_CHANNEL_12,
	ADC_CHANNEL_13,
	ADC_CHANNEL_14,
	ADC_CHANNEL_15,
	ADC_CHANNEL_16,
	ADC_CHANNEL_17,
	ADC_CHANNEL_18

}adc_channel_no_t;

typedef enum
{
	ADC_AHB_APB_CLK,
	ADC_PLL_CLK,
	ADC_TM00_TRGO_CLK,
	ADC_TM01_TRGO_CLK,
}adc_clk_mode_t;

typedef enum
{
	ADC_RESOL_12BITS,
	ADC_RESOL_10BITS,
	ADC_RESOL_8BITS,
}adc_resol_t;

typedef enum
{
	ADC_SINGLE_CONV,
	ADC_SCAN_CONV,
	ADC_LOOP_CONV,
}adc_conv_mode_t;

typedef enum
{
	TRIGGER_DISABLED,
	TRIGGER_RISING_EDGE,
	TRIGGER_FALLING_EDGE,
	TRIGGER_BOTH_EDGE
}adc_trig_t;

typedef enum
{
	RIGTH_ALIGN,
	LEFT_ALIGN
}adc_data_align_t;


typedef enum
{
	SAMP_TIME_24_ADCLK,
	SAMP_TIME_30_ADCLK,
}adc_samp_time_t;

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
extern  void Adc_ClockEnable(void);

extern void Adc_EnableNVICInterrupt(void);

extern void Adc_SetResolution(adc_resol_t adc_resolution);
extern void Adc_SetConvMode(adc_conv_mode_t adc_conv_mode);
extern void Adc_SetTriggerMode(adc_trig_t adc_trig);

extern void Adc_SetDataAligment(adc_data_align_t adc_data_align);
extern void Adc_GetCalibrationFactor(void);

extern void Adc_Enable(void);

extern void Adc_ClockSrcConfig(adc_clk_mode_t sel_clk);
extern void Adc_EnableChannel(adc_channel_no_t adc_channel_no);
extern void Adc_DisableChannel(adc_channel_no_t adc_channel_no);

extern void Adc_SetSamplingTime(adc_samp_time_t adc_samp_time);

extern void Adc_SetEOCInterruptEnable(void);
extern void Adc_SetEOSEQInterruptEnable(void);

extern void Adc_StartConversion(void);

#endif // DRIVER_ADC_SYM32F0XX_H_

/*-------------------------------END OF FILE----------------------------------*/
