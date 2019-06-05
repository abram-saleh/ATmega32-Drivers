/*
 * LCD_priv.h
 *
 *  Created on: May 26, 2019
 *      Author: Abram Saleh
 */

#ifndef HAL_LCD_LCD_PRIV_H_
#define HAL_LCD_LCD_PRIV_H_

/**********************************************************************************/
/****************************** Private Definitions *******************************/
/**********************************************************************************/

/* Instructions */
#define FUNCTION_SET 0x20
#define DISP_CTRL	 0x08
#define ENTRY_MODE	 0x04

/* Move Direction */
#define MOVE_DIR_RIGHT 0x02
#define MOVE_DIR_LEFT  0x00

/* Display Shift Status */
#define SHIFT_OFF 0x00
#define SHIFT_ON  0x01

/* Line Addresses */
#define FIRST_LINE_ADDRESS  0x7F
#define SECOND_LINE_ADDRESS 0xBF

/* Data Length */
#define DATA_LEN 0x08

/* Data Limits */
#define U8_MIN  0x00
#define U8_MAX  0xFF
#define U16_MIN 0x0000
#define U16_MAX 0xFFFF

/**********************************************************************************/
/******************************* Private Functions ********************************/
/**********************************************************************************/

/**********************************************************************************/
// Description: Write data on the 4 data pins (D4-D7)
// Input	  : 8-bit data
// Output	  : Nothing
/**********************************************************************************/
extern void LCD_vidWriteData4Bit(u8 u8DataCpy);

/**********************************************************************************/
// Description: Write data on the 8 data pins (D0-D7)
// Input	  : 8-bit data
// Output	  : Nothing
/**********************************************************************************/
extern void LCD_vidWriteData8Bit(u8 u8DataCpy);

#endif /* HAL_LCD_LCD_PRIV_H_ */
