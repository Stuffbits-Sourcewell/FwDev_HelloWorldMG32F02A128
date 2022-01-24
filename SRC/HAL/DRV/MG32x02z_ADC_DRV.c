/**
 ******************************************************************************
 *
 * @file        MG32x02z_ADC_DRV.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the ADC peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.17
 * @date        2020/04/23
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2016 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par 		Disclaimer 
 *		The Demo software is provided "AS IS"  without any warranty, either 
 *		expressed or implied, including, but not limited to, the implied warranties 
 *		of merchantability and fitness for a particular purpose.  The author will 
 *		not be liable for any special, incidental, consequential or indirect 
 *		damages due to loss of data or any other reason. 
 *		These statements agree with the world wide and local dictated laws about 
 *		authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */ 


#include "MG32x02z_ADC_DRV.H"




/**
 * @brief  	simple define
 *
 */ 

/**
 * @name	Deinitial ADC to default condition
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Deinitializes the ADCx peripheral registers to their default reset 
 *			    values.
 * @details     Reset ADCx to default configuration
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return		No
 * @note 
 * @par         Example
 * @code
    ADC_DeInit(ADC0);
 * @endcode
 *******************************************************************************
 */
void ADC_DeInit(ADC_Struct *ADCx)
{
    ADCx->INT.W = 0x00000000;
    ADCx->CLK.W = 0x00000000;
    ADCx->CR0.W = 0x00000000;
    ADCx->CR1.W = 0x00000000;
    ADCx->MSK.W = 0x00000000;
    ADCx->START.W = 0x00001000;
#if (MG32_1ST)	
    ADCx->ANA.W = 0x00008000;
#endif
#if (MG32_2ND)
    ADCx->ANA.W = 0x00000300;
#endif
    // CAL
    ADCx->GAIN.W = 0x00000000;
    ADCx->SUM0.W = 0x00E00000;
    ADCx->SUM1.W = 0x00E00000;
    ADCx->SUM2.W = 0x00E00000;
    // TCAL
    ADCx->DAT0.B[2] = 0xC0;
    
    ADCx->STA.W = 0xFFFFFFFF;
}
///@}


/**
 * @name	Initializes the ADC Unit peripheral according to the specified\
 *          parameters in the ADC_InitTypeDef.
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Fills each ADC_InitTypeDef member with its default value.
 * @param[in]   ADC_BaseInitStruct : pointer to a ADC_InitTypeDef
 *        	    structure which will be initialized.
 * @return		No
 * @note 
 * @par         Example
 * @code
    ADC_InitTypeDef ADC_BaseInitStruct;

    ADC_BaseStructure_Init(&ADC_BaseInitStruct);
 * @endcode
 *******************************************************************************
 */
 void ADC_BaseStructure_Init(ADC_InitTypeDef* ADC_BaseInitStruct)
{
    // config ADC clock 
    ADC_BaseInitStruct->ADCMainClockSelect = ADC_CKADC;
        ADC_BaseInitStruct->ADC_IntCK_Div = ADC_IntDIV16;   // for internal clock divider
        ADC_BaseInitStruct->ADC_CKPLL_Div = ADC_PLLDIV6;    // only for clock select PLL     
    
    // ADC data alignment mode (Right or Left)
    ADC_BaseInitStruct->ADC_DataAlign = ADC_RightJustified;
    
    // ADC conversion resolution 10 or 12 bit
    ADC_BaseInitStruct->ADC_ResolutionSel = ADC_12BitData;
    
    // ADC overwritten data or keep data
    ADC_BaseInitStruct->ADC_DataOverrunEvent = ADC_DataOverWritten;
    
}

/**
 *******************************************************************************
 * @brief       Initializes the ADC peripheral according to 
 *			    the specified parameters in the ADC_BaseInitStruct.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in]   ADC_BaseInitStruct : pointer to a ADC_InitTypeDef
 *        	    structure that contains the configuration information for
 *        	    the specified ADC peripheral.
 * @return		No
 * @note 
 * @par         Example
 * @code
    ADC_InitTypeDef ADC_BaseInitStruct;
 
    ADC_Base_Init(ADC0, &ADC_BaseInitStruct);
 * @endcode
 *******************************************************************************
 */
void ADC_Base_Init(ADC_Struct* ADCx, ADC_InitTypeDef* ADC_BaseInitStruct)
{
    // config clock
    ADC_ClockSource_Select(ADCx, ADC_BaseInitStruct->ADCMainClockSelect);
        ADC_SetInternalClockDivider(ADCx, ADC_BaseInitStruct->ADC_IntCK_Div);
        ADC_SetPLLClockDivider(ADCx, ADC_BaseInitStruct->ADC_CKPLL_Div);
    
    // ADC data alignment
    ADC_DataAlignment_Select(ADCx, ADC_BaseInitStruct->ADC_DataAlign);
    
    // ADC conversion resolution
    ADC_DataResolution_Select(ADCx, ADC_BaseInitStruct->ADC_ResolutionSel);
    
    // ADC data overwritten or keep mode
    ADC_DataOverrunMode_Select(ADCx, ADC_BaseInitStruct->ADC_DataOverrunEvent);
    
    ADCx->CR0.W |= ADC_CR0_CH_CHG_mask_w;

    #if (MG32_2ND)
        ADCx->ANA.W |= 0x00000300;
    #endif
}
///@}



/** 
 * @name		Config ADC clock 
 *
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Configures the ADCx counter direction.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	PLLClockDIV : specifies the PLL clock divider
 *  @arg\b	    ADC_PLLDIV2 : divided by 2
 *  @arg\b	    ADC_PLLDIV4 : divided by 4
 *  @arg\b	    ADC_PLLDIV5 : divided by 5
 *  @arg\b	    ADC_PLLDIV6 : divided by 6
 * @return		No
 * @note 
 * @par         Example
 * @code
    ADC_SetPLLClockDivider(ADC0, ADC_PLLDIV6);
 * @endcode
 *******************************************************************************
 */
void ADC_SetPLLClockDivider(ADC_Struct* ADCx, ADC_PLLClockDivDef PLLClockDIV)
{
	ADCx->CLK.MBIT.CK_DIV2 = PLLClockDIV;
}

/**
 *******************************************************************************
 * @brief	    Configures ADC clock source
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCClockSrc : specifies the Main Counter direction to be used
 *  @arg\b	    ADC_CKADC : ADC clock from CK_ADC
 *  @arg\b	    ADC_CKPLL : ADC clock from PLL 
 *  @arg\b	    ADC_TM00TRGO : ADC clock from TM00 TRGO
 *  @arg\b	    ADC_TM01TRGO : ADC clock from TM01 TRGO
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ClockSource_Select(ADC0, ADC_CKADC);
 * @endcode
 *******************************************************************************
 */
