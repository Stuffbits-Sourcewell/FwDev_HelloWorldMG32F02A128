/**
******************************************************************************
* @file    hal_adc_mg32x02z.c
* @author  NGS
* @date    07-JUNE-2016
* @brief   This  file contains Functions to related to configure adc using Driver
* 		   file
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
*
*******************************************************************************
*/

/*
*******************************************************************************
*                               PRIVATE INCLUDES
*******************************************************************************
*/
#include <hal_adc_mg32x02z.h>

/*
*******************************************************************************
*                          PRIVATE MACROS & CONSTANTS
*******************************************************************************
*/
#define NO_OF_ADC_CHANNEL				(2U)
#define MAX_SAMPLE_COUNT				(20U)

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



/*
*******************************************************************************
*                      PRIVATE FUNCTION DECLARATION                               
*******************************************************************************
*/


/**
******************************************************************************
* @fn  void Adc_Init (void)
******************************************************************************
* @brief   This routine Initialise the ADC peripheral
* @note    None
* @param   None
* @retval  None
*******************************************************************************
*/
void Adc_Init(void)
{
	ADC_InitTypeDef ADC_Base;
	Adc_ClockEnable();

	// make sure :

	//===Set CSC init====
	//MG32x02z_CSC_Init.h(Configuration Wizard)
	//Select CK_HS source = CK_IHRCO
	//Select IHRCO = 12M
	//Select CK_MAIN Source = CK_HS
	//Configure PLL->Select APB Prescaler = CK_MAIN/1
	//Configure Peripheral On Mode Clock->ADC = Enable
	//Configure Peripheral On Mode Clock->Port A = Enable

	//==Set GPIO init
	//MG32x02z_GPIO_Init.h(Configuration Wizard)->Use GPIOA->Pin4
	//GPIO port initial is 0xFFFF
	//Pin4 mode is AIO
	//Pin4 function GPA4

	// ------------------------------------------------------------------------
	// 1.Config ADC base parameter
	ADC_BaseStructure_Init(&ADC_Base);
	{   // modify parameter
		ADC_Base.ADCMainClockSelect = ADC_CKADC;
		ADC_Base.ADC_IntCK_Div = ADC_IntDIV4;   // for internal clock divider

		// ADC data alignment mode (Right or Left)
		ADC_Base.ADC_DataAlign = ADC_RightJustified;

		// ADC conversion resolution 8, 10 or 12 bit
		ADC_Base.ADC_ResolutionSel = ADC_12BitData;

		// ADC overwritten data or keep data
		ADC_Base.ADC_DataOverrunEvent = ADC_DataOverWritten;

	}
	ADC_Base_Init(ADC0, &ADC_Base);

	// ------------------------------------------------------------------------
	// 2.Enable ADC
	ADC_Cmd(ADC0, ENABLE);

	// ------------------------------------------------------------------------
	// 3.Config ADC Mode
	ADC_ConversionMode_Select(ADC0, ADCMode);   // one-shot
	ADC_PGA_Cmd(ADC0, DISABLE);                 // Disable PGA
	ADC_SingleDifferentMode_Select(ADC0, ADC_SingleMode);  // Single Mode

	// ------------------------------------------------------------------------
	// 4.Clear all flag
	ADC_ClearFlag(ADC0, 0xFFFFFFFF);

	// ------------------------------------------------------------------------
	// 5.Start Calibration
//	ADC_StartCalibration(ADC0, ENABLE);

	//Trigger Source select and Start conversion
	ADC_TriggerSource_Select(ADC0, ADC_START);


	//	Adc_ClockEnable();
	//
	//	Adc_ClockSrcConfig(ADC_AHB_APB_CLK);
	//
	//	Adc_SetResolution(ADC_RESOL_12BITS);
	//
	//	Adc_SetConvMode(ADC_SCAN_CONV);
	//
	//	Adc_SetTriggerMode(TRIGGER_DISABLED);
	//
	//	Adc_SetDataAligment(RIGTH_ALIGN);
	//
	//	Adc_SetSamplingTime(SAMP_TIME_30_ADCLK);
	//
	//	Adc_Enable();

}//End of Adc_Init()


/**
******************************************************************************
* @fn float Adc_CalcVddaValue(void)
******************************************************************************
* @brief   Get the actual value of  VDDA supply to IC
* @note    None
* @param   None
* @retval
******************************************************************************
*/
uint16_t Adc_CalcChannelValue(ADC_ExtChannelDef adc_channel)
{
	uint8_t loop_var;
	uint32_t adc_data = 0;

	ADC_ExternalChannel_Select(ADC0, adc_channel);

	for(loop_var = 0; loop_var < 4; loop_var++)
	{
		ADC_SoftwareConversion_Cmd(ADC0, ENABLE);
		adc_data += Adc_ReadData();
	}

	adc_data =  adc_data >> 2;

//	Adc_Disable();

//	Adc_DisableChannel(adc_channel);

	return((uint16_t)adc_data);
}// End of Adc_CalcVddaValue()

/**
******************************************************************************
* @fn uint16_t Adc_ReadData(void)
******************************************************************************
* @brief   Read the data from Selected ADC channel
* @note    None
* @param   None
* @retval  adc_data : ADC 12 bit data
******************************************************************************
*/
uint16_t Adc_ReadData(void)
{
	// ------------------------------------------------------------------------
	// 8.until E1CNVF & clear flag
	while(ADC_GetSingleFlagStatus(ADC0, ADC_E1CNVF) == 0);
	ADC_ClearFlag(ADC0, ADC_E1CNVF);

	return (uint16_t) ADC_GetDAT0Data(ADC0);
}//End of AdcReadData()

/*---------------------------------End of File-------------------------------*/
