/**
 ******************************************************************************
 *
 * @file        MG32x02z_ADC_DRV.H
 *
 * @brief       This file contains all the functions prototypes for the ADC 
 *              firmware library.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.14
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

#ifndef _MG32x02z_ADC_DRV_H

/*!< _MG32x02z_ADC_DRV_H */ 
#define _MG32x02z_ADC_DRV_H


#include "MG32x02z__Common_DRV.H"
#include "MG32x02z_ADC.H"
//#include "MG32x02z_CFG_DRV.H"


/** 
 * @enum		ADC_PLLClockDivDef
 * @brief		declare Timer PLL clock divider 
 */        
typedef enum 
{ 
    ADC_PLLDIV2=0,       /*!< ADC PLL clock divder (DIV2) */
    ADC_PLLDIV4,         /*!< ADC PLL clock divder (DIV4) */
    ADC_PLLDIV5,         /*!< ADC PLL clock divder (DIV5) */
    ADC_PLLDIV6          /*!< ADC PLL clock divder (DIV6) */
} ADC_PLLClockDivDef;



/** 
 * @enum		ADC_ClockSourceDef
 * @brief		declare ADC clock source
 */        
typedef enum 
{ 
    ADC_CKADC=0,         /*!< ADC clock from CK_ADC */
    ADC_CKPLL,           /*!< ADC clock from PLL */
    ADC_TM00TRGO,        /*!< ADC clock from TM00 TRGO */
    ADC_TM01TRGO,        /*!< ADC clock from TM01 TRGO */
} ADC_ClockSourceDef;


/** 
 * @enum		ADC_INTClockDivDef
 * @brief		declare ADC internal clock divided 
 */        
typedef enum 
{ 
    ADC_IntDIV1=0,       /*!< ADC internal clock divider (DIV1) */
    ADC_IntDIV2,         /*!< ADC internal clock divider (DIV2) */
    ADC_IntDIV4,         /*!< ADC internal clock divider (DIV4) */
    ADC_IntDIV16         /*!< ADC internal clock divider (DIV16) */
} ADC_INTClockDivDef;


/** 
 * @enum		ADC_SCNTClockDivDef
 * @brief		declare ADC SCNT internal clock divided 
 */        
typedef enum 
{ 
    ADC_SCNTIntDIV1=0,  /*!< ADC SCNT internal clock divider (DIV1) */
    ADC_SCNTIntDIV4,    /*!< ADC SCNT internal clock divider (DIV4) */
    ADC_SCNTIntDIV16,   /*!< ADC SCNT internal clock divider (DIV16) */
    ADC_SCNTIntDIV32    /*!< ADC SCNT internal clock divider (DIV32) */
} ADC_SCNTClockDivDef;



/** 
 * @enum		ADC_WindowDetectApplyDef
 * @brief		apply window detect function (single / all channels)
 */        
typedef enum 
{ 
    ADC_WINDSingle=0,   /*!< window detect function only apply single channel */
    ADC_WINDAll,        /*!< window detect function apply all channel */
} ADC_WindowDetectApplyDef;

/** 
 * @enum		ADC_OutputDef
 * @brief		select ADC ouput property (LF,IF,HF,Current State)
 */        
typedef enum 
{ 
    ADC_WDL_Event=0,    /*!< WDLF - outside low */
    ADC_WDI_Event,      /*!< WDIF - inside */
    ADC_WDH_Event,      /*!< WDHF - outside high */
} ADC_OutputDef;

/** 
 * @enum		ADC_ConversionModeDef
 * @brief		select ADC conversion mode (ONE,Scan, Loop /w Continue)
 */        
typedef enum 
{ 
    ADCMode,            /*!< One channel */
    ADCContinueMode,    /*!< One + Continue */
    ScanMode,           /*!< Scan */
    ScanContinueMode,   /*!< Scan + continue */
    LoopMode,           /*!< Loop */
} ADC_ConversionModeDef;


