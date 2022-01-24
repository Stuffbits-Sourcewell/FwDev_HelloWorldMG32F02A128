/**
******************************************************************************
* @file    driver_uart_mg32x02z.h
* @author  PVG
* @version 01.01
* @date    31-MAR-2015
* @brief   This file contains all the functions prototypes for the USART
* 		   firmware library.
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
* Author    : NGS
* Date      : 31-MAR-2015
* Brief     : created file
*
*******************************************************************************
* Change    : 02
* Author    : KS
* Date      : 30-APR-2015
* Brief     : changed function body of Uart_ClockEnable,Uart_EnableInterruptNVIC
* 			  Uart_SelClkSrc by changing switch case to if else
* 			  block.
* 			  Removed typedef sel_uart_t.
*
*******************************************************************************
*/

#ifndef DRIVER_UART_STM32F0XX_H_
#define DRIVER_UART_STM32F0XX_H_
/*
*******************************************************************************
*                              	   INCLUDES
*******************************************************************************
*/
#include "driver_rcc_mg32x02z.h"
#include "mg32x02z.h"
#include "std_data_types.h"
#include "MG32x02z_CSC.h"
#include "MG32x02z_URT.h"

/*
*******************************************************************************
*                               PUBLIC MACROS
*******************************************************************************
*/
//None

/*
*******************************************************************************
*                         PUBLIC TYPEDEF DECLARATION
*******************************************************************************
*/
typedef enum
{
	UART_BAUDRATE_1200   = 1200,
	UART_BAUDRATE_2400   = 2400,
	UART_BAUDRATE_4800   = 4800,
	UART_BAUDRATE_9600   = 9600,
	UART_BAUDRATE_19200  = 19200,
	UART_BAUDRATE_38400  = 38400,
	UART_BAUDRATE_57600  = 57600,
	UART_BAUDRATE_115200 = 115200
}usart_baudrate_sel_t;


typedef enum
{
	UART_NONE,
	UART_ODD,
	UART_EVEN
}usart_parity_sel_t;

typedef enum
{
	UART_7BIT,
	UART_8BIT,
}usart_word_len_t;

typedef enum
{
	UART_0_5STOPBIT ,
	UART_1STOPBIT ,
	UART_1_5STOPBIT ,
	UART_2STOPBIT
}usart_stopbit_sel_t;

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
extern void Uart_ClockEnable(URT_Struct* URTx);
extern void Uart_EnableInterruptNVIC(URT_Struct* URTx);

extern void Uart_SetBaudrate(URT_Struct* URTx ,uint32_t usart_clk_khz , usart_baudrate_sel_t baud_rate);
extern void Uart_SetParity(URT_Struct* URTx, usart_parity_sel_t parity);
extern void Uart_SetWordLength(URT_Struct* URTx, usart_word_len_t word_len);
extern void Uart_SetStopbits(URT_Struct* URTx, usart_stopbit_sel_t stopbit_sel);

extern void Uart_EnableRxInterrupt(URT_Struct* URTx);
extern void Uart_DisableRxInterrupt(URT_Struct* URTx);
extern void Uart_EnableTxInterrupt(URT_Struct* URTx);
extern void Uart_DisableTxInterrupt(URT_Struct* URTx);

extern void Uart_Enable(URT_Struct* URTx);
extern void Uart_Disable(URT_Struct* URTx);
#endif //driver_uart_STM32F0XX_H_

/*-------------------------------END OF FILE----------------------------------*/
