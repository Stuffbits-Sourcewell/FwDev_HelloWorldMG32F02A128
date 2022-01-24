/**
  ******************************************************************************
  * @file      startup_stm32l072xx.s
  * @author    MCD Application Team
  * @brief     STM32L072xx Devices vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M0+ processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m0plus
  .fpu softvfp
  .thumb

.global  g_pfnVectors
.global  Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word  _sidata
/* start address for the .data section. defined in linker script */
.word  _sdata
/* end address for the .data section. defined in linker script */
.word  _edata
/* start address for the .bss section. defined in linker script */
.word  _sbss
/* end address for the .bss section. defined in linker script */
.word  _ebss

    .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:
   ldr   r0, =_estack
   mov   sp, r0          /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit

/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
    bl __libc_init_array
/* Call the application's entry point.*/
  bl  main

LoopForever:
    b LoopForever


.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
  .size  g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  0
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler

	.word    WWDT_IRQHandler        //WindowWatchdog
	.word    SYS_IRQHandler        //SystemglobalInterrupt
	.word    0xFFFFFFFF        //Reserved
	.word    EXINT0_IRQHandler        //EXICEXINT0
	.word    EXINT1_IRQHandler        //EXICEXINT1
	.word    EXINT2_IRQHandler        //EXICEXINT2
	.word    EXINT3_IRQHandler        //EXICEXINT3
	.word    COMP_IRQHandler        //AnalogComparatorsglobalInterrupt
	.word    DMA_IRQHandler        //DMAallchannelglobalInterrupt
	.word    0xFFFFFFFF        //Reserved
	.word    ADC_IRQHandler        //ADCglobalInterrupt
	.word    DAC_IRQHandler        //DACglobalInterrupt
	.word    TM0x_IRQHandler        //TimerTM0xglobalInterrupt
	.word    TM10_IRQHandler        //TimerTM10
	.word    TM1x_IRQHandler        //TimerTM1xglobalInterrupt
	.word    TM20_IRQHandler        //TimerTM20
	.word    TM2x_IRQHandler        //TimerTM2xglobalInterrupt
	.word    TM3x_IRQHandler        //TimerTM3xglobalInterrupt
	.word    0xFFFFFFFF        //Reserved
	.word    0xFFFFFFFF        //Reserved
	.word    URT0_IRQHandler        //UARTURT0
	.word    URT123_IRQHandler        //UARTURT1/2/3globalInterrupt
	.word    URT4x_IRQHandler        //UARTURT4/5/6/7/..globalInterrupt
	.word    0xFFFFFFFF        //Reserved
	.word    SPI0_IRQHandler        //SPI0
	.word    SPIx_IRQHandler        //SPIxglobalInterrupt
	.word    0xFFFFFFFF        //Reserved
	.word    0xFFFFFFFF        //Reserved
	.word    I2C0_IRQHandler        //I2C0
	.word    I2Cx_IRQHandler        //I2CxglobalInterrupt
	.word    USB_IRQHandler        //USB
	.word    APX_IRQHandler        //APX

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

   .weak      NMI_Handler
   .thumb_set NMI_Handler,Default_Handler

   .weak      HardFault_Handler
   .thumb_set HardFault_Handler,Default_Handler

   .weak      SVC_Handler
   .thumb_set SVC_Handler,Default_Handler

   .weak      PendSV_Handler
   .thumb_set PendSV_Handler,Default_Handler

   .weak      SysTick_Handler
   .thumb_set SysTick_Handler,Default_Handler

   .weak      WWDT_IRQHandler
   .thumb_set WWDT_IRQHandler,Default_Handler

   .weak      SYS_IRQHandler
   .thumb_set SYS_IRQHandler,Default_Handler

   .weak      EXINT0_IRQHandler
   .thumb_set EXINT0_IRQHandler,Default_Handler

   .weak      EXINT1_IRQHandler
   .thumb_set EXINT1_IRQHandler,Default_Handler

   .weak      EXINT2_IRQHandler
   .thumb_set EXINT2_IRQHandler,Default_Handler

   .weak      EXINT3_IRQHandler
   .thumb_set EXINT3_IRQHandler,Default_Handler

   .weak      COMP_IRQHandler
   .thumb_set COMP_IRQHandler,Default_Handler

   .weak      DMA_IRQHandler
   .thumb_set DMA_IRQHandler,Default_Handler

   .weak      ADC_IRQHandler
   .thumb_set ADC_IRQHandler,Default_Handler

   .weak      DAC_IRQHandler
   .thumb_set DAC_IRQHandler,Default_Handler

   .weak      TM0x_IRQHandler
   .thumb_set TM0x_IRQHandler,Default_Handler

   .weak      TM10_IRQHandler
   .thumb_set TM10_IRQHandler,Default_Handler

   .weak      TM1x_IRQHandler
   .thumb_set TM1x_IRQHandler,Default_Handler

   .weak      TM20_IRQHandler
   .thumb_set TM20_IRQHandler,Default_Handler

   .weak      TM2x_IRQHandler
   .thumb_set TM2x_IRQHandler,Default_Handler

   .weak      TM3x_IRQHandler
   .thumb_set TM3x_IRQHandler,Default_Handler

   .weak      URT0_IRQHandler
   .thumb_set URT0_IRQHandler,Default_Handler

   .weak      URT123_IRQHandler
   .thumb_set URT123_IRQHandler,Default_Handler

   .weak      URT4x_IRQHandler
   .thumb_set URT4x_IRQHandler,Default_Handler

   .weak      SPI0_IRQHandler
   .thumb_set SPI0_IRQHandler,Default_Handler

   .weak      SPIx_IRQHandler
   .thumb_set SPIx_IRQHandler,Default_Handler

   .weak      I2C0_IRQHandler
   .thumb_set I2C0_IRQHandler,Default_Handler

   .weak      I2Cx_IRQHandler
   .thumb_set I2Cx_IRQHandler,Default_Handler

   .weak      USB_IRQHandler
   .thumb_set USB_IRQHandler,Default_Handler

   .weak      APX_IRQHandler
   .thumb_set APX_IRQHandler,Default_Handler


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