/** 
 * @enum		ADC_MainConversionModeDef
 * @brief		select ADC conversion mode (ONE,Scan, Loop)
 */        
typedef enum 
{ 
    ADC_OneShot,        /*!< One shot mode */
    ADC_Scan,           /*!< scan mode */
    ADC_Loop,           /*!< loop mode */
} ADC_MainConversionModeDef;

/** 
 * @enum		ADC_TriggerSourceDef
 * @brief		Select ADC trigger event to start conversion
 */        
typedef enum 
{ 
    ADC_START,          /*!< SW : ADC0_START register setting */
    ADC_TM00_TRGO,      /*!< TM00 : TM00_TRGO */
    ADC_TRGPin,         /*!< PIN : ADC0_TRG : ADC external trigger pin */
    ADC_CMP0Out,        /*!< CMP0 : CMP0_OUT */
    ADC_CMP1Out,        /*!< CMP1 : CMP1_OUT */
    ADC_TM01_TRGO,      /*!< TM01 : TM01_TRGO */
    ADC_TM20_TRGO,      /*!< TM20 : TM20_TRGO */
    ADC_TM36_TRGO,      /*!< TM36 : TM36_TRGO */
} ADC_TriggerSourceDef;

/** 
 * @enum		ADC_TriggerEdgeDef
 * @brief		config external trigger event to start conversion
 */        
typedef enum 
{ 
    ADC_DisableTrg,         /*!< Disable trigger source */
    ADC_AcceptRisingEdge,   /*!< accept rising edge of trigger  */
    ADC_AcceptFallingEdge,  /*!< accept falling edge of trigger  */
    ADC_AcceptDualEdge,     /*!< accept dual (rising & falling) edge of trigger */
} ADC_TriggerEdgeDef;


/** 
 * @enum		ADC_ChannelMUX_Def
 * @brief		config channel for ADC channel input (external/internal)
 */        
typedef enum 
{
    ADC_ExternalChannel,    /*!< select external channel, AIN0~15 */
    ADC_InternalChannel,    /*!< select internal channel, ie. VSSA, IVREF, VBG ... */
} ADC_ChannelMUX_Def;

/** 
 * @enum		ADC_MskChannelDef
 * @brief		specify channel select for mask (scan/loop)
 */        
typedef enum 
{ 
    ADC_MskAIN0 = ADC_MSK_CH_MSK0_enable_h0,    /*!< specify ADC select channel channel 0 */ 
    ADC_MskAIN1 = ADC_MSK_CH_MSK1_enable_h0,    /*!< specify ADC select channel channel 1 */  
    ADC_MskAIN2 = ADC_MSK_CH_MSK2_enable_h0,    /*!< specify ADC select channel channel 2 */  
    ADC_MskAIN3 = ADC_MSK_CH_MSK3_enable_h0,    /*!< specify ADC select channel channel 3 */ 
#if (MG32_1ST || MG32_3RD)
    ADC_MskAIN4 = ADC_MSK_CH_MSK4_enable_h0,    /*!< specify ADC select channel channel 4 */  
    ADC_MskAIN5 = ADC_MSK_CH_MSK5_enable_h0,    /*!< specify ADC select channel channel 5 */  
    ADC_MskAIN6 = ADC_MSK_CH_MSK6_enable_h0,    /*!< specify ADC select channel channel 6 */  
    ADC_MskAIN7 = ADC_MSK_CH_MSK7_enable_h0,    /*!< specify ADC select channel channel 7 */  
#endif
    ADC_MskAIN8 = ADC_MSK_CH_MSK8_enable_h0,    /*!< specify ADC select channel channel 8 */  
    ADC_MskAIN9 = ADC_MSK_CH_MSK9_enable_h0,    /*!< specify ADC select channel channel 9 */  
    ADC_MskAIN10 = ADC_MSK_CH_MSK10_enable_h0,  /*!< specify ADC select channel channel 10 */ 
    ADC_MskAIN11 = ADC_MSK_CH_MSK11_enable_h0,  /*!< specify ADC select channel channel 11 */ 
    ADC_MskAIN12 = ADC_MSK_CH_MSK12_enable_h0,  /*!< specify ADC select channel channel 12 */ 
    ADC_MskAIN13 = ADC_MSK_CH_MSK13_enable_h0,  /*!< specify ADC select channel channel 13 */ 
    ADC_MskAIN14 = ADC_MSK_CH_MSK14_enable_h0,  /*!< specify ADC select channel channel 14 */ 
    ADC_MskAIN15 = ADC_MSK_CH_MSK15_enable_h0,  /*!< specify ADC select channel channel 15 */ 
} ADC_MskChannelDef;

