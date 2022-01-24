/**
******************************************************************************
* @file    std_data_types.h
* @author  Nasreen Shaikh
* @version 01.00
* @date    30-MAR-2018
* @brief   Contains basic integer data types redefined to enable porting of
*          code on different compiler platforms
******************************************************************************
* @attention
* @{
* <h2><center>&copy; Copyright 2017 Stuffbits Technologies </center></h2>
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
* Author    : Nasreen Shaikh
* Date      : 30-MAR-2018
* Brief     : created file
*
*******************************************************************************
*/
#ifndef STD_DATA_TYPES_H_
#define STD_DATA_TYPES_H_

/*
*******************************************************************************
*                                INCLUDE FILES                                   
*******************************************************************************
*/
//None

/*
*******************************************************************************
*                          PUBLIC MACROS & CONSTANTS
*******************************************************************************
*/

#ifdef	FALSE
#undef	FALSE
#endif
#define FALSE	(0)

#ifdef	TRUE
#undef	TRUE
#endif
#define	TRUE	(1)

#ifdef	NULL
#undef	NULL
#endif
#define NULL	(0)

#ifdef int8_t
#undef int8_t
#endif
typedef signed char 			int8_t;


#ifdef int16_t
#undef int16_t
#endif
typedef signed short int    	int16_t;


#ifdef int32_t
#undef int32_t
#endif
typedef signed long int     	int32_t;

#ifdef int64_t
#undef int64_t
#endif
typedef signed long long     	int64_t;

#ifdef uint8_t
#undef uint8_t
#endif
typedef unsigned char       	uint8_t;


#ifdef uint16_t
#undef uint16_t
#endif
typedef unsigned short int  	uint16_t;


#ifdef uint32_t
#undef uint32_t
#endif
typedef unsigned long int   	uint32_t;

#ifdef uint64_t
#undef uint64_t
#endif
typedef unsigned long long   	uint64_t;

#ifdef vuint8_t
#undef vuint8_t
#endif
typedef volatile uint8_t        vuint8_t;

#ifdef vuint16_t
#undef vuint16_t
#endif
typedef volatile uint16_t       vuint16_t;

#ifdef vuint32_t
#undef vuint32_t
#endif
typedef volatile uint32_t       vuint32_t;

#ifdef bool_t
#undef bool_t
#endif
typedef unsigned char       	bool_t;


typedef float             		float32_t;


#define MEM_CRC_SECTION				__attribute__((section(".code_crc_sec")))
#define WELMEC_SECTION				__attribute__((section(".welmec_sec")))

/*
*******************************************************************************
*                         PUBLIC VARIABLE DECLARATION
*******************************************************************************
*/

//None

/*
*******************************************************************************
*                         PUBLIC FUNCTION DECLARATION
*******************************************************************************
*/
#endif /* STD_DATA_TYPES_H_ */
/*-------------------------------END OF FILE----------------------------------*/
