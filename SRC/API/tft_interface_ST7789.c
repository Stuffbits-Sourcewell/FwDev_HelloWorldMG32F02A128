/**
******************************************************************************
* @file    flash_interface.c
* @author  KS
* @version 01.00
* @date    30-MAR-2015
* @brief   This file provides routines write and read to EEPROM/Flash
* 			Memory map for data to be stored and retrieved should be defined
* 			in header.
* 			+ EEPROMWriteData() can be called to write the desired data at
* 			  location defined by memory map in the EEPROM/Flash
* 			+ EEPROMReadData() can be used to read the data from the Flash.
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


/*
*******************************************************************************
*                                INCLUDE FILES                                   
*******************************************************************************
*/

#include "tft_interface_ST7789.h"

/*
*******************************************************************************
*                          PRIVATE MACROS & CONSTANTS                                
*******************************************************************************
*/

#define TFTLCD_Delay_10us				0x00F5

static const uint8_t ST7789_regValues[] = {
		0x11, 0,
		TFTLCD_Delay_10us, 10,
		0x36, 1, 0x00, 		//Memory Data Access Control
		0x3A, 1, 0x05, 		//RGB 5-6-5-bit
		0xB2, 5, 0x0C, 0x0C, 0x00, 0x33, 0x33,	//Porch Setting
		0xB7, 1, 0x35, 		//Gate Control
		0xBB, 1, 0x32, 		//VCOM Setting
		0xC0, 1, 0x2C, 		//LCM Control
		0xC2, 1, 0x01, 		//VDV and VRH Command Enable
		0xC3, 1, 0x10,		//VRH Set
		0xC4, 1, 0x20, 		//VDV Set
		0xC6, 1, 0x06, 		//Frame Rate Control in Normal Mode
		0xD0, 2, 0xA4, 0xA1, 	//Power Control 1
		0xE0, 14, 0xD0, 0x00, 0x02, 0x07, 0x0A, 0x28, 0x32, 0x44, 0x42, 0x06, 0x0E, 0x12, 0x14, 0x17, //Positive Voltage Gamma Control
		0xE1, 14, 0xD0, 0x00, 0x02, 0x07, 0x0A, 0x28, 0x31, 0x54, 0x47, 0x0E, 0x1C, 0x17, 0x1B, 0x1E, //Negative Voltage Gamma Control
		0x2A, 4, 0x00, 0x00, 0x00, 0xEF,	//Column Address Set
		0x2B, 4, 0x00, 0x00, 0x01, 0x3F,	//Row Address Set
		0x2C, 0,
		0x29, 0,		//display on
		TFTLCD_Delay_10us, 10,
};

#define RD_ACTIVE  						GPIO_PIN_LOW(GPIOA, 0)
#define RD_IDLE    						GPIO_PIN_HIGH(GPIOA, 0)

#define WR_ACTIVE  						GPIO_PIN_LOW(GPIOA, 1)
#define WR_IDLE    						GPIO_PIN_HIGH(GPIOA, 1)

#define CD_COMMAND 						GPIO_PIN_LOW(GPIOA, 2)
#define CD_DATA    						GPIO_PIN_HIGH(GPIOA, 2)


#define CS_ACTIVE  						GPIO_PIN_LOW(GPIOA, 3)
#define CS_IDLE    						GPIO_PIN_HIGH(GPIOA, 3)


#define RESET_ACTIVE  					GPIO_PIN_LOW(GPIOA, 4)
#define RESET_IDLE    					GPIO_PIN_HIGH(GPIOA, 4)


#define WR_STROBE 			{ WR_ACTIVE;WR_ACTIVE;WR_IDLE; }
#define RD_STROBE 			RD_IDLE, RD_ACTIVE, RD_ACTIVE, RD_ACTIVE


/*
*******************************************************************************
*                          PRIVATE VARIABLE DECLARATION
*/
static uint8_t lookup[16] = {
0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };

static uint16_t width, height = 0;
static 	uint8_t _MC, _MP, _SC, _SP, _EC, _EP, _MW;


/*
*******************************************************************************
*                          PRIVATE FUNCTION DECLARATION
*******************************************************************************
*/

static void WriteCmdParamN(uint16_t cmd, int8_t N, uint8_t * block);
static void WriteCmdParam4(uint8_t cmd, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4);
static void setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1);

static void write8(uint8_t data);
static void write16(uint16_t data);
static void WriteCmd(uint8_t data);


/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/

