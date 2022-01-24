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

#ifndef TFT_INTERFACE_ST7789_H_
#define TFT_INTERFACE_ST7789_H_


/*
*******************************************************************************
*                                INCLUDE FILES                                   
*******************************************************************************
*/

#include "string.h"
#include <hal_adc_mg32x02z.h>
#include "sys_tick.h"
#include "ui_fonts.h"
#include <driver_gpio_mg32x02z.h>


/*
*******************************************************************************
*                          PUBLIC MACROS & CONSTANTS                                
*******************************************************************************
*/


#define COLOUR_BLACK					(0x0000)
#define COLOUR_BLUE						(0x001F)
#define COLOUR_GREEN					(0x07E0)
#define COLOUR_CYAN						(0x07FF)
#define COLOUR_GREY						(0x8410)
#define COLOUR_DGREY					(0x4208)
#define COLOUR_RED						(0xF800)
#define COLOUR_YELLOW					(0xFFE0)
#define COLOUR_WHITE					(0xFFFF)
#define	COLOUR_NEW						(0x07FF)
#define COLOUR_LIGHT_YELLOW				(0xFFEC)

typedef enum
{
	HORIZONTAL_SCREEN,
	HORIZONTAL_1_SCREEN,
	VERTICAL_SCREEN,
	VERTICAL_BGR_SCREEN,
	VERTICAL_1_SCREEN,
	TEST_SCREEN
}screen_direction_t;

typedef enum
{
	HORIZONTAL,
	VERTICAL
}direction_t;

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
	bool_t key_sense;
}point_db_t;




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

extern void TFT_Init(void);
extern void setRotation(uint8_t r, bool_t BGR_flag);
extern void Set_ScreenDir(screen_direction_t screen_direction);
extern void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
extern void Draw_Icon(int16_t x, int16_t y, int16_t w, int16_t h,const uint8_t* data, uint16_t front_colour, uint16_t back_colour);
extern void Draw_Line(int16_t x, int16_t y, direction_t direction,uint16_t colour, uint8_t thickness, uint16_t length);
extern void Draw_Margin(uint8_t margin, uint16_t colour, uint8_t thickness);
extern void Draw_Table(int16_t x, int16_t y, uint16_t no_co, uint16_t no_ro, uint16_t w, uint16_t h);
extern void Draw_Rectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2,  uint16_t colour, uint8_t thickness);

extern void TftWriteText(int16_t x, int16_t y, const gfont_t* font_info, char *data_ptr, uint8_t len, uint16_t txt_colour, uint16_t bk_colour );
extern void TftDispDigits(char *data_ptr , int y_offset);

extern uint16_t Get_Width(void);
extern uint16_t Get_Height(void);


//#endif

#endif /* TFT_INTERFACE_ST7789_H_ */
/*-------------------------------END OF FILE----------------------------------*/
