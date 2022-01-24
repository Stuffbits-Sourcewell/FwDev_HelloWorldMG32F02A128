/**
 ******************************************************************************
 * @file    Driver_adc_mg32x02z.c
 * @author  NGS
 * @date    31-MAR-2015
 * @brief   This Driver file provide following functionality of ADC peripheral
 * 		   Initialization ,Channel selection ,and reading adc data from selected
 * 		   channel .
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
 ******************************************************************************
 */

/*
 *******************************************************************************
 *                               PRIVATE INCLUDES
 *******************************************************************************
 */
#include <driver_adc_mg32x02z.h>

/*
 *******************************************************************************
 *                               PRIVATE DEFINES
 *******************************************************************************
 */


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




/**
 ******************************************************************************
 * @fn void Adc_ClockEnable(void)
 ******************************************************************************
 * @brief   ADC clock enable
 * @note    None
 * @param   None
 * @retval  None
 ******************************************************************************
 */
void Adc_ClockEnable(void)
{
	//-->>Enable ADC clock
	CSC->APB0.W |= CSC_APB0_ADC0_EN_mask_w;

}//End of AdcClockEnable()

/**
 ******************************************************************************
 * @fn void Adc_EnableNVICInterrupt(void)
 ******************************************************************************
 * @brief   Enabling SPI Interrupt NVIC interrupt
 * @note    None
 * @param   index : SPI1/SPI2
 * @retval  None
 ******************************************************************************
 */
void Adc_EnableNVICInterrupt(void)
{
	NVIC_EnableIRQ(ADC_IRQn);

}//Adc_EnableNVICInterrupt()

/**
 ******************************************************************************
 * @fn void Adc_SetResolution(adc_resol_t adc_resolution)
 ******************************************************************************
 * @brief   Adc_SetResolution
 * @note    None
 * @param   adc_resolution
 * @retval  None
 ******************************************************************************
 */
void Adc_SetResolution(adc_resol_t adc_resolution)
{
	ADC0->CR0.W |= (adc_resolution << 3);

}//End of Adc_SetResolution


/**
 ******************************************************************************
 * @fn void Adc_SetConvMode(adc_conv_mode_t adc_conv_mode)
 ******************************************************************************
 * @brief   Adc_SetResolution
 * @note    None
 * @param   adc_conv_mode
 * @retval  None
 ******************************************************************************
 */
void Adc_SetConvMode(adc_conv_mode_t adc_conv_mode)
{
	if(ADC_SINGLE_CONV == adc_conv_mode)
	{
		ADC0->START.W &= ~ ADC_START_CONV_MDS_mask_w ;
	}
	else
	{
		ADC0->START.W &= ~ ADC_START_CONV_MDS_mask_w ;
		ADC0->START.W |= (adc_conv_mode <<24) ;
	}

}//End of Adc_SetConvMode

/**
 ******************************************************************************
 * @fn void Adc_SetTriggerMode(adc_trig_t adc_trig)
 ******************************************************************************
 * @brief   Adc_SetResolution
 * @note    None
 * @param   adc_trig
 * @retval  None
 ******************************************************************************
 */
void Adc_SetTriggerMode(adc_trig_t adc_trig)
{
	ADC0->START.W |= ((adc_trig<< 20) & ADC_START_TRG_SEL_mask_w);

}//End of Adc_SetTriggerMode


/**
 ******************************************************************************
 * @fn void Adc_SetDataAligment(adc_data_align_t adc_data_align)
 ******************************************************************************
 * @brief   Adc_SetDataAligment
 * @note    None
 * @param   adc_data_align
 * @retval  None
 ******************************************************************************
 */
void Adc_SetDataAligment(adc_data_align_t adc_data_align)
{
	if(RIGTH_ALIGN == adc_data_align)
	{
		ADC0->CR1.W &= ~ADC_CR1_ALIGN_SEL_mask_w ;
	}
	else
	{
		ADC0->CR1.W |= ADC_CR1_ALIGN_SEL_mask_w ;
	}

}//End of Adc_SetDataAligment


