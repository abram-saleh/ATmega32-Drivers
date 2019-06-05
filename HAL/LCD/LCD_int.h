/*
 * LCD_int.h
 *
 *  Created on: May 26, 2019
 *      Author: Abram Saleh
 */

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_

/**********************************************************************************/
/*************************** Public Definitions ***********************************/
/**********************************************************************************/

/* Commands */
#define CLR_DISP	 0x01
#define RETURN_HOME	 0x02
// Move Direction
#define DIR_RIGHT	 0x06
#define DIR_LEFT	 0x04
#define SHIFT_RIGHT	 0x07
#define SHIFT_LEFT	 0x05
// One-time Shifts
#define CURSOR_RIGHT 0x14
#define CURSOR_LEFT	 0x10
#define DISP_RIGHT	 0x1C
#define DISP_LEFT	 0x18

/* LCD Interface Data Length */
#define DL_4BIT 0x00
#define DL_8BIT 0x10

/* Number of Lines */
#define ONE_LINE  0x00
#define TWO_LINES 0x08

/* Character Size */
#define SIZE_5x7  0x00
#define SIZE_5x10 0x04

/* Display ON/OFF Status */
#define DISP_OFF 0x00
#define DISP_ON  0x04

/* Cursor Status */
#define CURSOR_OFF 0x00
#define CURSOR_ON  0x02

/* Character Blink Status */
#define BLINK_OFF 0x00
#define BLINK_ON  0x01

/* Lines */
#define FIRST_LINE	0
#define SECOND_LINE	1

/* Positions */
#define POS1  1
#define POS2  2
#define POS3  3
#define POS4  4
#define POS5  5
#define POS6  6
#define POS7  7
#define POS8  8
#define POS9  9
#define POS10 10
#define POS11 11
#define POS12 12
#define POS13 13
#define POS14 14
#define POS15 15
#define POS16 16

/* Position Index Limits */
#define POS_MIN 1
#define POS_MAX 40


/**********************************************************************************/
/**************************** Public Functions ************************************/
/**********************************************************************************/

/**********************************************************************************/
// Description: Apply initialization sequence to LCD module
// Input	  : Nothing
// Output	  : Error Index
/**********************************************************************************/
extern void LCD_vidInit(void);

/**********************************************************************************/
// Description: Send command to the LCD
// Input	  : Command ID
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8SendCmd(u8 u8CmdCpy);

/**********************************************************************************/
// Description: Set Address Counter (AC) to a specific position in the DDRAM
// Input	  : Line index (1 or 2) and position index (1 to 40)
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8GoTo(u8 u8LineIndexCpy, u8 u8PosIndexCpy);

/**********************************************************************************/
// Description: Write a character on the LCD
// Input	  : Character ASCII code
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8WriteChar(u8 u8CharCpy);

/**********************************************************************************/
// Description: Write a string on the LCD
// Input	  : Pointer to a string and string length
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8WriteString(u8* pu8StrCpy, u8 u8StrLenCpy);

/**********************************************************************************/
// Description: Write an unsigned short integer (u16) on the LCD
// Input	  : Unsigned short integer (u16)
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8WriteU16(u16 u16ValCpy);

/**********************************************************************************/
// Description: Sets interface data length, number of lines and character font
// Input	  : Data length, number of lines and character font
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8FunctionSet(u8 u8DataLengthCpy, u8 u8NumberOfLinesCpy, u8 u8CharacterFontCpy);

/**********************************************************************************/
// Description: Controls display, cursor and character blink states
// Input	  : Display state, cursor state and character blink state
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8DispCtrl(u8 u8DispStateCpy, u8 u8CursorStateCpy, u8 u8BlinkStateCpy);

#endif /* HAL_LCD_LCD_INT_H_ */
