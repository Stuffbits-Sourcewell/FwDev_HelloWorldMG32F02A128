/**
 ******************************************************************************
 * @file    driver_rcc_mg32x02z.c
 * @author  KS
 * @version 01.00
 * @date    27-MAR-2015
 * @brief   Driver for enabling the PLL mode in clock options with
 *  		   external crystal.
 *  		   + The Crystal and PLL output frequency in MHz
 *  		   is selected in header file.
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
 * Date      : 27-MAR-2015
 * Brief     : created file
 *
 *******************************************************************************
 */

/*
 *******************************************************************************
 *                               PRIVATE INCLUDES
 *******************************************************************************
 */
#include <driver_rcc_mg32x02z.h>
#include "system_MG32x02z.h"

/*
 *******************************************************************************
 *                               PRIVATE MACROS
 *******************************************************************************
 */
#define KHZ_CONVERSION_FACTOR      	    (1000U)


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
 * @fn  void Rcc_ClockInit(void)
 ******************************************************************************
 * @brief   System Clock initialization function
 * @note    User should select clock source either internal or external from
 * 		   driver header of same file.
 * @param   None
 * @retval  None
 ******************************************************************************
 */
void Rcc_ClockInit(void)
{
	// Flash wait state setting
	MEM->KEY.MBIT.KEY = 0xA217;
	MEM->CR0.W = (MEM->CR0.W & (~MEM_CR0_FWAIT_mask_w)) | (MEM_CR0_FWAIT_zero_w| MEM_CR0_FWAIT_one_w);

	MEM->KEY.MBIT.KEY = 0x0000;

	// Unprotect CSC module
	CSC->KEY.MBIT.KEY = 0xA217;
	// Set PLLI_DIV, PLLO_DIV, AHB_DIV, APB_DIV, USB_DIV and UT_DIV
	//PLL input div/2
	//PLL output div/4
	//EXTAL = 12 Mhz
	//PLL output = (12 *16)/2/2 =24mHz
	CSC->DIV.W = (CSC_DIV_PLLI_DIV_div2_w |CSC_DIV_PLLO_DIV_div2_w);                     //  | CSC_DIV_USB_DIV_div2_w //Harshal
	// Set PLL_MDS, PLLI_SEL, PLL_VCOS, PLL_MUL, PLL_MULX and XOSC_GN
	// PLL_MULX = 0xF
	CSC->PLL.W = (CSC_PLL_PLL_MDS_mask_w   | (8192 - 0x00000200) | CSC_PLL_XOSC_GN_medium_w);

	// When XOSC is medium gain, and wizard configuration enables "miss clock detect", will enable "miss clock detect".
	CSC->CR0.MBIT.MCD_DIS = 0;

	CSC->CR0.W |= CSC_CR0_IHRCO_EN_enable_w;

	/*!< Module clock ready status check */
	// Check CK_HS success
	while(CSC->STA.MBIT.HS_STA != (0x01));


	/*===== CK_MAIN Select =====*/
	// Enable PLL
	CSC->CR0.MBIT.PLL_EN = 1;

	// Wait PLL ready
	while(CSC->STA.MBIT.PLL_STA == 0);
	// Clear PLLF
	CSC->STA.B[0] = CSC_STA_PLLF_mask_b0;

	// PLL output is Main clock .
	CSC->CR0.MBIT.MAIN_SEL = 0x02;

	// System tick external clock select.
//	CSC->CR0.MBIT.ST_SEL= 0;

	/*===== FPGA mask CK_HS =====*/
	// Check CK_HS success
	while(CSC->STA.MBIT.MAIN_STA != 0x04);

	/*===== Disable Not Used Clock Source =====*/
	// When CK_HS and CK_HS2 not select CK_IHRCO

	if((CSC->CR0.MBIT.HS_SEL != 0)&&(CSC->CR0.MBIT.HS2_SEL != 0))
		CSC->CR0.MBIT.IHRCO_EN = 0;

	// Protect CSC module
	CSC->KEY.MBIT.KEY = 0x0000;

	//	SystemCoreClock = CONF_CK_AHB_FREQ;

	SystemCoreClockUpdate();

	// Protect CSC module
	CSC->KEY.MBIT.KEY = 0x0000;

}//End of Rcc_ClockInit


/**
 ******************************************************************************
 * @fn  uint32_t Rcc_GetSysClkValKhz(void)
 ******************************************************************************
 * @brief   Routine to get the system Clock Value in Mhz set in header and
 *  		   return it in Khz
 * @note    None
 * @param   None
 * @retval  sys_clk_khz : system clock value in Khz
 ******************************************************************************
 */
uint32_t Rcc_GetSysClkValKhz(void)
{
	uint32_t sys_clk_khz = 0;
	sys_clk_khz = SystemCoreClock/KHZ_CONVERSION_FACTOR;
	return (sys_clk_khz);

}//End of GetSysClkValKhz()

/**
 ******************************************************************************
 * @fn  uint32_t Rcc_GetAhbClkValKhz(void)
 ******************************************************************************
 * @brief   Routine to get the AHB Clock Value in Mhz set in header andreturn
 *          it in Khz
 * @note    None
 * @param   None
 * @retval  ahb_clk_khz : AHB clock value in Khz
 ******************************************************************************
 */
uint32_t Rcc_GetAhbClkValKhz(void)
{
	uint32_t ahb_clk_khz = 0;

	ahb_clk_khz = (SystemCoreClock >> AHB_CLOCK_DIVISOR)/KHZ_CONVERSION_FACTOR;
	return (ahb_clk_khz);

}//End of GetAHBClkValKhz()

/**
 ******************************************************************************
 * @fn  uint32_t Rcc_GetPclkValKhz(void)
 ******************************************************************************
 * @brief   Routine to get the pclk Clock Value in Mhz set in header and return
 *          it in Khz
 * @note    None
 * @param   None
 * @retval  pclk_khz : pclk clock value in Khz
 ******************************************************************************
 */
uint32_t Rcc_GetPclkValKhz(void)
{
	uint32_t pclk_khz = 0;

	pclk_khz = (SystemCoreClock >> APB_CLOCK_DIVISOR)/KHZ_CONVERSION_FACTOR;
	return (pclk_khz);

}//End of GetPclkValKhz()



/*-------------------------------END OF FILE----------------------------------*/
