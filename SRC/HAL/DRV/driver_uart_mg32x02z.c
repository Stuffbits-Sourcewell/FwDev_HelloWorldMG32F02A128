/**
 ******************************************************************************
 * @file    driver_uart_mg32x02z.c
 * @author  NGS
 * @version 01.01
 * @date    31-MAR-2015
 * @brief   This file provides firmware functions to manage the (USART)
 * 			+ USART Initialization
 * 			+ USART Transmit Receive
 * 			+ USART interrupts
 *
 *
 ******************************************************************************
 * @attention
 * @{
 * <h2><center>&copy; Copyright 2016 SpryLogic Technologies </center></h2>
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
 * Author    : KS
 * Date      : 31-MAR-2015
 * Brief     : created file
 *
 *******************************************************************************
 */

/*
 *******************************************************************************
 *                               PRIVATE INCLUDES
 *******************************************************************************
 */
#include <driver_uart_mg32x02z.h>

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
 ******************************************************************************
 * @fn vvoid Uart_ClockEnable(URT_Struct* URTx)
 ******************************************************************************
 * @brief   enables clock for selected USART
 * @note    None
 * @param   URTx : Select URT0/URT1/USART3/USART4
 * @retval  None
 ******************************************************************************
 */
void Uart_ClockEnable(URT_Struct* URTx)
{
	if(URTx == URT0)
	{
		//Enable clock to UART1
		CSC->APB0.W |= CSC_APB0_URT0_EN_mask_w;
	}
	else if(URTx == URT1)
	{
		//Enable clock to UART2
		CSC->APB0.W |= CSC_APB0_URT1_EN_mask_w;
	}
	else if(URTx == URT2)
	{
		//Enable clock to UART2
		CSC->APB0.W |= CSC_APB0_URT2_EN_mask_w;
	}
	else if(URTx == URT7)
	{
		//Enable clock to UART2
		CSC->APB0.W |= CSC_APB0_URT7_EN_mask_w;
	}
	else
	{
		//Invalid argument
		while(1);

	}
}//End of Uart_ClockEnable()

/**
 ******************************************************************************
 * @fn  void Uart_EnableInterruptNVIC(URT_Struct* URTx)
 ******************************************************************************
 * @brief   This Routine enables interrupt in the Interrupt controller
 * 		   for respective UART module.
 * @note    None
 * @param   GPIOx : URT0/URT1/USART3/USART4
 * @retval  None
 ******************************************************************************
 */
void Uart_EnableInterruptNVIC(URT_Struct* URTx)
{
	if(URTx == URT0)
	{
		NVIC_EnableIRQ(URT0_IRQn);
	}
	else if((URTx == URT1) || (URTx == URT2) )
	{
		NVIC_EnableIRQ(URT123_IRQn);
	}
	else if((URTx == URT4) || (URTx == URT7))
	{
		NVIC_EnableIRQ(URT4x_IRQn);
	}
	else
	{
		//Invalid argument
		while(1);
	}
}//End of Uart_EnableInterruptNVIC()


/**
 ******************************************************************************
 * @fn void Uart_SetBaudrate(URT_Struct* URTx ,usart_baudrate_sel_t baud_rate)
 ******************************************************************************
 * @brief   Set Baudrate for Selected UART
 * @note    Baud-Rate = f(CK_URTx) / (PSR+1) / (RLR+1) / (OS_NUM+1)
 * @param   URTx   : URT0/URT1/USART3/USART4
 * @param   baud_rate: Setting baudrate from given values
 * @retval  None
 ******************************************************************************
 */
void Uart_SetBaudrate(URT_Struct* URTx ,uint32_t usart_clk_khz , usart_baudrate_sel_t baud_rate)
{
	uint32_t over_samp_no;
	uint32_t temp;

	uint8_t best_sol,over_sample,remainder;
	//==========================================
	//Baud rate
	temp = usart_clk_khz * 1000 / baud_rate;
	if(temp < 8)
	{
		while(1);//error
	}
	//================TX and RX oversampling value===================
	best_sol = 0;

	for(over_sample=8;over_sample<32;over_sample++)
	{
		remainder = temp % over_sample;
		if(remainder==0)
		{
			if( (temp / over_sample)<4096)
			{
				over_samp_no = over_sample;
				break;
			}
		}
		else
		{
			if((over_sample-remainder)>best_sol || (over_sample-remainder)==best_sol)
			{
				best_sol = over_sample - remainder;
				over_samp_no = over_sample;
			}
		}
	}

	URTx->CLK.W  &= (~(URT_CLK_TX_CKS_mask_w| URT_CLK_RX_CKS_mask_w | URT_CLK_CK_SEL_mask_w));
	temp = temp / (over_samp_no);
	if(temp>4096)
	{
		while(1);//Error
	}
	URTx->RLR.H[0] = (temp - 1);


	over_samp_no = over_samp_no - 1;
	URTx->CR1.B[3] = over_samp_no;
	URTx->CR1.B[1] = over_samp_no;

//    URTx->CLK.W |= (URT_CLK_BR_MDS_separated_w | URT_CLK_BR_EN_enable_w);

    URTx->CLK.W |= (URT_CLK_BR_MDS_combined_w | URT_CLK_BR_EN_enable_w);
}//End of Uart_SetBaudrate()