/** 
 * @enum		ADC_ExtChannelDef
 * @brief		specify external channel select 
 */        
typedef enum 
{ 
    ADC_ExtAIN0=0,		/*!< specify ADC sample external channel 0 */ 
    ADC_ExtAIN1=1,    	/*!< specify ADC sample external channel 1 */  
    ADC_ExtAIN2=2,    	/*!< specify ADC sample external channel 2 */  
    ADC_ExtAIN3=3,    	/*!< specify ADC sample external channel 3 */  

#if (MG32_1ST || MG32_3RD)
    ADC_ExtAIN4=4,    	/*!< specify ADC sample external channel 4 */  
    ADC_ExtAIN5=5,    	/*!< specify ADC sample external channel 5 */  
    ADC_ExtAIN6=6,    	/*!< specify ADC sample external channel 6 */  
    ADC_ExtAIN7=7,    	/*!< specify ADC sample external channel 7 */
#endif
    
    ADC_ExtAIN8=8,    	/*!< specify ADC sample external channel 8 */  
    ADC_ExtAIN9=9,    	/*!< specify ADC sample external channel 9 */  
    ADC_ExtAIN10=10,	/*!< specify ADC sample external channel 10 */ 
    ADC_ExtAIN11=11,    /*!< specify ADC sample external channel 11 */ 
    ADC_ExtAIN12=12,    /*!< specify ADC sample external channel 12 */ 
    ADC_ExtAIN13=13,    /*!< specify ADC sample external channel 13 */ 
    ADC_ExtAIN14=14,    /*!< specify ADC sample external channel 14 */ 
    ADC_ExtAIN15=15,    /*!< specify ADC sample external channel 15 */ 
} ADC_ExtChannelDef;

/** 
 * @enum		ADC_IntChannelDef
 * @brief		specify internal channel select 
 */        
typedef enum 
{ 
    ADC_INT_VSSA = 0x10,    /*!< specify ADC sample internal VSSA */  
    ADC_INT_IVREF = 0x11,   /*!< specify ADC sample internal IVREF */ 
#if (MG32_1ST || MG32_3RD)
    ADC_INT_DACP0 = 0x12,   /*!< specify ADC sample internal DAC_P0 */ 
#endif
    ADC_INT_VBG = 0x13,     /*!< specify ADC sample internal VBG */ 
#if (MG32_2ND || MG32_3RD)
    ADC_INT_LDO = 0x18,     /*!< specify ADC sample internal LDO */ 
#endif
} ADC_IntChannelDef;


/** 
 * @enum		ADC_ConversionTypeDef
 * @brief		config ADC conversion type
 */        
typedef enum 
{ 
    ADC_SingleMode,         /*!< ADC single conversion mode */
    ADC_DifferentMode,      /*!< ADC different conversion mode  */
} ADC_ConversionTypeDef;



/** 
 * @enum		ADC_LimitModeDef
 * @brief		config process mode for spike data 
 */        
typedef enum 
{ 
    ADC_LimitNoOperation,   /*!< No operation for spike ADC conversion data */
    ADC_LimitSkip,          /*!< Skip for spike ADC conversion data  */
    ADC_LimitClamp,         /*!< Clamp for spike ADC conversion data */
} ADC_LimitModeDef;


