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

#ifndef TFT_TOUCH_INTERFACE_H_
#define TFT_TOUCH_INTERFACE_H_


/*
*******************************************************************************
*                                INCLUDE FILES
*******************************************************************************
*/
#include "tft_interface_ST7789.h"

/*
*******************************************************************************
*                          PUBLIC MACROS & CONSTANTS
*******************************************************************************
*/
#define MAX_NO_KEYS						(20U)




typedef struct
{
	uint16_t tx;
	uint16_t ty;
	uint16_t tx1;
	uint16_t ty1;
	void (*KeyPressedFunc)(void);
}key_db_t;

typedef struct
{
	key_db_t 	key_db[MAX_NO_KEYS];
	uint8_t		key_pressed_value;
	bool_t		is_key_press_event;
	uint8_t 	no_of_keys;
}touchkey_db_t;


/*
*******************************************************************************
*                         PUBLIC VARIABLE DECLARATION
*******************************************************************************
*/

// None


/*
*******************************************************************************
*                         PUBLIC FUNCTION DECLARATION
*******************************************************************************
*/

extern void Touch_Read(void);
extern point_db_t *GetTouchValue(void);


//#endif
#endif /* TFT_TOUCH_INTERFACE_H_ */
/*-------------------------------END OF FILE----------------------------------*/