void ADC_ClockSource_Select(ADC_Struct* ADCx, ADC_ClockSourceDef ADCClockSrc)
{
	ADCx->CLK.MBIT.CK_SEL2 = ADCClockSrc;
}
/**
 *******************************************************************************
 * @brief	    Configures ADC internal clock input divider.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	INTClockSrc : specifies the ADC inteernal clock divider
 *  @arg\b	    ADC_IntDIV1 : divided by 1
 *	@arg\b	    ADC_IntDIV2 : divided by 2
 *  @arg\b	    ADC_IntDIV4 : divided by 4
 *	@arg\b	    ADC_IntDIV16 : divided by 16
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetInternalClockDivider(ADC0, ADC_IntDIV2);
 * @endcode
 *******************************************************************************
 */
void ADC_SetInternalClockDivider(ADC_Struct* ADCx, ADC_INTClockDivDef INTClockSrc)
{
	ADCx->CLK.MBIT.CK_DIV = INTClockSrc;
}
///@}



/**
 * @name	Config window detect function routine
 *   		
 */ 
///@{ 
// Config window detect function routine
/**
 *******************************************************************************
 * @brief	    Configures lower threshold of window detect function
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	LThreshold: setting lower threshold
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetLowerThreshold(ADC0, 100);
 * @endcode
 *******************************************************************************
 */
void ADC_SetLowerThreshold(ADC_Struct* ADCx, int16_t LThreshold)
{
    ADCx->WINDTH.H[0] = LThreshold;
}
/**
 *******************************************************************************
 * @brief	    Configures higher threshold of window detect function
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	HThreshold: setting lower threshold
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetHigherThreshold(ADC0, 1000);
 * @endcode
 *******************************************************************************
 */
void ADC_SetHigherThreshold(ADC_Struct* ADCx, int16_t HThreshold)
{
    ADCx->WINDTH.H[1] = HThreshold;
}
/**
 *******************************************************************************
 * @brief	    Configures window detect function apply channel
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	WINDApply : specifies the ADC inteernal clock divider
 *  @arg\b	    ADC_WINDSingle : window detect function only apply single channel
 *	@arg\b	    ADC_WINDAll : window detect function apply all channel
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_WindowDetectRange_Select(ADC0, ADC_WINDSingle);
 * @endcode
 *******************************************************************************
 */
void ADC_WindowDetectRange_Select(ADC_Struct* ADCx, ADC_WindowDetectApplyDef WINDApply)
{
    ADCx->CR1.MBIT.WIND_MDS = WINDApply;
}
/**
 *******************************************************************************
 * @brief	    Enable/Disable window detect function 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of window detect function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_WindowDetect_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_WindowDetect_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->CR1.MBIT.WIND_EN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Select ADC Out property
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCOutSel: select window detect result
 *  @arg\b	    ADC_WDL_Event : WDLF - outside low
 *	@arg\b	    ADC_WDI_Event : WDIF - inside
 *  @arg\b	    ADC_WDH_Event : WDHF - outside high
 * @return 	    none
 * @note        
 * @par         Example
 * @code
    ADC_Output_Select(ADC0, ADC_WDI_Event);
 * @endcode
 *******************************************************************************
 */
void ADC_Output_Select(ADC_Struct* ADCx,ADC_OutputDef ADCOutSel)
{
    ADCx->CR1.MBIT.OUT_SEL = ADCOutSel;
}
///@}



/**
 * @name	config PGA property 
 *   		
 */ 
///@{ 
// config PGA property 
/**
 *******************************************************************************
 * @brief	    Enable/Disable PGA function 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of PGA
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_PGA_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_PGA_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->ANA.MBIT.PGA_EN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Config PGA gain
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	PGAGain: setting gain x1~x4
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetPGAGain(ADC0, 10);
 * @endcode
 *******************************************************************************
 */
void ADC_SetPGAGain(ADC_Struct* ADCx, uint8_t PGAGain)
{
    ADCx->GAIN.MBIT.GAIN_PGA = PGAGain;
}

/**
 *******************************************************************************
 * @brief	    St PGA offset
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	PGAOFFT: 0~63
 * @return 	    none
 *******************************************************************************
 */
void ADC_SetPGAOffset(ADC_Struct* ADCx, uint8_t PGAOFFT)
{
    ADCx->GAIN.MBIT.OFFT_PGA = PGAOFFT;
}
/**
 *******************************************************************************
 * @brief	    Enable/Disable PGA calibration state
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of PGA calibration ON/OFF
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_PGAOffsetCalibration_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_PGAOffsetCalibration_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    uint8_t VOD_x, VOD_0, VOD_63;
    uint8_t PGAOFFT;
    
    if (NewState == DISABLE)
        return;
    
    // enable PGA calibration state
    ADCx->CAL.MBIT.CAL_POFFT = 1;
    
    //
    PGAOFFT = 32;
    ADC_SetPGAOffset(ADC0, PGAOFFT);
    ADC_PGA_Cmd(ADC0, ENABLE);
    
    // read VOD
    VOD_x = ADC0->STA.MBIT.POF;
    
    ADC_SetPGAOffset(ADC0, 0);
    VOD_0 = ADC0->STA.MBIT.POF;
    
    ADC_SetPGAOffset(ADC0, 63);
    VOD_63 = ADC0->STA.MBIT.POF;
    
    if((VOD_0 == VOD_x) && (VOD_63 == VOD_x))
    {
        ADC_SetPGAOffset(ADC0, PGAOFFT);
        ADC0->CAL.MBIT.CAL_POFFT = 0;
        return;
    }
    
    // read VOD 
    if (ADC0->STA.MBIT.POF != VOD_x)
    {
        PGAOFFT  = 33;
        ADC_SetPGAOffset(ADC0, PGAOFFT);
        
        while (1)
        {
            if (ADC0->STA.MBIT.POF != VOD_x) break;
            PGAOFFT ++;
            ADC_SetPGAOffset(ADC0, PGAOFFT);
        }
    } else 
    {
        PGAOFFT  = 31;
        ADC_SetPGAOffset(ADC0, PGAOFFT);
        
        while (1)
        {
            if (ADC0->STA.MBIT.POF != VOD_x) break;
            PGAOFFT --;
            ADC_SetPGAOffset(ADC0, PGAOFFT);
        }
        
    }
        
    // Disable calibration 
    ADC0->CAL.MBIT.CAL_POFFT = 0;
}
///@}


/**
 * @name	ADC Calibration
 *   		
 */ 