/**
 * @name	SumXChannelSel
 *   		SumXChannelSel(SAIN0, SAIN1, SAIN2 ... AIN15)
 */ 
///@{  
#define SAIN0       0       /*!< External channel-0 be scan/loop channel. */    
#define SAIN1       1       /*!< External channel-1 be scan/loop channel. */
#define SAIN2       2       /*!< External channel-2 be scan/loop channel. */
#define SAIN3       3       /*!< External channel-3 be scan/loop channel. */

#if (MG32_1ST || MG32_3RD)
    #define SAIN4       4   /*!< External channel-4 be scan/loop channel. */
    #define SAIN5       5   /*!< External channel-5 be scan/loop channel. */
    #define SAIN6       6   /*!< External channel-6 be scan/loop channel. */
    #define SAIN7       7   /*!< External channel-7 be scan/loop channel. */
#endif

#define SAIN8       8       /*!< External channel-8 be scan/loop channel. */
#define SAIN9       9       /*!< External channel-9 be scan/loop channel. */
#define SAIN10      10      /*!< External channel-10 be scan/loop channel. */
#define SAIN11      11      /*!< External channel-11 be scan/loop channel. */
#define SAIN12      12      /*!< External channel-12 be scan/loop channel. */
#define SAIN13      13      /*!< External channel-13 be scan/loop channel. */
#define SAIN14      14      /*!< External channel-14 be scan/loop channel. */
#define SAIN15      15      /*!< External channel-15 be scan/loop channel. */
///@}

/** 
 * @enum		ADC_SumChannelXDef
 * @brief		accumulate channel that single / all channel
 */        
typedef enum 
{ 
    ADC_SumSpeciallyChannel,/*!< Single specify channel */
    ADC_SumAllChannel,      /*!< accumulate all conversion channel data  */
} ADC_SumChannelXDef;

/** 
 * @enum		ADC_SumDataOWDef
 * @brief		config sum overrun mode 
 */        
typedef enum 
{ 
    ADC_SumOverWritten, /*!< Overwritten by new data */
    ADC_SumKeep,        /*!< Preserved old date */
} ADC_SumDataOWDef;

/** 
 * @enum		ADC_DataAlignModeDef
 * @brief		config data alignment mode (Right/Left alignment)
 */        
typedef enum 
{ 
    ADC_RightJustified, /*!< Right Justified of ADC conversion data format */
    ADC_LeftJustified,  /*!< Left Justified of ADC conversion data format  */
} ADC_DataAlignModeDef;

/** 
 * @enum		ADC_ResolutionDef
 * @brief		config data resolution (12/10 bit)
 */        
typedef enum 
{ 
    ADC_12BitData,  /*!< data resolution = 12 bit */
    ADC_10BitData,  /*!< data resolution = 10 bit */
    ADC_8BitData,   /*!< data resolution = 8 bit */
} ADC_ResolutionDef;

/** 
 * @enum		ADC_DataOWDef
 * @brief		config data overrun mode 
 */        
typedef enum 
{ 
    ADC_DataOverWritten, /*!< Overwritten by new data */
    ADC_DataKeep,        /*!< Preserved old date */
} ADC_DataOWDef;


/** 
 * @enum		ADC_ITSrc
 * @brief		ADC interrupt source
 */        
