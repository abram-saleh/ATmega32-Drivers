/*
 * LCD_cfg.h
 *
 *  Created on: May 26, 2019
 *      Author: Abram Saleh
 */

// Driver information : 16 x 2 Character LCD (LMB161A)

#ifndef HAL_LCD_LCD_CFG_H_
#define HAL_LCD_LCD_CFG_H_

/**********************************************************************************/
/*********************** Software Configuration Definitions ***********************/
/**********************************************************************************/

/* LCD Interface Data Length */
/* Range:
 * DL_4BIT		->	Data is sent or received in 4-bit length (D4-D7)
 * DL_8BIT		->	Data is sent or received in 8-bit length (D0-D7)
 */
#define LCD_DL DL_8BIT

/* Number of Lines */
/* Range:
 * ONE_LINE		->	One line display (1/8 duty)
 * TWO_LINES	->	Two line display (1/16 duty)
 */
#define LCD_LINE ONE_LINE

/* Character Size */
/* Range:
 * SIZE_5x7		->	Character is 5 x 7 dots
 * SIZE_5x10	->	Character is 5 x 10 dots
 */
#define CHAR_SIZE SIZE_5x7

/* Display ON/OFF Status */
/* Range:
 * DISP_OFF		->	The entire display is off (the display data remain in the DDRAM)
 * DISP_ON		->	The entire display is on
 */
#define DISP_STATE DISP_ON

/* Cursor Status */
/* Range:
 * CURSOR_OFF	->	Turns the cursor off
 * CURSOR_ON	->	Turns the cursor on (the cursor is displayed on the 8th line when 5 x 7 character size has been selected)
 */
#define CURSOR_STATE CURSOR_ON

/* Character Blink Status */
/* Range:
 * BLINK_OFF	->	Character blink is off
 * BLINK_ON		->	The character indicated by the cursor blinks
 */
#define BLINK_STATE BLINK_OFF

/* Move Direction */
/* Range:
 * MOVE_DIR_RIGHT	->	Cursor or blink move to the right
 * MOVE_DIR_LEFT		->	Cursor or blink move to the left
 */
#define MOVE_DIR MOVE_DIR_RIGHT

/* Display Shift Status */
/* Range:
 * SHIFT_OFF	->	Display shift is turned off
 * SHIFT_ON		->	Shifts the entire display when writing to the DDRAM. The shift direction is determined by the move direction configuration above.
 */
#define SHIFT_STATE SHIFT_OFF

/**********************************************************************************/
/***************************** Hardware Connections *******************************/
/**********************************************************************************/

/* Data Port */
// Range: PORTA, PORTB, PORTC, PORTD
#define DATA_PORT PORTD

/* Control Port */
// Range: PORTA, PORTB, PORTC, PORTD
#define CONTROL_PORT PORTC

/* RS Pin */
// Range: PIN0 -> PIN7
#define RS_PIN PIN0

/* R/W Pin */
// Range: PIN0 -> PIN7
#define RW_PIN PIN1

/* Enable Pin */
// Range: PIN0 -> PIN7
#define EN_PIN PIN2

/* Data Pins for 4-bit Mode */
// Range: PIN0 -> PIN7
#define D0_PIN PIN0
#define D1_PIN PIN1
#define D2_PIN PIN2
#define D3_PIN PIN3
#define D4_PIN PIN4
#define D5_PIN PIN5
#define D6_PIN PIN6
#define D7_PIN PIN7

#endif /* HAL_LCD_LCD_CFG_H_ */