void TFT_Init(void)
{
	uint16_t size = sizeof(ST7789_regValues);
	uint8_t* ptr = (uint8_t*)ST7789_regValues;

	uint16_t cmd, value, loop_var = 0;
	uint8_t data[24] = {0};


	Gpio_SetPullValue(PINA(1), PULL_UP);	//	WR
	Gpio_SetPullValue(PINA(2), PULL_UP);	//	RS
	Gpio_SetPullValue(PINA(3), PULL_UP);	//	CS
	Gpio_SetPullValue(PINA(4), PULL_UP);	//	RST

	Gpio_SetModePin(PINA(0), DATA_DIR_OUT_PP);	//	WR
	Gpio_SetModePin(PINA(1), DATA_DIR_OUT_PP);	//	WR
	Gpio_SetModePin(PINA(2), DATA_DIR_OUT_PP);	//	RS
	Gpio_SetModePin(PINA(3), DATA_DIR_OUT_PP);	//	CS
	Gpio_SetModePin(PINA(4), DATA_DIR_OUT_PP);	//	RST

	Gpio_SetModePin(PINB(6), DATA_DIR_OUT_PP);	//D0
	Gpio_SetModePin(PINB(5), DATA_DIR_OUT_PP);	//D1
	Gpio_SetModePin(PINA(13), DATA_DIR_OUT_PP);	//D2
	Gpio_SetModePin(PINA(12), DATA_DIR_OUT_PP);	//D3
	Gpio_SetModePin(PINA(11), DATA_DIR_OUT_PP);	//D4
	Gpio_SetModePin(PINA(10), DATA_DIR_OUT_PP);	//D5
	Gpio_SetModePin(PINA(9), DATA_DIR_OUT_PP);	//D6
	Gpio_SetModePin(PINA(8), DATA_DIR_OUT_PP);	//D7

	GPIO_PIN_HIGH(GPIOA, PIN_0);	//	RD
	GPIO_PIN_HIGH(GPIOA, PIN_2);	//	RS
	GPIO_PIN_HIGH(GPIOA, PIN_3);	//	CS

	GPIO_PIN_HIGH(GPIOB, PIN_6);	//	RS
	GPIO_PIN_HIGH(GPIOB, PIN_5);

	_MW = 0x2C;
	_MC = 0x2A;
	_MP	= 0x2B;
	_SC	= 0x2A;
	_SP	= 0x2B;
	_EC = 0x2A;
	_EP = 0x2B;

    CS_IDLE;
    WR_IDLE;
    RESET_IDLE;

    Delay_10us(10000);

    RESET_ACTIVE;
    Delay_10us(10000);
    RESET_IDLE;
    Delay_10us(10000);

	while(size > 0)
	{
		cmd = *ptr++;
		value = *ptr++;
		if(cmd == TFTLCD_Delay_10us)
		{
			Delay_10us(value);
			value = 0;
		}
		else {

		for(loop_var = 0; loop_var < value; loop_var++)
		{
			data[loop_var] = *ptr++;
		}

		WriteCmdParamN(cmd, value, data);
		}
		size -= value + 2;
	}
}

/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/

void Write_Strobe(void)
{
	Gpio_WriteOutPin(GPIOA, PIN_1, DATA_OUT_LOW);
	Delay_10us(5);
	Gpio_WriteOutPin(GPIOA, PIN_1, DATA_OUT_HIGH);
}

/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/

static void WriteCmdParamN(uint16_t cmd, int8_t N, uint8_t * block)
{
    CS_ACTIVE;
    WriteCmd(cmd);
    while (N-- > 0) {
        uint8_t u8 = *block++;
        write8(u8);
    }
    CS_IDLE;
}

/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/
void WriteCmdParam4(uint8_t cmd, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4)
{
    uint8_t d[4];
    d[0] = d1, d[1] = d2, d[2] = d3, d[3] = d4;
    WriteCmdParamN(cmd, 4, d);
}

/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/
void setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1)
{
    WriteCmdParam4(_SC, x >> 8, x, x1 >> 8, x1);   //Start column instead of _MC
    WriteCmdParam4(_SP, y >> 8, y, y1 >> 8, y1);
}


/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	int16_t end;
	setAddrWindow(x, y, x + w - 1, y + h - 1);
	CS_ACTIVE;
	WriteCmd(_MW);

    while (h-- > 0)
    {
        end = w;
        do {
        	write16(color);
        } while (--end != 0);
    }
    CS_IDLE;

}

/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/

void Draw_Icon(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t* data, uint16_t front_colour, uint16_t back_colour)
{
	uint32_t count = 0;
	uint16_t bit_count = 8;
	setAddrWindow(x, y, x + w - 1, y + h - 1);
	CS_ACTIVE;
	WriteCmd(_MW);
	count = w * h;

	while(count-- > 0)
	{
		if(bit_count == 0)
		{
			data++;
			bit_count = 8;
		}

		if(((*data >> (bit_count - 1)) & 0x01) != 0)
		{
			write16(front_colour);
		}
		else
		{
			write16(back_colour);
		}
		bit_count--;
	}


    CS_IDLE;
}