typedef enum 
{ 
    ADC_SUMOVR_IE = ADC_INT_SUMOVR_IE_enable_w, /*!< ADC0 data sum-0,1,2  overrun event interrupt enable */
    ADC_SUMC_IE = ADC_INT_SUMC_IE_enable_w,     /*!< ADC0 data sum-0,1,2  accumulation complete interrupt  */
    ADC_SUMO_IE = ADC_INT_SUMO_IE_enable_w,     /*!< ADC0 data sum-0,1,2  accumulation overflow or underflow interrupt enable */
    ADC_WDH_IE = ADC_INT_WDH_IE_enable_w,       /*!< ADC0 voltage window detect outside high event interrupt enable */
    ADC_WDI_IE = ADC_INT_WDI_IE_enable_w,       /*!< ADC0 voltage window detect inside event interrupt enable */
    ADC_WDL_IE = ADC_INT_WDL_IE_enable_w,       /*!< ADC0 voltage window detect outside low event interrupt enabl */
    ADC_OVR_IE = ADC_INT_OVR_IE_enable_w,       /*!< ADC0 conversion overrun event interrupt enable */
    ADC_ESCNV_IE = ADC_INT_ESCNV_IE_enable_w,   /*!< ADC0 channel scan conversion end interrupt enable */
    ADC_E1CNV_IE = ADC_INT_E1CNV_IE_enable_w,   /*!< ADC0 one-time conversion end interrupt enable */
    ADC_ESMP_IE = ADC_INT_ESMP_IE_enable_w,     /*!< ADC0 sampling end interrupt enable */
    
} ADC_ITSrc;


/** 
 * @enum		ADC_ITSTAFlag
 * @brief		ADC status flag 
 */    
typedef enum 
{
    ADC_SUMOVRF =   ADC_STA_SUMOVRF_happened_w, /*!< ADC0 data sum-0,1,2  register overrun flag */
    ADC_SUMCF   =   ADC_STA_SUMCF_happened_w,   /*!< ADC0 data sum-0,1,2  accumulation complete flag */
    ADC_SUMOF   =   ADC_STA_SUMOF_happened_w,   /*!< ADC0 data sum-0,1,2 accumulation overflow or underflow flag */
    ADC_WDHF    =   ADC_STA_WDHF_happened_w,    /*!< ADC0 voltage window detect outside high event flag */
    ADC_WDIF    =   ADC_STA_WDIF_happened_w,    /*!< ADC0 voltage window detect inside event flag */
    ADC_WDLF    =   ADC_STA_WDLF_happened_w,    /*!< ADC0 voltage window detect outside low event flag */
    ADC_OVRF    =   ADC_STA_OVRF_happened_w,    /*!< ADC0 conversion overrun event flag */
    ADC_ESCNVF  =   ADC_STA_ESCNVF_happened_w,  /*!< ADC0 channel scan conversion end flag */
    ADC_E1CNVF  =   ADC_STA_E1CNVF_happened_w,  /*!< ADC0 one-time conversion end flagg */
    ADC_ESMPF   =   ADC_STA_ESMPF_happened_w,   /*!< ADC0 sampling end flag */
} ADC_ITSTAFlag;

/** 
 * @enum		ADC_OutputCodeFormatDef
 * @brief		Config ADC conversion code format
 */    
typedef enum 
{
    ADC_UnsignedFormat,         /*!< ADC output unsigned data format */
    ADC_2sCompletementFormat,   /*!< ADC output 2's complement data format */
} ADC_OutputCodeFormatDef;


/** 
 * @enum		ADC_DAT0FlagsDef
 * @brief		ADC interrupt source
 */        
typedef enum 
{ 
    ADC_DAT0_WDLF = ADC_DAT0_DAT0_WDLF_normal_b2,   /*!< ADC voltage window detect outside low event flag */
    ADC_DAT0_WDIF = ADC_DAT0_DAT0_WDIF_normal_b2,   /*!< ADC voltage window detect inside event flag */
    ADC_DAT0_WDHF = ADC_DAT0_DAT0_WDHF_normal_b2,   /*!< ADC voltage window detect outside high event flag */
    ADC_DAT0_CF = ADC_DAT0_DAT0_CF_mask_b2,         /*!< ADC0 conversion data-0 complete in 1-time and data ready status bit */
    ADC_DAT0_OVRF = ADC_DAT0_DAT0_OVRF_mask_b2,     /*!< ADC0 conversion data register-0 overwrite/overrun indication status bit */
} ADC_DAT0FlagsDef;