/**
 ******************************************************************************
 * @fn void Uart_SetParity(URT_Struct* URTx, usart_parity_sel_t parity)
 ******************************************************************************
 * @brief   Set Baudrate for Selected UART
 * @note    None
 * @param   URTx   : URT0/URT1/USART3/USART4
 * @param   parity:
 * @retval  None
 ******************************************************************************
 */
void Uart_SetParity(URT_Struct* URTx, usart_parity_sel_t parity)
{
	switch(parity)
	{
	case UART_ODD:
		URTx->CR1.W |= (URT_CR1_TXPAR_EN_mask_w |URT_CR1_RXPAR_EN_mask_w);
		URTx->CR1.W |= (URT_CR1_TXPAR_POL_mask_w | URT_CR1_RXPAR_POL_mask_w);
		break;

	case UART_EVEN:
		URTx->CR1.W |= (URT_CR1_TXPAR_EN_mask_w |URT_CR1_RXPAR_EN_mask_w);
		URTx->CR1.W &= ~(URT_CR1_TXPAR_POL_mask_w | URT_CR1_RXPAR_POL_mask_w);
		break;

	case UART_NONE:
	default:
		URTx->CR1.W &= ~(URT_CR1_TXPAR_EN_mask_w |URT_CR1_RXPAR_EN_mask_w) ;
		break;
	}
}//End of Uart_SetParity()


/**
 ******************************************************************************
 * @fn void Uart_SetWordLength(URT_Struct* URTx, usart_word_len_t word_len)
 ******************************************************************************
 * @brief   Set Baudrate for Selected UART
 * @note    None
 * @param   URTx   : URT0/URT1/USART3/USART4
 * @param   baud_rate: Setting baudrate from given values
 * @retval  None
 ******************************************************************************
 */
void Uart_SetWordLength(URT_Struct* URTx, usart_word_len_t word_len)
{
	switch(word_len)
	{
	case UART_7BIT:
		URTx->CR1.W &= ~(URT_CR1_TXDSIZE_mask_w |URT_CR1_RXDSIZE_mask_w);
		URTx->CR1.W |= (URT_CR1_TXDSIZE_7bit_w | URT_CR1_RXDSIZE_7bit_w);
		break;

	case UART_8BIT:
	default:
		URTx->CR1.W &= ~(URT_CR1_TXDSIZE_mask_w |URT_CR1_RXDSIZE_mask_w);
		break;
	}
}//End of Uart_SetWordLength()


/**
 ******************************************************************************
 * @fn void Uart_SetStopbits(URT_Struct* URTx, usart_stopbit_sel_t stopbit_sel)
 ******************************************************************************
 * @brief   Set Stopbits for Selected UART
 * @note    None
 * @param   URTx   : URT0/URT1/USART3/USART4
 * @param   parity:
 * @retval  None
 ******************************************************************************
 */
void Uart_SetStopbits(URT_Struct* URTx, usart_stopbit_sel_t stopbit_sel)
{
	switch(stopbit_sel)
	{
	case UART_0_5STOPBIT:
		URTx->CR1.W &= ~(URT_CR1_TXSTP_LEN_mask_w |URT_CR1_RXSTP_LEN_mask_w);
		break;

	case UART_1STOPBIT:
		URTx->CR1.W &= ~(URT_CR1_TXSTP_LEN_mask_w |URT_CR1_RXSTP_LEN_mask_w);
		URTx->CR1.W |= (URT_CR1_TXSTP_LEN_1bit_w |URT_CR1_RXSTP_LEN_1bit_w);
		break;

	case UART_1_5STOPBIT:
		URTx->CR1.W &= ~(URT_CR1_TXSTP_LEN_mask_w |URT_CR1_RXSTP_LEN_mask_w);
		URTx->CR1.W |= (URT_CR1_TXSTP_LEN_1_5bit_w |URT_CR1_RXSTP_LEN_1_5bit_w);
		break;

	case UART_2STOPBIT:
		URTx->CR1.W |= (URT_CR1_TXSTP_LEN_2bit_w |URT_CR1_RXSTP_LEN_2bit_w);
		break;

	}
}//End of Uart_SetStopbits()