/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/

void Draw_Line(int16_t x, int16_t y, direction_t direction,uint16_t colour, uint8_t thickness, uint16_t length)
{
	uint16_t x1, y1, data_count = 0;

	if(direction == HORIZONTAL)
	{
		x1 = x + length - 1;
		y1 = y + thickness;
		data_count = length * thickness;
	}
	else
	{
		x1 = x + thickness - 1;
		y1 = y + length;
		data_count = length * thickness;
	}

	setAddrWindow(x, y, x1, y1);
	CS_ACTIVE;
	WriteCmd(_MW);

    while (data_count > 0)
    {
		write16(colour);
		data_count--;
    }

    CS_IDLE;

    setAddrWindow(0, 0, width - 1, height - 1);

}


/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/

void Draw_Rectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2,  uint16_t colour, uint8_t thickness)
{
	Draw_Line(x1 , y1 , HORIZONTAL , colour , thickness , x2 - x1);
	Draw_Line(x1 , y1 , VERTICAL , colour , thickness ,y2 - y1);

	Draw_Line(x2 , y1 , VERTICAL , colour , thickness , y2 - y1);
	Draw_Line(x1 , y2 , HORIZONTAL , colour , thickness , x2 - x1 + thickness);

}//End of Draw_Rectangle

/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/

void Draw_Margin(uint8_t margin, uint16_t colour, uint8_t thickness)
{
	Draw_Line(margin, margin, HORIZONTAL, colour, thickness, Get_Width() - margin*2);
	Draw_Line(margin, Get_Height() - margin, HORIZONTAL, colour, thickness, Get_Width() - margin*2);
	Draw_Line(margin, margin, VERTICAL, colour, thickness, Get_Height() - margin*2);
	Draw_Line(Get_Width() - margin, margin, VERTICAL, colour, thickness, Get_Height() - margin*2);
}

/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/

void Draw_Table(int16_t x, int16_t y, uint16_t no_co, uint16_t no_ro, uint16_t w, uint16_t h)
{
	uint16_t loop_var;
	for(loop_var = 0; loop_var < no_ro; loop_var++)
		Draw_Line(x, y + (((h - y)/no_ro) * loop_var) , HORIZONTAL, COLOUR_WHITE, 1, w);

	Draw_Line(x, h - 1, HORIZONTAL, COLOUR_WHITE, 1, w);

	for(loop_var = 0; loop_var < no_co; loop_var++)
		Draw_Line(x + (((w - x)/no_co)*loop_var), y, VERTICAL, COLOUR_WHITE, 1, h);

	Draw_Line(w - x - 1, y, VERTICAL, COLOUR_WHITE, 1, h);
}

/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/
void setRotation(uint8_t r, bool_t BGR_flag)
{
	uint8_t temp_value = (r << 4) & 0xF0;

	if(BGR_flag == TRUE)
	{
		temp_value |= 0x08;
	}

	WriteCmdParamN(0x16, 1, &temp_value);

	switch(r)
	{
	case 0x00:	//vertical mirror  BGR
	case 0x01:	//vertical mirror  BGR
	case 0x02:	//vertical mirror  BGR
	case 0x03:	//vertical mirror  BGR
	case 0x04:	//opp. vertical mirror RGB
	case 0x05:	//opp. vertical mirror RGB
	case 0x06:	//opp. vertical mirror RGB
	case 0x07:	//opp. vertical mirror RGB
	case 0x08:	//opp. vertical mirror RGB
	case 0x09:	//opp. vertical mirror RGB
	case 0x0A:	//opp. vertical mirror RGB
	case 0x0B:	//opp. vertical mirror BGR
	case 0x0C:	//vertical RGB///////////////		BGR with BGR flag TRUE
	case 0x0D:	//vertical mirror BGR		opp. horizontal RGB////////////////////vertical RGB
		if((BGR_flag == TRUE) && (r == 0x0D))
		{

			width = 240;
			height = 320;
		}
		break;

	case 0x0E:	//horizontal mirror RGB				opp. vertical BGR(with BGR flag TRUE

		width = 240;
		height = 320;
		break;
	case 0x0F:	//horizontal RGB///////////////////		opp.vertical BGR(with BGR flag TRUE
		if(BGR_flag == TRUE)
		{
			width = 240;
			height = 320;
		}
		else
		{
			width = 320;
			height = 240;
		}
		break;

	default:
		width = 240;
		height = 240;
		break;
	}
}