/**
 ******************************************************************************
 * @fn void Adc_Enable(void)
 ******************************************************************************
 * @brief   ADC Module enable
 * @note    None
 * @param   None
 * @retval  None
 ******************************************************************************
 */
void Adc_Enable(void)
{
	//-->> ADC Enable control
	ADC0->CR0.W |= ADC_CR0_EN_enable_w ;

}//End of AdcEnable()


/**
 ******************************************************************************
 * @fn void Adc_ClockSrcConfig(adc_clk_mode_t sel_pclk_div)
 ******************************************************************************
 * @brief   ADC peripheral clk division
 * @note    None
 * @param   sel_pclk_div : Sel division factor for pclk.
 * @retval  None
 ******************************************************************************
 */
void Adc_ClockSrcConfig(adc_clk_mode_t sel_clk)
{
	ADC0->CLK.W |= (sel_clk << 8);

}//End of Adc_ClockSrcConfig()

/**
 ******************************************************************************
 * @fn void Adc_EnableChannel()(adc_channel_no_t adc_channel_no)
 ******************************************************************************
 * @brief   ADC Channel selection
 * @note    None
 * @param   adc_chanel :Select any channel from ADC_CHANEL0 to ADC_CHANEL18
 * @retval  None
 ******************************************************************************
 */
void Adc_EnableChannel(adc_channel_no_t adc_channel_no)
{
	//-->>Channel selected ADC_IN
	ADC0->MSK.W |= (1 << adc_channel_no);

}//End of Adc_EnableChannel()

/**
 ******************************************************************************
 * @fn void Adc_DisableChannel()(adc_channel_no_t adc_channel_no)
 ******************************************************************************
 * @brief   disbale the ADC Channel selection
 * @note    None
 * @param   adc_chanel :Select any channel from ADC_CHANEL0 to ADC_CHANEL18
 * @retval  None
 ******************************************************************************
 */
void Adc_DisableChannel(adc_channel_no_t adc_channel_no)
{
	//-->>Channel selected ADC_IN
	ADC0->MSK.W &= ~(1 << adc_channel_no);

}//End of Adc_DisableChannel()


/**
 ******************************************************************************
 * @fn void Adc_SetSamplingTime(adc_samp_time_t adc_samp_time)
 ******************************************************************************
 * @brief   ADC sample time
 * @note    None
 * @param   adc_samp_time_t
 * @retval  None
 ******************************************************************************
 */
void Adc_SetSamplingTime(adc_samp_time_t adc_samp_time)
{
	//-->>Set sampling rate of signal
	ADC0->ANA.W |= (adc_samp_time << 14);

}//End of Adc_SetSamplingTime


/**
 ******************************************************************************
 * @fn void Adc_SetEOCInterruptEnable(void)
 ******************************************************************************
 * @brief   Adc_SetEOCInterruptEnable
 * @note    None
 * @param   None
 * @retval  None
 ******************************************************************************
 */
void Adc_SetEOCInterruptEnable(void)
{
	ADC0->INT.W |= ADC_INT_E1CNV_IE_mask_w;
}//End of Adc_SetEOCInterruptEnable

/**
 ******************************************************************************
 * @fn void Adc_SetEOSEQInterruptEnable(void)
 ******************************************************************************
 * @brief   Adc_SetEOCInterruptEnable
 * @note    None
 * @param   None
 * @retval  None
 ******************************************************************************
 */
void Adc_SetEOSEQInterruptEnable(void)
{
	ADC0->INT.W |= ADC_INT_ESCNV_IE_mask_w;
}//End of Adc_SetEOSEQInterruptEnable


/**
 ******************************************************************************
 * @fn void Adc_StartConversion(void)
 ******************************************************************************
 * @brief   Start ADC conversion
 * @note    None
 * @param   None
 * @retval  None
 ******************************************************************************
 */
void Adc_StartConversion(void)
{
	//-->> ADC Enable control
	ADC0->START.W |= ADC_START_START_mask_w ;


}//End of AdcEnable()

/**
 ******************************************************************************
 * @fn uint32_t Adc_GetCalibrationFactor(void)
 ******************************************************************************
 * @brief   Start ADC calibration procedure
 * @note    None
 * @param   None
 * @retval  None
 ******************************************************************************
 */