///@{ 
#if (MG32_1ST)	
/******************************************************************************
 * @brief       Calibrate offset of middle
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return      none
 * @note        no release
 *****************************************************************************/
void ADC_VRMCalibration(ADC_Struct* ADCx,uint8_t VRMV) 
{
    int32_t VRPV, VRNV, VRM;
    int32_t CaliV;
    uint8_t i;
    
    UnProtectModuleReg(CFGprotect); 

    VRM = VRMV;
    
    // middle trim
    while (1)
    {
        ADC_InternalChannel_Select(ADCx, ADC_INT_VSSA);
        for (i=0, VRNV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx,ADC_STA_E1CNVF_happened_h0);
        }
        for (i=0, VRNV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx,ADC_STA_E1CNVF_happened_h0);
            VRNV += ADC_GetDAT0Data(ADCx);
        }
        VRNV = VRNV / 10;
        
        //-------------------------------------------------
        ADC_InternalChannel_Select(ADCx, ADC_INT_IVREF);
        for (i=0, VRNV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx,ADC_STA_E1CNVF_happened_h0);
        }
        for (i=0, VRPV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx,ADC_STA_E1CNVF_happened_h0);
            VRPV += ADC_GetDAT0Data(ADCx);
        }
        VRPV = VRPV / 10;
        
        
        //-------------------------------------------------
        CaliV = (VRNV + VRPV) >> 1;
        CaliV = CaliV - 2048;
        CaliV = CaliV / 2;
        VRM = VRM + CaliV;
        CFG_SetADC0RefMiddle(VRM);
        
                
        if (CaliV == 1) break;
        if (CaliV == 0) break;
        if (CaliV == -1) break;
        
        
    }
        
    // 2018.08.29 test
    VRM = VRM + 1;
    CFG_SetADC0RefMiddle(VRM);
}
#endif        
    
/**
 *******************************************************************************
 * @brief	    Enable/Disable ADC calibration state
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of ADC calibration 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_StartCalibration(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_StartCalibration(ADC_Struct* ADCx, FunctionalState NewState)
{
#if (MG32_1ST)
    int16_t VRP, VRN, VRM;
    int32_t VRPV, VRNV;
    uint8_t i;
    uint32_t rADC_MSK, rADC_START, rADC_CR0;
    
    //
    if (NewState == DISABLE)
        return;
   
    // RESAVE
    rADC_MSK = ADCx->MSK.W;
    rADC_START = ADCx->START.W;
    rADC_CR0 = ADCx->CR0.W;    

    // config ADC mode for calibration 
    ADC_ConversionMode_Select(ADCx, ADCMode);
    ADC_TriggerSource_Select(ADCx, ADC_START);
    ADC_SingleDifferentMode_Select(ADC0, ADC_SingleMode);
    ADC_SetOutputCodeFormat(ADC0, ADC_UnsignedFormat);
    ADC_DataResolution_Select(ADC0, ADC_12BitData);
    
    // start calibration
    UnProtectModuleReg(CFGprotect); 
    
    VRP = 32;
    VRN = 32;
    VRM = 32;
    CFG_SetADC0RefTop(VRP);
    CFG_SetADC0RefMiddle(VRM);
    CFG_SetADC0RefBottom(VRN);
    
    
    VRN = 0;
    while(1)
    {
        CFG_SetADC0RefBottom(VRN);
        ADC_ChannelMUX_Select(ADC0, ADC_InternalChannel);
        ADC_InternalChannel_Select(ADCx, ADC_INT_VSSA);
        for (i=0, VRNV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx,ADC_STA_E1CNVF_happened_h0);
        }
        for (i=0, VRNV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx,ADC_STA_E1CNVF_happened_h0);
            if( ADC_GetDAT0Data(ADCx) == 0x0000) break;
            VRNV += ADC_GetDAT0Data(ADCx);
        }
        VRNV = VRNV / 10;
        
        if (VRNV > 0) VRN ++;
        if (VRNV == 0) 
        {
            VRN -= 1; 
            break;
        }
        if (VRN == 64) 
        {
            VRN = 32;
            break;
        }
    }
    
    CFG_SetADC0RefMiddle(32);
    CFG_SetADC0RefBottom(32);
    VRP = 0;
    while(1)
    {
        CFG_SetADC0RefTop(VRP);
        
        ADC_InternalChannel_Select(ADCx, ADC_INT_IVREF);
        for (i=0, VRPV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx,ADC_STA_E1CNVF_happened_h0);
        }
        for (i=0, VRPV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx,ADC_STA_E1CNVF_happened_h0);
            if( ADC_GetDAT0Data(ADCx) < 4095) break;
            VRPV += ADC_GetDAT0Data(ADCx);
        }
        VRPV = VRPV / 10;
        
        if (VRPV > 4094) 
            VRP ++;
        else 
        {
            VRP --;
            break;
        }
        
        if (VRP == 64) 
        {
            VRP = 32;
            break;
        }
        
    }
    
    CFG_SetADC0RefTop(VRP);
    CFG_SetADC0RefMiddle(VRM);
    CFG_SetADC0RefBottom(VRN);
    
    
    VRM = (CFG_GetADC0RefTop() + CFG_GetADC0RefBottom()) / 2;
    CFG_SetADC0RefMiddle(VRM);
    
//    // middle trim
    ADC_VRMCalibration(ADCx, VRM);
            
    ProtectModuleReg(CFGprotect);   
    
    ADCx->MSK.W = rADC_MSK;
    ADCx->START.W = rADC_START;
    ADCx->CR0.W = rADC_CR0;    
#endif   
}
///@}



/**
 * @name	ADC Auxrity config
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Enable or Disable ADC macro
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of ADC
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->CR0.MBIT.EN = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable or Disable DMA access ADC result
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of ADC
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_DMA_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_DMA_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->CR0.MBIT.DMA_EN = NewState;
}

#if (MG32_2ND || MG32_3RD)
/**
 *******************************************************************************
 * @brief	    Set ADC data size for DMA transmission 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	DMADataSize: select dats size for DMA transmission
 *  @arg\b	    ADC_DMA_32bit : ADC will transfer ADC0_DAT0 for DMA transmission
 *	@arg\b	    ADC_DMA_16bit : ADC will transfer the bit[15:0] of ADC0_DAT0 for 
 *                              DMA transmission
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_DMADataSize_Select(ADC0, ADC_DMA_16bit);
 * @endcode
 *******************************************************************************
 */