/** 
 * @enum		ADC_SUMxFlagDef
 * @brief		ADC SUMx flag declare
 */        
typedef enum 
{ 
    ADC_SUMxOVRF = ADC_SUM0_SUM0_OVRF_mask_h1,      /*!< ADC0 data sum-0,1,2 register overrun flag */
    ADC_SUMxCF = ADC_SUM0_SUM0_CF_mask_h1,          /*!< ADC0 data sum-0,1,2 accumulation complete flag */
    ADC_SUMxOF = ADC_SUM0_SUM0_OF_mask_h1,          /*!< ADC0 data sum-0,1,2 accumulation overflow flag */
    ADC_SUMxUF = ADC_SUM0_SUM0_UF_mask_h1,          /*!< ADC0 data sum-0,1,2 accumulation underflow flag */
} ADC_SUMxFlagDef;

#if (MG32_2ND || MG32_3RD)
/** 
 * @enum		ADC_DMADataSizeDef
 * @brief		Config ADC data size for DMA transmission
 */    
typedef enum 
{
    ADC_DMA_32bit,              /*!< ADC will transfer ADC0_DAT0 for DMA transmission */
    ADC_DMA_16bit,              /*!< ADC will transfer the bit[15:0] of ADC0_DAT0 for DMA transmission */
} ADC_DMADataSizeDef;

/** 
 * @enum		ADC_DMAMaskE1CNVFDef
 * @brief		Config ADC mask E1CNVF during DMA transmission
 */    
typedef enum 
{
    ADC_Mask_E1CNVF,            /*!< E1CNVF flag will be masked after ADC conversion end during DMA access */
    ADC_Assert_E1CNVF,          /*!< E1CNVF flag asserted mode select during DMA access */
} ADC_DMAMaskE1CNVFDef;


/** 
 * @enum		ADC_ChangeTimingDef
 * @brief		Config ADC change channel MUX timing 
 */    
typedef enum 
{
    ADC_ChangeMUX_E1CNVF,       /*!< Change channel MUX when E1CNVF happened. */
    ADC_ChangeMUX_ESMPF,        /*!< Change channel MUX when ESMPF happened. */
} ADC_ChangeTimingDef;

#endif

/** 
 * @struct  ADC_InitTypeDef
 * @brief   ADC Base initial structure
 */        
typedef struct 				
{ 
    ADC_ClockSourceDef ADCMainClockSelect;      /*!< Specifies whether the conversion is performed in */
    
        ADC_INTClockDivDef ADC_IntCK_Div;       /*!< Select CK_ADC divider .
                                                  This parameter can be Selected /1, /2, /4, /16 .*/                         
                                                  
        ADC_PLLClockDivDef ADC_CKPLL_Div;       /*!< Select PLL clock divider .
                                                  This parameter can be Selected /2, /4, /5, /6 .*/    
    
    ADC_DataAlignModeDef ADC_DataAlign;         /*!< Specifies whether the ADC data alignment is left or righ */
    
    ADC_ResolutionDef ADC_ResolutionSel;        /*!< Specifies whether the ADC conversion resolution 10 or 12 bit */
                                                                                                    
    ADC_DataOWDef ADC_DataOverrunEvent;         /*!< Specifies the ADC data overwritten or Keep */   
    
} ADC_InitTypeDef;   





/**
 * @name	Function announce
 *   		
 */ 
///@{  
void ADC_DeInit(ADC_Struct *ADCx);
///@}

///@{
void ADC_BaseStructure_Init(ADC_InitTypeDef* ADC_BaseInitStruct);
void ADC_Base_Init(ADC_Struct* ADCx, ADC_InitTypeDef* ADC_BaseInitStruct);
///@}

///@{
void ADC_SetPLLClockDivider(ADC_Struct* ADCx, ADC_PLLClockDivDef PLLClockDIV);
void ADC_ClockSource_Select(ADC_Struct* ADCx, ADC_ClockSourceDef ADCClockSrc);
void ADC_SetInternalClockDivider(ADC_Struct* ADCx, ADC_INTClockDivDef INTClockSrc);
///@}

