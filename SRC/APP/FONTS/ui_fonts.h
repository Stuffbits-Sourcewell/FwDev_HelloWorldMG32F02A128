/**
******************************************************************************
* @file    flash_interface.h
* @author  KS
* @version 01.00
* @date    30-MAR-2015
* @brief   File includes function prototypes to interface with device flash
*          memory
******************************************************************************
* @attention
* @{
* <h2><center>&copy; Copyright 2017 StuffBits Technologies LLP </center></h2>
*			                All rights reserved.
* An unpublished work by Petrotec  Limited . This material contains
* CONFIDENTIAL INFORMATION that is the property of Petrotec  Limited .
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
* Date      : 30-MAR-2015
* Brief     : created file
*
*******************************************************************************
*/

#ifndef UI_FONTS_H_
#define UI_FONTS_H_


/*
*******************************************************************************
*                                INCLUDE FILES
*******************************************************************************
*/

#include "std_data_types.h"

/*
*******************************************************************************
*                          PUBLIC MACROS & CONSTANTS
*******************************************************************************
*/

/// Data stored for FONT AS A WHOLE
typedef struct
{
	uint8_t height; /*  Character height in bytes */
	uint8_t start_char; /*  Start character */
	const uint16_t *font_descr; /*  Character descriptor array */
	const uint8_t *font_bitmap; /*  Character bitmap array */
	const uint8_t padding;
} gfont_t;

extern const gfont_t swis721CnBT_18pt_info;
extern const gfont_t digifaceWide_48pt_info ;
extern const gfont_t digifaceWide_30pt_info ;
extern const gfont_t bookAntiqua_18pt_info;
extern const gfont_t bookAntiqua_28pt_info;


/*
*******************************************************************************
*                         PUBLIC VARIABLE DECLARATION
*******************************************************************************
*/



/*
*******************************************************************************
*                         PUBLIC FUNCTION DECLARATION
*******************************************************************************
*/

#endif	/*UI_FONTS_H_*/