void Adc_GetCalibrationFactor(void)
{
	int16_t ADC_CONV;
	uint8_t i, OFFT_ADC_MinIDX;
	uint32_t rADC_MSK, rADC_START, rADC_CR0, rADC_CR1;
	uint32_t rSUM0, rSUM1, rSUM2;

	// RESAVE
	rADC_MSK = ADC0->MSK.W;
	rADC_START = ADC0->START.W;
	rADC_CR0 = ADC0->CR0.W;
	rADC_CR1 = ADC0->CR1.W;
	rSUM0 = ADC0->SUM0.W;
	rSUM1 = ADC0->SUM1.W;
	rSUM2 = ADC0->SUM2.W;

	// reset SUM_NUM & window detect
	ADC0->CR1.W &= ~(ADC_CR1_SUM_NUM_mask_w | ADC_CR1_WIND_EN_enable_w);

	// ------------------------------------------------------------------------
	// start calibration - Offset issue
	// ------------------------------------------------------------------------
	ADC0->START.B[1] = 0x10;// select internal channel VSSA

	OFFT_ADC_MinIDX = 0;

	// ------------------------------------------------------------------------
	// 1. Scan minimum index when ADC sample not equal '0'
	// ------------------------------------------------------------------------
	while(1)
	{
		// set ADC_GAIN_OFFT
		ADC0->GAIN.MBIT.OFFT_ADC = OFFT_ADC_MinIDX;

		// sample internal VSS
		Adc_StartConversion();

		while (ADC0->STA.MBIT.E1CNVF == 0);
		ADC0->STA.W |= (ADC_STA_E1CNVF_mask_w | ADC_STA_ESMPF_mask_w);
		ADC_CONV = ADC0->DAT0.H[0];


		// check ADC_CONV data (search ADC_CONV==1 or 2)
		if (ADC_CONV == 0)
		{
			OFFT_ADC_MinIDX ++;
		}
		else
		{
			if(OFFT_ADC_MinIDX < 2)     // No trimming range in this issue
			{
				OFFT_ADC_MinIDX = 0;
				break;
			}
			OFFT_ADC_MinIDX -= 2;
			break;
		}

		//
		if (OFFT_ADC_MinIDX == 31) break;

	}

	// ------------------------------------------------------------------------
	// 2. average ADC conversion data -> decide the optimum
	// ------------------------------------------------------------------------
	while(1)
	{
		// set ADC_GAIN_OFFT
		ADC0->GAIN.MBIT.OFFT_ADC = OFFT_ADC_MinIDX;

		// Average ADC conversion


		for (i=0, ADC_CONV=0 ; i<8; i++)
		{
			// sample internal VSS
			Adc_StartConversion();

			while (ADC0->STA.MBIT.E1CNVF == 0);
			ADC0->STA.W |= (ADC_STA_E1CNVF_mask_w | ADC_STA_ESMPF_mask_w);
			ADC_CONV += ADC0->DAT0.H[0];


		}

		// check ADC_CONV data (search ADC_CONV==1 or 2)
		if (ADC_CONV == 0)
		{
			OFFT_ADC_MinIDX ++;
		}
		else if (ADC_CONV < 8)
		{
			break;
		}
		else
		{
			if(OFFT_ADC_MinIDX == 0) break;         // No trimming range in this issue
			OFFT_ADC_MinIDX --;         // make sure -> ADC can convert '0'
			break;
		}
		//
		if (OFFT_ADC_MinIDX > 31) break;

	}

	// desire ADC_GAIN_OFFT
	ADC0->GAIN.MBIT.OFFT_ADC = OFFT_ADC_MinIDX;


	// restore
	ADC0->MSK.W = rADC_MSK;
	ADC0->START.W = rADC_START;
	ADC0->CR0.W = rADC_CR0;
	ADC0->CR1.W = rADC_CR1;
	ADC0->SUM0.W = rSUM0;
	ADC0->SUM1.W = rSUM1;
	ADC0->SUM2.W = rSUM2;
}//end of Adc_GetCalibrationFactor

/*-------------------------------END OF FILE----------------------------------*/