///@{
void ADC_SetLowerThreshold(ADC_Struct* ADCx, int16_t LThreshold);
void ADC_SetHigherThreshold(ADC_Struct* ADCx, int16_t HThreshold);
void ADC_WindowDetectRange_Select(ADC_Struct* ADCx, ADC_WindowDetectApplyDef WINDApply);
void ADC_WindowDetect_Cmd(ADC_Struct* ADCx, FunctionalState NewState);
void ADC_Output_Select(ADC_Struct* ADCx,ADC_OutputDef ADCOutSel);
///@}

///@{
void ADC_PGA_Cmd(ADC_Struct* ADCx, FunctionalState NewState);
void ADC_SetPGAGain(ADC_Struct* ADCx, uint8_t PGAGain);
void ADC_SetPGAOffset(ADC_Struct* ADCx, uint8_t PGAOFFT);
void ADC_PGAOffsetCalibration_Cmd(ADC_Struct* ADCx, FunctionalState NewState);
///@}

///@{
#if (MG32_1ST)
void ADC_VRMCalibration(ADC_Struct* ADCx,uint8_t VRMV);
#endif
void ADC_StartCalibration(ADC_Struct* ADCx, FunctionalState NewState);
///@}

///@{
void ADC_Cmd(ADC_Struct* ADCx, FunctionalState NewState);
void ADC_DMA_Cmd(ADC_Struct* ADCx, FunctionalState NewState);
#if (MG32_2ND || MG32_3RD)
    void ADC_DMADataSize_Select(ADC_Struct* ADCx, ADC_DMADataSizeDef DMADataSize);
    void ADC_DMAMaskFlag_Select(ADC_Struct* ADCx, ADC_DMAMaskE1CNVFDef DMAMaskFlagDef);
    uint8_t ADC_GetNextConversionChannel(ADC_Struct* ADCx);
#endif
#if (MG32_1ST || MG32_3RD)
    void ADC_AutoOff_Cmd(ADC_Struct* ADCx, FunctionalState NewState);
    #if (MG32_1ST || MG32_3RD)
        void ADC_SetStartupTime(ADC_Struct* ADCx, uint16_t ADCSCNTime);
        void ADC_SetStartupDivider(ADC_Struct* ADCx, ADC_SCNTClockDivDef ADCSCNDIV);
    #endif
#endif
void ADC_WaitDataReadOut(ADC_Struct* ADCx, FunctionalState NewState);
void ADC_SetExtendSampling(ADC_Struct* ADCx, uint8_t ADCSampleTime);
///@}

///@{
void ADC_ConversionMode_Select(ADC_Struct* ADCx, ADC_ConversionModeDef ADCConvMode);
void ADC_ContinueMode_Cmd(ADC_Struct* ADCx, FunctionalState NewState);
void ADC_HoldConversion_Cmd(ADC_Struct* ADCx, FunctionalState NewState);
void ADC_MainConversionMode_Select(ADC_Struct* ADCx, ADC_MainConversionModeDef MainCM);
///@}

///@{
void ADC_TriggerSource_Select(ADC_Struct* ADCx, ADC_TriggerSourceDef ADCTrgSel);
void ADC_SoftwareConversion_Cmd(ADC_Struct* ADCx, FunctionalState NewState);
void ADC_TriggerEdge_Select(ADC_Struct* ADCx, ADC_TriggerEdgeDef ADCExtEdgeSel);
///@}

///@{
void ADC_ChannelMUX_Select(ADC_Struct* ADCx, ADC_ChannelMUX_Def ChannelSel);
void ADC_ExternalChannel_Select(ADC_Struct* ADCx, ADC_ExtChannelDef ExtCHSel);
void ADC_InternalChannel_Select(ADC_Struct* ADCx, ADC_IntChannelDef IntCHSel);
void ADC_ScanLoopChannel_Enable(ADC_Struct* ADCx, uint16_t MSKChannelSel, FunctionalState NewState);
#if (MG32_2ND || MG32_3RD)
    void ADC_ChangeMUXTiming_Select(ADC_Struct* ADCx, ADC_ChangeTimingDef ADC_ChangTimeing);
