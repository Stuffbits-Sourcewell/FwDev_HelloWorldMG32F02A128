/**
 ******************************************************************************
 * @file    main.c
 * @author  Nasreen Shaikh
 * @version 01.00
 * @date    11-JULY-2015
 * @brief
 ******************************************************************************
 * @attention
 * @{
 * <h2><center>&copy; Copyright 2015 StuffBits Technologies LLP. </center></h2>
 *			                All rights reserved.
 * An unpublished work by StuffBits Technologies LLP. This material contains
 * CONFIDENTIAL INFORMATION that is the property of StuffBits Technologies LLP.
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
 * Date      : 11-JULY-2015
 * Brief     : created file
 *
 *******************************************************************************
 */

/*
 *******************************************************************************
 *                                INCLUDE FILES
 *******************************************************************************
 */

#include "main.h"


/*
 *******************************************************************************
 *                          PRIVATE MACROS & CONSTANTS
 *******************************************************************************
 */




/*
 *******************************************************************************
 *                         PRIVATE VARIABLE DECLARATION
 *******************************************************************************
 */


/*
 *******************************************************************************
 *                         PRIVATE FUNCTION DECLARATION
 *******************************************************************************
 */

static void Ui_Prcs(void);

/**
 *******************************************************************************
 * @fn int16_t main(void)
 *******************************************************************************
 * @brief     Main Functio for Project.
 * @param     None
 * @retval    0
 ********************************************************************************
 */

int main(void)
{
	typedef enum
	{
		UI_PRCS_STATE,
		KEYPAD_PRCS_STATE,
	}main_state_t;

	main_state_t main_state = UI_PRCS_STATE;

	Sys_Init();

	TftWriteText(10 , 10 , &swis721CnBT_18pt_info , "Hello World", strlen ("Hello World"),COLOUR_CYAN, COLOUR_BLACK);
	while (TRUE)
	{

		switch(main_state)
		{

		case UI_PRCS_STATE:
			Ui_Prcs();
			main_state = KEYPAD_PRCS_STATE;
			break;

		case KEYPAD_PRCS_STATE:
			Touch_Read();
			main_state = UI_PRCS_STATE;
			break;

		default:
			main_state = UI_PRCS_STATE;
			break;
		}

	}

	return (0);
}//End  of main


/**
 ******************************************************************************
 * @fn
 ******************************************************************************
 * @brief :
 * @NOTE  :
 * @param : void
 * @retval: void
 ******************************************************************************
 */

void Ui_Prcs(void)
{
	char str[7];
	point_db_t *point_db_ptr =GetTouchValue();

	sprintf(str, "%d", point_db_ptr->x);
	TftDispDigits(str ,40);

	sprintf(str, "%d", point_db_ptr->y);
	TftDispDigits(str, 120);

	sprintf(str, "%d", point_db_ptr->z);
	TftDispDigits(str, 180);


}//End of Ui_UpdateMainPage
/*-------------------------------END OF FILE----------------------------------*/
