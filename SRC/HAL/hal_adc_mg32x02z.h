/**
******************************************************************************
* @file    hal_adc_mg32x02z.h
* @author  NGS
* @date    07-JUNE-2016
* @brief   This file contains all function prototypes of adc peripherals
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
* Change No.: 01
* Author    : NGS
* Date      : 07-JUNE-2016
* Brief     : created file
*******************************************************************************
*/
#ifndef HAL_ADC_STM32F0XX_H_
#define HAL_ADC_STM32F0XX_H_

/*
*******************************************************************************
*                              	   INCLUDES
*******************************************************************************
*/
#include "DRV/driver_adc_mg32x02z.h"
#include "std_data_types.h"
#include "DRV/driver_delay_mg32x02z.h"
#include <MG32x02z_ADC_DRV.H>


/*
*******************************************************************************
*                          PUBLIC MACROS & CONSTANTS
*******************************************************************************
*/

#define ADC_MAX_VTG						(3.3f)
#define ADC_FULL_SCALE					(1<<12)

/*
*******************************************************************************
*                         PUBLIC TYPEDEF DECLARATION                                
*******************************************************************************
*/
typedef enum
{
	ADC_IN1_SENSE			        = ADC_CHANNEL_16,
	ADC_IN2_SENSE			        = ADC_CHANNEL_17,
} sensing_channel_t;

typedef struct
{
    uint32_t adc_sum;
    uint32_t adc_avg;
    uint8_t sample_ctr;
    bool_t is_avg_calc;

} adc_db_t;

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

extern void Adc_Init (void);
extern uint16_t Adc_CalcChannelValue(ADC_ExtChannelDef adc_channel);

extern uint16_t Adc_ReadData(void);
#endif //HAL_ADC_STM32F0XX_H_

/*********************************End of File*********************************/