/**
 ******************************************************************************
 * @fn void Uart_EnableRxInterrupt(URT_Struct* URTx)
 ******************************************************************************
 * @brief   Enable Receive Interrupt for UART
 * @note    None
 * @param   URTx : URT0/URT1/USART3/USART4
 * @retval  None
 ******************************************************************************
 */
void Uart_EnableRxInterrupt(URT_Struct* URTx)
{
	URTx->INT.W |= URT_INT_RX_IE_mask_w|URT_INT_IEA_mask_w |URT_INT_UG_IE_mask_w;

}//End of Uart_EnableRxInterrupt()

/**
 ******************************************************************************
 * @fn void Uart_DisableRxInterrupt(URT_Struct* URTx)
 ******************************************************************************
 * @brief   Disable Receive Interrupt for UART
 * @note    None
 * @param   URTx : URT0/URT1/USART3/USART4
 * @retval  None
 ******************************************************************************
 */
void Uart_DisableRxInterrupt(URT_Struct* URTx)
{
	URTx->INT.W &= ~(URT_INT_RX_IE_mask_w);
}//End of Uart_DisableRxInterrupt()

/**
 ******************************************************************************
 * @fn void Uart_EnableTxInterrupt(URT_Struct* URTx)
 ******************************************************************************
 * @brief   Enable Transmit Interrupt for UART
 * @note    None
 * @param   URTx : URT0/URT1/USART3/USART4
 * @retval  None
 ******************************************************************************
 */
void Uart_EnableTxInterrupt(URT_Struct* URTx)
{
	URTx->INT.W |=  URT_INT_TX_IE_mask_w |URT_INT_IEA_mask_w |URT_INT_UG_IE_mask_w;

}//End of Uart_EnableTxInterrupt()

/**
 ******************************************************************************
 * @fn void Uart_DisableTxInterrupt(URT_Struct* URTx)
 ******************************************************************************
 * @brief   Disable Transmit Interrupt for UART
 * @note    None
 * @param   URTx : URT0/URT1/USART3/USART4
 * @retval  None
 ******************************************************************************
 */
void Uart_DisableTxInterrupt(URT_Struct* URTx)
{
	URTx->INT.W &=  ~(URT_INT_TX_IE_mask_w );

}//End of Uart_DisableTxInterrupt()


/**
 ******************************************************************************
 * @fn void Uart_Enable(URT_Struct* URTx)
 ******************************************************************************
 * @brief   Enabling USART module for communication
 * @note    None
 * @param   URTx : URT0/URT1/USART3/USART4
 * @retval  None
 ******************************************************************************
 */
void Uart_Enable(URT_Struct* URTx)
{

    //=============================
    //1. Set URT mode
    //2. Data line is 2 line
    //3. RX shadow buffer level is 1byte.
    //4. RX oversampling majority vote set. (3 sample bits method)
    URTx->CR0.W = (URTx->CR0.W & (~ (URT_CR0_MDS_mask_w | URT_CR0_DAT_LINE_mask_w | URT_CR0_RX_TH_mask_w | URT_CR0_OS_MDS_mask_w)));

    //============================
    //1. Enable RX & TX
    //2. Enable URT
    URTx->CR2.W = URTx->CR2.W | (URT_CR2_TX_EN_mask_w | URT_CR2_RX_EN_mask_w);
    URTx->CR0.W = URTx->CR0.W | URT_CR0_EN_mask_w;
	URTx->CR4.W |= (URT_CR4_RDAT_CLR_mask_w | URT_CR4_TDAT_CLR_mask_w);

}//End of Uart_Enable()

/**
 ******************************************************************************
 * @fn void Uart_Disable(URT_Struct* URTx)
 ******************************************************************************
 * @brief   Disable USART module for communication
 * @note    None
 * @param   URTx : URT0/URT1/USART3/USART4
 * @retval  None
 ******************************************************************************
 */
void Uart_Disable(URT_Struct* URTx)
{
	URTx->CR2.W &= ~(URT_CR2_TX_EN_mask_w | URT_CR2_RX_EN_mask_w);
	URTx->CR0.W &= ~URT_CR0_EN_mask_w;

}//End of Uart_Enable()
/*-------------------------------END OF FILE----------------------------------*/