#endif
///@}

///@{
void ADC_SingleDifferentMode_Select(ADC_Struct* ADCx, ADC_ConversionTypeDef ADC_ConversionType);
///@}

///@{
void ADC_SetLimitFunction(ADC_Struct* ADCx, ADC_LimitModeDef ADCLimitMode);
void ADC_SetSum0Channel(ADC_Struct* ADCx,uint8_t Sum0ChannelSel);
void ADC_SetSum1Channel(ADC_Struct* ADCx,uint8_t Sum1ChannelSel);
void ADC_SetSum2Channel(ADC_Struct* ADCx,uint8_t Sum2ChannelSel);
void ADC_SumChannelMode_Select(ADC_Struct* ADCx,ADC_SumChannelXDef ADCSumChXDef);
void ADC_SetSumNumber(ADC_Struct* ADCx, uint8_t ADCSumNumbers);
void ADC_SumOverrunMode_Select(ADC_Struct* ADCx, ADC_SumDataOWDef ADCSumOW);
uint16_t ADC_GetSum0Flags(ADC_Struct* ADCx);
uint16_t ADC_GetSum1Flags(ADC_Struct* ADCx);
uint16_t ADC_GetSum2Flags(ADC_Struct* ADCx);
void ADC_ClearSum0Flags(ADC_Struct* ADCx, uint8_t ADC_SUMxFlag);
void ADC_ClearSum1Flags(ADC_Struct* ADCx, uint8_t ADC_SUMxFlag);
void ADC_ClearSum2Flags(ADC_Struct* ADCx, uint8_t ADC_SUMxFlag);
int16_t ADC_GetSum0Data(ADC_Struct* ADCx);
int16_t ADC_GetSum1Data(ADC_Struct* ADCx);
int16_t ADC_GetSum2Data(ADC_Struct* ADCx);
void ADC_SetSum0Data(ADC_Struct* ADCx, int16_t ADCSum0Initial);
void ADC_SetSum1Data(ADC_Struct* ADCx, int16_t ADCSum1Initial);
void ADC_SetSum2Data(ADC_Struct* ADCx, int16_t ADCSum2Initial);
///@}

///@{
void ADC_DataAlignment_Select(ADC_Struct* ADCx, ADC_DataAlignModeDef AlignMode);
void ADC_DataResolution_Select(ADC_Struct* ADCx, ADC_ResolutionDef ResolutionData);
void ADC_DataOverrunMode_Select(ADC_Struct* ADCx, ADC_DataOWDef DataOW);
uint8_t ADC_GetDAT0Flags(ADC_Struct* ADCx);
uint8_t ADC_GetDAT0Channel(ADC_Struct* ADCx);
int16_t ADC_GetDAT0Data(ADC_Struct* ADCx);
void ADC_SetDigitalOffset(ADC_Struct* ADCx, int8_t sDigiOffset);
void ADC_SetOutputCodeFormat(ADC_Struct* ADCx, ADC_OutputCodeFormatDef DatFormat);
///@}


///@{
void ADC_IT_Config(ADC_Struct* ADCx, uint32_t ADC_ITSrc, FunctionalState NewState);
void ADC_ITEA_Cmd(ADC_Struct* ADCx, FunctionalState NewState);
DRV_Return ADC_GetSingleFlagStatus(ADC_Struct* ADCx, uint32_t ADC_ITSTAFlag);
uint32_t ADC_GetAllFlagStatus(ADC_Struct* ADCx);
void ADC_ClearFlag(ADC_Struct* ADCx, uint32_t ADC_ITSTAFlag);
///@}

#endif