void ADC_DMADataSize_Select(ADC_Struct* ADCx, ADC_DMADataSizeDef DMADataSize)
{
    ADCx->CR0.MBIT.DMA_DSIZE = DMADataSize;
}


/**
 *******************************************************************************
 * @brief	    Set ADC assert E1CNVF during DMA transmission
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	DMAMaskFlagDef: Select flag state during DMA access
 *  @arg\b	    ADC_Mask_E1CNVF : E1CNVF flag will be masked after ADC conversion
 *                                end during DMA access.
 *	@arg\b	    ADC_Assert_E1CNVF : E1CNVF flag asserted mode select during DMA access
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_DMAMaskFlag_Select(ADC0, ADC_Assert_E1CNVF);
 * @endcode
 *******************************************************************************
 */
void ADC_DMAMaskFlag_Select(ADC_Struct* ADCx, ADC_DMAMaskE1CNVFDef DMAMaskFlagDef)
{
    ADCx->CR0.MBIT.DMA_MDS = DMAMaskFlagDef;
}


/**
 *******************************************************************************
 * @brief	    Get ADC next conversion channel
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    Next Channel seletion
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetNextConversionChannel(ADC0);
 * @endcode
 *******************************************************************************
 */
uint8_t ADC_GetNextConversionChannel(ADC_Struct* ADCx)
{
    return ADCx->STA.MBIT.CNV_CH;
}
#endif

#if (MG32_1ST || MG32_3RD)	
/**
 *******************************************************************************
 * @brief	    Config ADC into idle when stop conversion
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of ADC AutoOff (save power)
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_AutoOff_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_AutoOff_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->CR0.MBIT.AUTOFF_EN = NewState;
}
#endif


/**
 *******************************************************************************
 * @brief	    ADC had readed data then start the next 
 *              conversion (for low frequency MCU)
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of ADC conversion wait mode
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_WaitDataReadOut(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_WaitDataReadOut(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->CR0.MBIT.WAIT_EN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Extend sampling time for ADC conversion 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSampleTime: 0~255 (1T~256T)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetExtendSampling(ADC0, 6);
 * @endcode
 *******************************************************************************
 */
void ADC_SetExtendSampling(ADC_Struct* ADCx, uint8_t ADCSampleTime)
{
    ADCx->CR0.MBIT.SMP_SEL = ADCSampleTime;
}
///@}




/**
 * @name	ADC Conversion mode configuration
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config ADC conversion mode
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCConvMode: select convertsion mode
 *  @arg\b	    ADCMode : One channel 
 *	@arg\b	    ADCContinueMode : One + Continue
 *	@arg\b	    ScanMode : Scan
 *	@arg\b	    ScanContinueMode : Scan + continue 
 *	@arg\b	    LoopMode : Loop
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ConversionMode_Select(ADC0, ScanContinueMode);
 * @endcode
 *******************************************************************************
 */
void ADC_ConversionMode_Select(ADC_Struct* ADCx, ADC_ConversionModeDef ADCConvMode)
{
    switch(ADCConvMode)
    {
        case ADCMode:
            ADC_MainConversionMode_Select(ADC0, ADC_OneShot);
            ADC_ContinueMode_Cmd(ADC0, DISABLE);
            break;
        
        case ADCContinueMode:
            ADC_MainConversionMode_Select(ADC0, ADC_OneShot);
            ADC_ContinueMode_Cmd(ADC0, ENABLE);
            break;

        case ScanMode:
            ADC_MainConversionMode_Select(ADC0, ADC_Scan);
            ADC_ContinueMode_Cmd(ADC0, DISABLE);
            break;

        case ScanContinueMode:
            ADC_MainConversionMode_Select(ADC0, ADC_Scan);
            ADC_ContinueMode_Cmd(ADC0, ENABLE);
            break;

        case LoopMode:
            ADC_MainConversionMode_Select(ADC0, ADC_Loop);
            ADC_ContinueMode_Cmd(ADC0, DISABLE);
            break;

        default:
            break;
    }
            
}
/**
 *******************************************************************************
 * @brief	    Enable/Disable ADC countinue state
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of ADC continue mode
 *      	    This parameter can be: ENABLE or DISABLE.
 * @note        no release
 * @return 	    none
 *******************************************************************************
 */
void ADC_ContinueMode_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->START.MBIT.TRG_CONT = NewState;
}
/**
 *******************************************************************************
 * @brief	    Hold ADC countinue mode
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: Hold conversion (En/Disable)
 *      	    This parameter can be: ENABLE or DISABLE.
 * @note        no release
 * @return 	    none
 *******************************************************************************
 */
void ADC_HoldConversion_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->START.MBIT.HOLD = NewState;
}

/**
 *******************************************************************************
 * @brief	    Set ADC main conversion mode
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	MainCM: select main convertsion mode
 *  @arg\b	    ADC_OneShot : One shot 
 *	@arg\b	    ADC_Scan : scan mode
 *	@arg\b	    ADC_Loop : loop mode
 * @note        no release
 * @return 	    none
 *******************************************************************************
 */
void ADC_MainConversionMode_Select(ADC_Struct* ADCx, ADC_MainConversionModeDef MainCM)
{
    ADCx->START.MBIT.CONV_MDS = MainCM;
}
///@}





/**
 * @name	ADC trigger source for conversion
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config ADC trigger source for conversion
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCTrgSel: select convertsion trigger source
 *  @arg\b	    ADC_START : SW setting to convert
 *	@arg\b	    ADC_TM00_TRGO : TM00 trigger out to convert 
 *	@arg\b	    ADC_TRGPin : External ADC pin trigger to convert
 *	@arg\b	    ADC_CMP0Out : comparator0 output to convert
 *	@arg\b	    ADC_CMP1Out : comparator1 output to convert
 *	@arg\b	    ADC_TM01_TRGO : TM01 trigger out to convert 
 *	@arg\b	    ADC_TM20_TRGO : TM20 trigger out to convert 
 *	@arg\b	    ADC_TM36_TRGO : TM36 trigger out to convert 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_TriggerSource_Select(ADC0, ADC_START);
 * @endcode
 *******************************************************************************
 */
void ADC_TriggerSource_Select(ADC_Struct* ADCx, ADC_TriggerSourceDef ADCTrgSel)
{
    ADCx->START.MBIT.START_SEL = ADCTrgSel;
}