/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/

void Set_ScreenDir(screen_direction_t screen_direction)
{
	uint8_t temp_value;
	switch(screen_direction)
	{
	case HORIZONTAL_SCREEN:
		width = 320;
		height = 240;
		temp_value = 0x60;
		break;

	case HORIZONTAL_1_SCREEN:
		width = 320;
		height = 240;
		temp_value = 0xA0;
		break;

	case VERTICAL_SCREEN:
		width = 240;
		height = 320;
		temp_value = 0x00;
		break;

	case VERTICAL_BGR_SCREEN:
		width = 240;
		height = 320;
		temp_value = 0xC8;
		break;

	case VERTICAL_1_SCREEN:
		width = 240;
		height = 320;
		temp_value = 0xC0;
		break;

	default:
		width = 240;
		height = 240;
		break;
	}
//	temp_value = 0xC8;
//	0x20:hori1-mirror 0x80:ver1-mirror 0x40:ver-mirror
	WriteCmdParamN(0x36, 1, &temp_value);

}


/**
 ******************************************************************************
 * @fn
 ******************************************************************************
 * @brief
 * @note   None
 * @param
 * @retval
 ******************************************************************************
 */

void TftWriteText(int16_t x, int16_t y, const gfont_t* font_info, char *data_ptr, uint8_t len, uint16_t txt_colour, uint16_t bk_colour )
{
	uint16_t index ,j , h, w = 0;
	uint16_t bit_count = 0;
	uint8_t * font_addr_ptr;
	char ascii_data = 0;

	uint8_t font_width = 0;
	uint16_t temp2 = 0;

	for(j = 0 ; j < len ; j++)
	{
		ascii_data = *data_ptr++;

		//Get the ascii offset w.r.t starting ascii character
		index = (ascii_data-font_info->start_char);

		//Get the width in pixels of current ascii character
		font_width = *(font_info->font_descr + (index<<1));

		//Get the bitmap starting address for above ascii character
		temp2 = *(font_info->font_descr + (index<<1) + 1);
		font_addr_ptr = (uint8_t *)&font_info->font_bitmap[temp2];

		setAddrWindow(x , y , x + font_width + font_info->padding - 1, y + font_info->height + 1);
		CS_ACTIVE;
		WriteCmd(_MW);

		h = 0;
		bit_count = 8;

		while(h < font_info->height)
		{
			w = 0;
			while(w < font_width)
			{
				if(bit_count == 0)
				{
					font_addr_ptr++;
					bit_count = 8;
				}

				if(((*font_addr_ptr >> (bit_count - 1)) & 0x01) != 0)
				{
					write16(txt_colour);
				}
				else
				{
					write16(bk_colour);
				}

				bit_count--;
				w++;
			}
			//padding pixels blank after each character
			for(index = 0 ; index < font_info->padding ; index++)
			{
				write16(bk_colour);
			}
			bit_count = 8;
			font_addr_ptr++;
			h++;
		}
		x += font_width + font_info->padding;
	}
	CS_IDLE;
}


/**
 ******************************************************************************
 * @fn
 ******************************************************************************
 * @brief
 * @note   None
 * @param
 * @retval
 ******************************************************************************
 */
void TftDispDigits(char *data_ptr , int y_offset)
{
	TftWriteText(0, y_offset , &digifaceWide_30pt_info, data_ptr , strlen(data_ptr) , COLOUR_CYAN, COLOUR_BLACK);
}//End of DispDigits


/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/
uint16_t Get_Width(void)
{
	return(width);
}

/**
******************************************************************************
* @fn
******************************************************************************
* @brief
* @note   None
* @param
* @retval
******************************************************************************
*/
uint16_t Get_Height(void)
{
	return(height);
}

void write8(uint8_t data)
{
	uint8_t byte = 0;

	Gpio_WriteOutPin(GPIOB, PIN_6, (data & 0x01));	//D0
	Gpio_WriteOutPin(GPIOB, PIN_5, (data & 0x02)>>1);	//D1

	data &= 0xFC;

	byte = (lookup[data&0x0F] << 4) | lookup[data>>4];

	GPIOA->OUT.B[1] &= 0xC0;
	GPIOA->OUT.B[1] |= byte;
	WR_STROBE;
}

void write16(uint16_t data)
{
	uint8_t h = (data)>>8, l = data;
	write8(h);
	write8(l);
}

void WriteCmd(uint8_t data)
{
	 CD_COMMAND;
	 write8(data)/*write16(x)*/;
	 CD_DATA;
}

/*-------------------------------END OF FILE----------------------------------*/