/**
 *******************************************************************************
 * @brief	    Software start ADC conversion
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of software trigger ADC conversion
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SoftwareConversion_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_SoftwareConversion_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->START.MBIT.START = NewState;
}

/**
 *******************************************************************************
 * @brief	    Config ADC trigger event (Disable/rising/falling/dual edge)
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCExtEdgeSel: select trigger edge event to convert
 *  @arg\b	    ADC_DisableExtTrg : disable to convert
 *	@arg\b	    ADC_AcceptRisingEdge : Rising edge trigger out to convert 
 *	@arg\b	    ADC_AcceptFallingEdge : Falling edge trigger out to convert
 *	@arg\b	    ADC_AcceptDualEdge : dual edge trigger out to convert
 * @return 	    none
 * @note        Apply ADC_TRGPin 
 * @par         Example
 * @code
    ADC_TriggerEdge_Select(ADC0, ADC_AcceptRisingEdge);
 * @endcode
 *******************************************************************************
 */
void ADC_TriggerEdge_Select(ADC_Struct* ADCx, ADC_TriggerEdgeDef ADCExtEdgeSel)
{
    ADCx->START.MBIT.TRG_SEL = ADCExtEdgeSel;
}
///@}




/**
 * @name	config conversion channel
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config ADC conversion channel MUX external 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ChannelSel: config channel for ADC channel input 
 *  @arg\b	    ADC_ExternalChannel : select external channel, AIN0~15
 *	@arg\b	    ADC_InternalChannel : select internal channel, ie. VSSA, IVREF...
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ChannelMUX_Select(ADC0, ADC_ExternalChannel);
 * @endcode
 *******************************************************************************
 */
void ADC_ChannelMUX_Select(ADC_Struct* ADCx, ADC_ChannelMUX_Def ChannelSel)
{
    ADCx->START.MBIT.CH_SEL = ChannelSel;
}

/**
 *******************************************************************************
 * @brief	    Select channel for ADC conversion
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ExtCHSel: which external channel 
 *  @arg\b	    ADC_ExtAIN0 : select external channel AIN0
 *  @arg\b	    ADC_ExtAIN1 : select external channel AIN1
 *  @arg\b	    ADC_ExtAIN2 : select external channel AIN2
 *  @arg\b	    ADC_ExtAIN3 : select external channel AIN3
 *  @arg\b	    ADC_ExtAIN4 : select external channel AIN4 
 *  @arg\b	    ADC_ExtAIN5 : select external channel AIN5
 *  @arg\b	    ADC_ExtAIN6 : select external channel AIN6
 *  @arg\b	    ADC_ExtAIN7 : select external channel AIN7
 *  @arg\b	    ADC_ExtAIN8 : select external channel AIN8
 *  @arg\b	    ADC_ExtAIN9 : select external channel AIN9
 *  @arg\b	    ADC_ExtAIN10 : select external channel AIN10
 *  @arg\b	    ADC_ExtAIN11 : select external channel AIN11
 *  @arg\b	    ADC_ExtAIN12 : select external channel AIN12
 *  @arg\b	    ADC_ExtAIN13 : select external channel AIN13
 *  @arg\b	    ADC_ExtAIN14 : select external channel AIN14
 *  @arg\b	    ADC_ExtAIN15 : select external channel AIN15
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ExternalChannel_Select(ADC0, ADC_ExtAIN3);
 * @endcode
 *******************************************************************************
 */
void ADC_ExternalChannel_Select(ADC_Struct* ADCx, ADC_ExtChannelDef ExtCHSel)
{
    ADCx->START.B[1] = ExtCHSel;
}

/**
 *******************************************************************************
 * @brief	    Select channel for ADC conversion
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	IntCHSel: which internal channel 
 *  @arg\b	    ADC_INT_VSSA : select internal channel VSSA
 *  @arg\b	    ADC_INT_IVREF : select internal channel IVREF
 *  @arg\b	    ADC_INT_VBG : select internal channel VBG
 *  @arg\b	    ADC_INT_DACP0 : select internal channel DAC_P0
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_InternalChannel_Select(ADC0, ADC_INT_IVREF);
 * @endcode
 *******************************************************************************
 */
void ADC_InternalChannel_Select(ADC_Struct* ADCx, ADC_IntChannelDef IntCHSel)
{
    ADCx->START.B[1] = IntCHSel;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable channel in scan/loop mode
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	MSKChannelSel : AIN0, AIN1 ... AIN15
 * @param[in] 	NewState: new state of ADC Mask channel
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ScanLoopChannel_Enable(ADC0, (ADC_MskAIN4 | ADC_MskAIN11), ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_ScanLoopChannel_Enable(ADC_Struct* ADCx, uint16_t MSKChannelSel, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        #if (MG32_2ND)	
            ADCx->MSK.H[0] |= MSKChannelSel & 0xFF0F;
		#endif
		#if (MG32_1ST || MG32_3RD)	
            ADCx->MSK.H[0] |= MSKChannelSel;
		#endif
    }
    else
        ADCx->MSK.H[0] &= ~MSKChannelSel;
}


#if (MG32_2ND || MG32_3RD)
/**
 *******************************************************************************
 * @brief	    Config ADC change channel MUX timing when in Scan/Loop mode.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_ChangTimeing: ADC change channel MUX timing
 *  @arg\b	    ADC_ChangeMUX_E1CNVF : Change channel MUX when E1CNVF happened.
 *  @arg\b	    ADC_ChangeMUX_ESMPF : Change channel MUX when ESMPF happened.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ChangeMUXTiming_Select(ADC0, ADC_ChangeMUX_E1CNVF);
 * @endcode
 *******************************************************************************
 */
void ADC_ChangeMUXTiming_Select(ADC_Struct* ADCx, ADC_ChangeTimingDef ADC_ChangTimeing)
{
    ADCx->CR0.MBIT.CH_CHG = ADC_ChangTimeing;
}
#endif
///@}


/**
 * @name	config ADC conversion type mode
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config ADC conversion type (Single or Different)
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_ConversionType: config ADC conversion type 
 *  @arg\b	    ADC_SingleMode : Single conversion mode
 *	@arg\b	    ADC_DifferentMode : Different conversion mode
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SingleDifferentMode_Select(ADC0, ADC_SingleMode);
 * @endcode
 *******************************************************************************
 */
void ADC_SingleDifferentMode_Select(ADC_Struct* ADCx, ADC_ConversionTypeDef ADC_ConversionType)
{
#if (MG32_1ST)
    ADCx->CR0.MBIT.MDS = ADC_ConversionType;
#endif
}

///@}



/**
 * @name	Accumulator for ADC data
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config process mode for spike data 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCLimitMode: new process mode 
 *  @arg\b	    ADC_LimitNoOperation : No operation for spike ADC conversion data
 *	@arg\b	    ADC_LimitSkip : Skip for spike ADC conversion data
 *	@arg\b	    ADC_LimitClamp : Clamp for spike ADC conversion data
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetLimitFunction(ADC0, ADC_LimitSkip);
 * @endcode
 *******************************************************************************
 */
void ADC_SetLimitFunction(ADC_Struct* ADCx, ADC_LimitModeDef ADCLimitMode)
{
    ADCx->CR0.MBIT.LIM_MDS = ADCLimitMode;
}

/**
 *******************************************************************************
 * @brief	    Select channel for accumulation-0
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	Sum0ChannelSel : SAIN0 or SAIN1 ... SAIN15
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_DeADC_SetSum0ChannelInit(ADC0, SAIN3);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSum0Channel(ADC_Struct* ADCx,uint8_t Sum0ChannelSel)
{
    ADCx->MSK.MBIT.SUM0_MUX = Sum0ChannelSel;
}
/**
 *******************************************************************************
 * @brief	    Select channel for accumulation-1
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	Sum1ChannelSel : SAIN0 or SAIN1 ... SAIN15
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_DeADC_SetSum1ChannelInit(ADC0, SAIN5);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSum1Channel(ADC_Struct* ADCx,uint8_t Sum1ChannelSel)
{
    ADCx->MSK.MBIT.SUM1_MUX = Sum1ChannelSel;
}
/**
 *******************************************************************************
 * @brief	    Select channel for accumulation-2
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	Sum2ChannelSel : SAIN0 or SAIN1 ... SAIN15
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_DeADC_SetSum2ChannelInit(ADC0, SAIN8);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSum2Channel(ADC_Struct* ADCx,uint8_t Sum2ChannelSel)
{
    ADCx->MSK.MBIT.SUM2_MUX = Sum2ChannelSel;
}

/**
 *******************************************************************************
 * @brief	    Config accumulate mode for single/all cahnnel data 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSumChXDef: new accumulate mode for sum0/1/2
 *  @arg\b	    ADC_SumSpeciallyChannel : specify single channel
 *	@arg\b	    ADC_SumAllChannel : accumulate all conversion channel data
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SumChannelMode_Select(ADC0, ADC_SumSpeciallyChannel);
 * @endcode
 *******************************************************************************
 */
void ADC_SumChannelMode_Select(ADC_Struct* ADCx,ADC_SumChannelXDef ADCSumChXDef)
{
    ADCx->CR1.MBIT.SUM_MDS = ADCSumChXDef;
}

/**
 *******************************************************************************
 * @brief	    Select channel for accumulation-2
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSumNumbers: ADC data sum accumulation data number (0~64)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetSumNumber(ADC0, 32);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSumNumber(ADC_Struct* ADCx, uint8_t ADCSumNumbers)
{
    ADCx->CR1.MBIT.SUM_NUM = ADCSumNumbers;
}

/**
 *******************************************************************************
 * @brief	    Config data sum overrun mode select 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSumOW: overrun mode select
 *  @arg\b	    ADC_SumOverWritten : Overwritten by new data
 *	@arg\b	    ADC_SumKeep : Preserved old date 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SumOverrunMode_Select(ADC0, ADC_SumKeep);
 * @endcode
 *******************************************************************************
 */
void ADC_SumOverrunMode_Select(ADC_Struct* ADCx, ADC_SumDataOWDef ADCSumOW)
{
    ADCx->CR1.MBIT.SOVR_MDS = ADCSumOW;
}

/**
 *******************************************************************************
 * @brief	    Get sum0 status flag 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    sum0 flag (OVRF/CF/OF)
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetSum0Flags(ADC0);
 * @endcode
 *******************************************************************************
 */
uint16_t ADC_GetSum0Flags(ADC_Struct* ADCx)
{
    return ADCx->SUM0.H[1];
}
/**
 *******************************************************************************
 * @brief	    Get sum1 status flag 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    sum1 flag (OVRF/CF/OF)
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetSum1Flags(ADC0);
 * @endcode
 *******************************************************************************
 */
uint16_t ADC_GetSum1Flags(ADC_Struct* ADCx)
{
    return ADCx->SUM1.H[1];
}
/**
 *******************************************************************************
 * @brief	    Get sum2 status flag 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    sum2 flag (OVRF/CF/OF)
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetSum2Flags(ADC0);
 * @endcode
 *******************************************************************************
 */
uint16_t ADC_GetSum2Flags(ADC_Struct* ADCx)
{
    return ADCx->SUM2.H[1];
}
/**
 *******************************************************************************
 * @brief	    Clear sum0 flag
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_SUMxFlag: interrupt source item
 *  @arg\b	    ADC_SUMxOVRF : ADC0 data sum-0,1,2 register overrun flag                  
 *  @arg\b	    ADC_SUMxCF : ADC0 data sum-0,1,2 accumulation complete flag             
 *  @arg\b	    ADC_SUMxOF : ADC0 data sum-0,1,2 accumulation overflow flag 
 *  @arg\b	    ADC_SUMxUF : ADC0 data sum-0,1,2 accumulation underflow flag 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ClearSum0Flags(ADC0, ADC_SUMxCF);
 * @endcode
 *******************************************************************************
 */
void ADC_ClearSum0Flags(ADC_Struct* ADCx, uint8_t ADC_SUMxFlag)
{
    ADCx->SUM0.H[1] = ADC_SUMxFlag;
}
/**
 *******************************************************************************
 * @brief	    Clear sum1 flag
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_SUMxFlag: interrupt source item
 *  @arg\b	    ADC_SUMxOVRF : ADC0 data sum-0,1,2 register overrun flag                  
 *  @arg\b	    ADC_SUMxCF : ADC0 data sum-0,1,2 accumulation complete flag             
 *  @arg\b	    ADC_SUMxOF : ADC0 data sum-0,1,2 accumulation overflow flag 
 *  @arg\b	    ADC_SUMxUF : ADC0 data sum-0,1,2 accumulation underflow flag 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ClearSum1Flags(ADC0, ADC_SUMxOF);
 * @endcode
 *******************************************************************************
 */
void ADC_ClearSum1Flags(ADC_Struct* ADCx, uint8_t ADC_SUMxFlag)
{
    ADCx->SUM1.H[1] = ADC_SUMxFlag;
}
/**
 *******************************************************************************
 * @brief	    Clear sum2 flag
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_SUMxFlag: interrupt source item
 *  @arg\b	    ADC_SUMxOVRF : ADC0 data sum-0,1,2 register overrun flag                  
 *  @arg\b	    ADC_SUMxCF : ADC0 data sum-0,1,2 accumulation complete flag             
 *  @arg\b	    ADC_SUMxOF : ADC0 data sum-0,1,2 accumulation overflow flag 
 *  @arg\b	    ADC_SUMxUF : ADC0 data sum-0,1,2 accumulation underflow flag 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ClearSum2Flags(ADC0, ADC_SUMxUF);
 * @endcode
 *******************************************************************************
 */
void ADC_ClearSum2Flags(ADC_Struct* ADCx, uint8_t ADC_SUMxFlag)
{
    ADCx->SUM2.H[1] = ADC_SUMxFlag;
}
/**
 *******************************************************************************
 * @brief	    Get sum0 data 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    sum0 data
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetSum0Data(ADC0);
 * @endcode
 *******************************************************************************
 */
int16_t ADC_GetSum0Data(ADC_Struct* ADCx)
{
    return ADCx->SUM0.H[0];
}
/**
 *******************************************************************************
 * @brief	    Get sum1 data
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    sum1 data
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetSum1Data(ADC0);
 * @endcode
 *******************************************************************************
 */
int16_t ADC_GetSum1Data(ADC_Struct* ADCx)
{
    return ADCx->SUM1.H[0];
}
/**
 *******************************************************************************
 * @brief	    Get sum2 data
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    sum2 data
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetSum2Data(ADC0);
 * @endcode
 *******************************************************************************
 */
int16_t ADC_GetSum2Data(ADC_Struct* ADCx)
{
    return ADCx->SUM2.H[0];
}
/**
 *******************************************************************************
 * @brief	    Set sum0 data 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSum0Initial: ADC sum-0 initial data 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetSum0Data(ADC0, 255);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSum0Data(ADC_Struct* ADCx, int16_t ADCSum0Initial)
{
    ADCx->SUM0.H[0] = ADCSum0Initial;
}
/**
 *******************************************************************************
 * @brief	    Set sum1 data
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSum1Initial: ADC sum-1 initial data 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetSum1Data(ADC0, 25);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSum1Data(ADC_Struct* ADCx, int16_t ADCSum1Initial)
{
    ADCx->SUM1.H[0] = ADCSum1Initial;
}
/**
 *******************************************************************************
 * @brief	    Set sum2 data
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSum2Initial: ADC sum-2 initial data 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetSum2Data(ADC0, 1000);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSum2Data(ADC_Struct* ADCx, int16_t ADCSum2Initial)
{
    ADCx->SUM2.H[0] = ADCSum2Initial;
}
///@}





/**
 * @name	ADC conversion data configuration
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config ADC conversion data Alignment mode
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	AlignMode: data alignment mode select (Right/Left)
 *  @arg\b	    ADC_RightJustified : Overwritten by new data
 *	@arg\b	    ADC_LeftJustified : Preserved old date 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_DataAlignment_Select(ADC0, ADC_RightJustified);
 * @endcode
 *******************************************************************************
 */
void ADC_DataAlignment_Select(ADC_Struct* ADCx, ADC_DataAlignModeDef AlignMode)
{
    ADCx->CR1.MBIT.ALIGN_SEL = AlignMode;
}

/**
 *******************************************************************************
 * @brief	    Config ADC conversion data resolution
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ResolutionData: data resolution (12/10 bit)
 *  @arg\b	    ADC_12BitData : data resolution = 12 bit
 *	@arg\b	    ADC_10BitData : data resolution = 10 bit
 *	@arg\b	    ADC_8BitData : data resolution = 10 bit
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_DataResolution_Select(ADC0, ADC_12BitData);
 * @endcode
 *******************************************************************************
 */
void ADC_DataResolution_Select(ADC_Struct* ADCx, ADC_ResolutionDef ResolutionData)
{
    ADCx->CR0.MBIT.RES_SEL = ResolutionData;
}

/**
 *******************************************************************************
 * @brief	    Config data overrun mode select 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	DataOW: overrun mode select
 *  @arg\b	    ADC_DataOverWritten : Overwritten by new data
 *	@arg\b	    ADC_DataKeep : Preserved old date 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_DataOverrunMode_Select(ADC0, ADC_DataOverWritten);
 * @endcode
 *******************************************************************************
 */
void ADC_DataOverrunMode_Select(ADC_Struct* ADCx, ADC_DataOWDef DataOW)
{
    ADCx->CR1.MBIT.OVR_MDS = DataOW;
}

/**
 *******************************************************************************
 * @brief	    Get DATA status flag 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    DATA flag (OVRF/CF)
 *  @arg\b	    ADC_DAT0_WDLF : ADC voltage window detect outside low event flag 
 *  @arg\b	    ADC_DAT0_WDIF : ADC voltage window detect inside event flag 
 *  @arg\b	    ADC_DAT0_WDHF : ADC voltage window detect outside high event flag 
 *  @arg\b	    ADC_DAT0_CF : ADC0 conversion data-0 complete in 1-time and 
 *                            data ready status bit 
 *  @arg\b	    ADC_DAT0_OVRF : ADC0 conversion data register-0 
 *                              overwrite/overrun indication status bit 
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetDAT0Flags(ADC0);
 * @endcode
 *******************************************************************************
 */
uint8_t ADC_GetDAT0Flags(ADC_Struct* ADCx)
{
    return ADCx->DAT0.B[2];
}

/**
 *******************************************************************************
 * @brief	    Get DATA conversion channel 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    which channel
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetDAT0Channel(ADC0);
 * @endcode
 *******************************************************************************
 */
uint8_t ADC_GetDAT0Channel(ADC_Struct* ADCx)
{
    return ADCx->DAT0.MBIT.DAT0_CH;
}

/**
 *******************************************************************************
 * @brief	    Get dat0 data
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    dat0 data
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetDAT0Data(ADC0);
 * @endcode
 *******************************************************************************
 */
int16_t ADC_GetDAT0Data(ADC_Struct* ADCx)
{
    return ADCx->DAT0.H[0];
}
/**
 *******************************************************************************
 * @brief	    Configures ADC output code with digital offset
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	sDigiOffset: specified 2s complement value of digital 
 *      	    This parameter can be: +15~-16.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetDigitalOffset(ADC0, 0);
 * @endcode
 *******************************************************************************
 */
void ADC_SetDigitalOffset(ADC_Struct* ADCx, int8_t sDigiOffset)
{
    ADCx->CR1.MBIT.DOS_VAL = sDigiOffset;
}

/**
 *******************************************************************************
 * @brief	    Configures ADC conversion data format
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	DatFormat: specified ADC output code format 
 *  @arg\b	    ADC_UnsignedFormat : ADC output unsigned data format
 *	@arg\b	    ADC_2sCompletementFormat : ADC output 2's complement data format
 * @return 	    none
 * @note        ADC_UnsignedFormat for ADC_SingleMode
 * @note        ADC_2sCompletementFormat for ADC_DifferentMode
 * @par         Example
 * @code
    ADC_SetOutputCodeFormat(ADC0, ADC_UnsignedFormat);
 * @endcode
 *******************************************************************************
 */
void ADC_SetOutputCodeFormat(ADC_Struct* ADCx, ADC_OutputCodeFormatDef DatFormat)
{
#if (MG32_1ST)
    ADCx->CR0.MBIT.CODE_FMT = DatFormat;
#endif
}
///@}



/**
 * @name	interrupt and flag (SET/CLEAR/Config) 
 *   		
 */ 
///@{ 
//
/**
 *******************************************************************************
 * @brief	    Config interrupt source (Enable/Disable)
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_ITSrc: interrupt source 
 *  @arg\b	    ADC_SUMOVR_IE : ADC0 data sum-0,1,2  overrun event interrupt enable 
 *  @arg\b	    ADC_SUMC_IE : ADC0 data sum-0,1,2  accumulation complete interrupt  
 *  @arg\b	    ADC_SUMO_IE : ADC0 data sum-0,1,2  accumulation overflow or underflow interrupt enable 
 *  @arg\b	    ADC_WDH_IE : ADC0 voltage window detect outside high event interrupt enable 
 *  @arg\b	    ADC_WDI_IE : ADC0 voltage window detect inside event interrupt enable 
 *  @arg\b	    ADC_WDL_IE : ADC0 voltage window detect outside low event interrupt enabl 
 *  @arg\b	    ADC_OVR_IE : ADC0 conversion overrun event interrupt enable 
 *  @arg\b	    ADC_ESCNV_IE : ADC0 channel scan conversion end interrupt enable 
 *  @arg\b	    ADC_E1CNV_IE : ADC0 one-time conversion end interrupt enable 
 *  @arg\b	    ADC_ESMP_IE : ADC0 sampling end interrupt enable 
 * @param[in] 	NewState: new state of the ADCx interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        
 * @par         Example
 * @code
    ADC_IT_Config(ADC0, ADC_WDI_IE, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_IT_Config(ADC_Struct* ADCx, uint32_t ADC_ITSrc, FunctionalState NewState)
{
    if (NewState == ENABLE)
        ADCx->INT.W |= ADC_ITSrc;
    else
        ADCx->INT.W &= ~ADC_ITSrc;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable all interrupt 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of the ADCx all interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ITEA_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_ITEA_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->INT.MBIT.IEA = NewState;
}

/**
 *******************************************************************************
 * @brief	    Get one interrupt source state
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_ITSTAFlag: interrupt flag
 *  @arg\b	    ADC_SUMOVRF : ADC0 data sum-0,1,2  register overrun flag                  
 *  @arg\b	    ADC_SUMCF : ADC0 data sum-0,1,2  accumulation complete flag             
 *  @arg\b	    ADC_SUMOF : ADC0 data sum-0,1,2 accumulation overflow or underflow flag 
 *  @arg\b	    ADC_WDHF : ADC0 voltage window detect outside high event flag          
 *  @arg\b	    ADC_WDIF : ADC0 voltage window detect inside event flag                
 *  @arg\b	    ADC_WDLF : ADC0 voltage window detect outside low event flag           
 *  @arg\b	    ADC_OVRF : ADC0 conversion overrun event flag                          
 *  @arg\b	    ADC_ESCNVF : ADC0 channel scan conversion end flag                       
 *  @arg\b	    ADC_E1CNVF : ADC0 one-time conversion end flagg                          
 *  @arg\b	    ADC_ESMPF : ADC0 sampling end flag                                      
 * @return 	    reference define of DRV_Return
 *  @arg  	    DRV_Happened : Happened
 *  @arg	    DRV_UnHappened : Unhappened
 * @note 
 * @par         Example
 * @code
    if(ADC_GetSingleFlagStatus(ADC0, ADC_WDIF) == DRV_Happened)
    {
        // to do ...
    }   
 * @endcode
 *******************************************************************************
 */
DRV_Return ADC_GetSingleFlagStatus(ADC_Struct* ADCx, uint32_t ADC_ITSTAFlag)
{   
    if (ADCx->STA.W & ADC_ITSTAFlag)
        return DRV_Happened;
    else
        return DRV_UnHappened;
    
    
}

/**
 *******************************************************************************
 * @brief	    Get all interrupt source state
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    response what happended of STA
 * @note        
 * @par         Example
 * @code
    tmp = ADC_GetAllFlagStatus(ADC0);
 * @endcode
 *******************************************************************************
 */
uint32_t ADC_GetAllFlagStatus(ADC_Struct* ADCx)
{
    return ADCx->STA.W;
}

/**
 *******************************************************************************
 * @brief	    Clear one or all interrupt source state
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_ITSTAFlag: interrupt source item
 *  @arg\b	    ADC_SUMOVRF : ADC0 data sum-0,1,2  register overrun flag                  
 *  @arg\b	    ADC_SUMCF : ADC0 data sum-0,1,2  accumulation complete flag             
 *  @arg\b	    ADC_SUMOF : ADC0 data sum-0,1,2 accumulation overflow or underflow flag 
 *  @arg\b	    ADC_WDHF : ADC0 voltage window detect outside high event flag          
 *  @arg\b	    ADC_WDIF : ADC0 voltage window detect inside event flag                
 *  @arg\b	    ADC_WDLF : ADC0 voltage window detect outside low event flag           
 *  @arg\b	    ADC_OVRF : ADC0 conversion overrun event flag                          
 *  @arg\b	    ADC_ESCNVF : ADC0 channel scan conversion end flag                       
 *  @arg\b	    ADC_E1CNVF : ADC0 one-time conversion end flagg                          
 *  @arg\b	    ADC_ESMPF : ADC0 sampling end flag                                      
 * @return 	    none
 * @note        
 * @par         Example
 * @code
    ADC_ClearFlag(ADC0, ADC_E1CNVF);
 * @endcode
 *******************************************************************************
 */
void ADC_ClearFlag(ADC_Struct* ADCx, uint32_t ADC_ITSTAFlag)
{
    ADCx->STA.W = ADC_ITSTAFlag;
}
///@}

