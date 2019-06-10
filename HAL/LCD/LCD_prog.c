/*
 * LCD_prog.c
 *
 *  Created on: May 26, 2019
 *      Author: Abram Saleh
 */

#include "../../LIB/types.h"
#include "../../LIB/util.h"
#include "../../MCAL/DIO/DIO_priv.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "avr/delay.h"
#include "LCD_priv.h"
#include "LCD_int.h"
#include "LCD_cfg.h"

/* Global Variables */
u8 u8DataLengthGbl = LCD_DL;	// LCD Interface Data Length

/* Error Codes */
typedef enum
{
	NO_ERROR,
	ERR_CMD_ID,
	ERR_DATA,
	ERR_LINE_ADDRESS,
	ERR_POS_INDEX,
	ERR_STR_LEN,
	ERR_CFG
}ERROR;

/**********************************************************************************/
/**************************** Public Functions ************************************/
/**********************************************************************************/

/**********************************************************************************/
// Description: Apply initialization sequence to the LCD module
// Input	  : Nothing
// Output	  : Error Index
/**********************************************************************************/
extern void LCD_vidInit(void)
{
	/* Set 4 or 8 data pins as output depending on the selected data length */
	if(u8DataLengthGbl == DL_4BIT)						// 4-bit Mode
	{
		/* Set data pins as output */
		DIO_u8SetPinDir(DATA_PORT, D4_PIN, PIN_OUTPUT);
		DIO_u8SetPinDir(DATA_PORT, D5_PIN, PIN_OUTPUT);
		DIO_u8SetPinDir(DATA_PORT, D6_PIN, PIN_OUTPUT);
		DIO_u8SetPinDir(DATA_PORT, D7_PIN, PIN_OUTPUT);
	}
	else												// 8-bit Mode
	{
		/* Set data port as output */
		DIO_u8SetPortDir(DATA_PORT, PORT_OUTPUT);
	}

	/* Set RS pin as output */
	DIO_u8SetPinDir(CONTROL_PORT, RS_PIN, PIN_OUTPUT);
	/* Set R/W pin as output */
	DIO_u8SetPinDir(CONTROL_PORT, RW_PIN, PIN_OUTPUT);
	/* Set EN pin as output */
	DIO_u8SetPinDir(CONTROL_PORT, EN_PIN, PIN_OUTPUT);

	/* Wait for more than 30 ms after VDD rises to 4.5 V for the LCD module to initialize */
	_delay_ms(30);

	/* Function set */
	LCD_u8SendCmd(FUNCTION_SET + LCD_DL + LCD_LINE + CHAR_SIZE);
	_delay_us(40);

	/* Display On/Off Control */
	LCD_u8SendCmd(DISP_CTRL + DISP_STATE + CURSOR_STATE + BLINK_STATE);
	_delay_us(40);

	/* Clear Display */
	LCD_u8SendCmd(CLR_DISP);
	_delay_ms(2);

	/* Entry Mode Set */
	LCD_u8SendCmd(ENTRY_MODE + MOVE_DIR + SHIFT_STATE);
	_delay_us(40);
}

/**********************************************************************************/
// Description: Send command to the LCD
// Input	  : Command ID
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8SendCmd(u8 u8CmdCpy)
{
	/* Make sure the command ID is within valid range */
	if((u8CmdCpy >= U8_MIN) && (u8CmdCpy <= U8_MAX))
	{
		/* Clear RS pin */
		DIO_u8SetPinVal(CONTROL_PORT, RS_PIN, PIN_LOW);
		/* Clear R/W pin */
		DIO_u8SetPinVal(CONTROL_PORT, RW_PIN, PIN_LOW);
		/* Set EN pin */
		DIO_u8SetPinVal(CONTROL_PORT, EN_PIN, PIN_HIGH);

		/* Load command on data port */
		if(u8DataLengthGbl == DL_4BIT)						// 4-bit Mode
		{
			LCD_vidWriteData4Bit(u8CmdCpy);
		}
		else												// 8-bit Mode
		{
			LCD_vidWriteData8Bit(u8CmdCpy);
		}

		/* Clear EN pin */
		DIO_u8SetPinVal(CONTROL_PORT, EN_PIN, PIN_LOW);
		/* Wait for EN to settle */
		_delay_ms(5);
		/* Set EN pin */
		DIO_u8SetPinVal(CONTROL_PORT, EN_PIN, PIN_HIGH);
		/* Wait for EN to settle */
		_delay_ms(10);

		/* Return No Error */
		return NO_ERROR;
	}
	else
	{
		return ERR_CMD_ID;	// Invalid Command ID
	}
}

/**********************************************************************************/
// Description: Set Address Counter (AC) to a specific position in the DDRAM
// Input	  : Line index (1 or 2) and position index (1 to 40)
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8GoTo(u8 u8LineIndexCpy, u8 u8PosIndexCpy)
{
	/* Make sure position index is within valid range */
	if((u8PosIndexCpy >= POS1) && (u8PosIndexCpy <= POS16))
	{
		switch(u8LineIndexCpy)
		{
		case FIRST_LINE:  LCD_u8SendCmd(FIRST_LINE_ADDRESS + u8PosIndexCpy);  break;
		case SECOND_LINE: LCD_u8SendCmd(SECOND_LINE_ADDRESS + u8PosIndexCpy); break;
		default: return ERR_LINE_ADDRESS; break;	// Invalid Line Address
		}

		/* Return No Error */
		return NO_ERROR;
	}
	else
	{
		/* Invalid Position Index */
		return ERR_POS_INDEX;
	}
}

/**********************************************************************************/
// Description: Write a character on the LCD
// Input	  : Character ASCII code
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8WriteChar(u8 u8CharCpy)
{
	/* Make sure the data is within valid range */
	if((u8CharCpy >= U8_MIN) && (u8CharCpy <= U8_MAX))
	{
		/* Set RS pin */
		DIO_u8SetPinVal(CONTROL_PORT, RS_PIN, PIN_HIGH);
		/* Clear R/W pin */
		DIO_u8SetPinVal(CONTROL_PORT, RW_PIN, PIN_LOW);
		/* Set EN pin */
		DIO_u8SetPinVal(CONTROL_PORT, EN_PIN, PIN_HIGH);

		/* Load command on data port */
		if(u8DataLengthGbl == DL_4BIT)						// 4-bit Mode
		{
			LCD_vidWriteData4Bit(u8CharCpy);
		}
		else												// 8-bit Mode
		{
			LCD_vidWriteData8Bit(u8CharCpy);
		}

		/* Clear EN pin */
		DIO_u8SetPinVal(CONTROL_PORT, EN_PIN, PIN_LOW);
		/* Wait for EN to settle */
		_delay_ms(5);
		/* Set EN pin */
		DIO_u8SetPinVal(CONTROL_PORT, EN_PIN, PIN_HIGH);
		/* Wait for EN to settle */
		_delay_ms(10);

		/* Return No Error */
		return NO_ERROR;
	}
	else
	{
		return ERR_DATA;	// Invalid Data
	}
}

/**********************************************************************************/
// Description: Write a string on the LCD
// Input	  : Pointer to a string and string length
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8WriteString(u8* pu8StrCpy, u8 u8StrLenCpy)
{
	/* Make sure string length is not longer than the valid range within each line (40 positions) */
	if((u8StrLenCpy >= POS_MIN) && (u8StrLenCpy <= POS_MAX))
	{
		/* Local Variables */
		u8 u8IterationLoc;

		for(u8IterationLoc = 0; u8IterationLoc < u8StrLenCpy; u8IterationLoc++)
		{
			LCD_u8WriteChar(pu8StrCpy[u8IterationLoc]);
		}

		/* Return No Error */
		return NO_ERROR;
	}
	else
	{
		return ERR_STR_LEN;		// Invalid String Length
	}
}

/**********************************************************************************/
// Description: Write an unsigned short integer (u16) on the LCD
// Input	  : Unsigned short integer (u16)
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8WriteU16(u16 u16ValCpy)
{
	/* Make sure the data is within valid range */
	if((u16ValCpy >= U16_MIN) && (u16ValCpy <= U16_MAX))
	{
		if(u16ValCpy == 0)
		{
			LCD_u8WriteChar('0');
		}
		else
		{
			/* Local Variables */
			u8 u8DigitCountLoc = 0;
			s8 s8IterationLoc;

			/* Create an array to store u16 digits */
			u8 au8DigitsLoc[5] = {};

			/* Split the value into single digits */
			while(u16ValCpy != 0)
			{
				au8DigitsLoc[u8DigitCountLoc] = (u16ValCpy % 10) + '0';
				u8DigitCountLoc++;
				u16ValCpy = u16ValCpy / 10;
			}

			/* Write the u16 number digit by digit */
			for(s8IterationLoc = u8DigitCountLoc - 1; s8IterationLoc >= 0; s8IterationLoc--)
			{
				LCD_u8WriteChar(au8DigitsLoc[s8IterationLoc]);
			}
		}

		/* Return No Error */
		return NO_ERROR;
	}
	else
	{
		return ERR_DATA;	// Invalid Data
	}
}

/**********************************************************************************/
// Description: Sets interface data length, number of lines and character font
// Input	  : Data length, number of lines and character font
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8FunctionSet(u8 u8DataLengthCpy, u8 u8NumberOfLinesCpy, u8 u8CharacterFontCpy)
{
	/* Make sure the configurations are valid */
	if( ( (u8DataLengthCpy == DL_4BIT)     ||   (u8DataLengthCpy   == DL_8BIT)   ) &&
	    ( (u8NumberOfLinesCpy == ONE_LINE) || (u8NumberOfLinesCpy  == TWO_LINES) ) &&
	    ( (u8CharacterFontCpy == SIZE_5x7) ||  (u8CharacterFontCpy == SIZE_5x10)  )   )
	{
		/* Function set */
		LCD_u8SendCmd(FUNCTION_SET + u8DataLengthCpy + u8NumberOfLinesCpy + u8CharacterFontCpy);

		/* Return No Error */
		return NO_ERROR;
	}
	else
	{
		/* Invalid Configurations */
		return ERR_CFG;
	}
}

/**********************************************************************************/
// Description: Controls display, cursor and character blink states
// Input	  : Display state, cursor state and character blink state
// Output	  : Error Index
/**********************************************************************************/
extern u8 LCD_u8DispCtrl(u8 u8DispStateCpy, u8 u8CursorStateCpy, u8 u8BlinkStateCpy)
{
	/* Make sure the configurations are valid */
	if( ( (u8DispStateCpy == DISP_OFF)     ||   (u8DispStateCpy   == DISP_ON)   ) &&
	    ( (u8CursorStateCpy == CURSOR_OFF) ||  (u8CursorStateCpy  == CURSOR_ON) ) &&
	    ( (u8BlinkStateCpy == BLINK_OFF)   ||   (u8BlinkStateCpy == BLINK_ON)   )    )
	{
		/* Display On/Off Control */
		LCD_u8SendCmd(DISP_CTRL + u8DispStateCpy + u8CursorStateCpy + u8BlinkStateCpy);

		/* Return No Error */
		return NO_ERROR;
	}
	else
	{
		/* Invalid Configurations */
		return ERR_CFG;
	}
}

/**********************************************************************************/
/******************************* Private Functions ********************************/
/**********************************************************************************/

/**********************************************************************************/
// Description: Write data on the 4 data pins (D4-D7)
// Input	  : 8-bit data
// Output	  : Nothing
/**********************************************************************************/
extern void LCD_vidWriteData4Bit(u8 u8DataCpy)
{
	/* Declare a local variable for the loop iterations */
	u8 u8IterationLoc;

	/* Declare an array to store the 8 bits of data */
	u8 au8DataLoc[DATA_LEN];

	/* Store the 8 bits of data into the array */
	for(u8IterationLoc = 0; u8IterationLoc < DATA_LEN; u8IterationLoc++)
	{
		au8DataLoc[u8IterationLoc] = GET_BIT(u8DataCpy, u8IterationLoc);
	}

	/* Write higher nibble of data on the 4 data pins */
	DIO_u8SetPinVal(DATA_PORT, D4_PIN, au8DataLoc[4]);
	DIO_u8SetPinVal(DATA_PORT, D5_PIN, au8DataLoc[5]);
	DIO_u8SetPinVal(DATA_PORT, D6_PIN, au8DataLoc[6]);
	DIO_u8SetPinVal(DATA_PORT, D7_PIN, au8DataLoc[7]);

	/* Clear EN pin */
	DIO_u8SetPinVal(CONTROL_PORT, EN_PIN, PIN_LOW);
	/* Wait for EN to settle */
	_delay_ms(5);
	/* Set EN pin */
	DIO_u8SetPinVal(CONTROL_PORT, EN_PIN, PIN_HIGH);
	/* Wait for EN to settle */
	_delay_ms(10);

	/* Set EN pin */
	DIO_u8SetPinVal(CONTROL_PORT, EN_PIN, PIN_HIGH);
	/* Write lower nibble of data on the 4 data pins */
	DIO_u8SetPinVal(DATA_PORT, D4_PIN, au8DataLoc[0]);
	DIO_u8SetPinVal(DATA_PORT, D5_PIN, au8DataLoc[1]);
	DIO_u8SetPinVal(DATA_PORT, D6_PIN, au8DataLoc[2]);
	DIO_u8SetPinVal(DATA_PORT, D7_PIN, au8DataLoc[3]);
}

/**********************************************************************************/
// Description: Write data on the 8 data pins (D0-D7)
// Input	  : 8-bit data
// Output	  : Nothing
/**********************************************************************************/
extern void LCD_vidWriteData8Bit(u8 u8DataCpy)
{
	/* Declare a local variable for the loop iterations */
	u8 u8IterationLoc;

	/* Declare an array to store the 8 bits of data */
	u8 au8DataLoc[DATA_LEN];

	/* Store the 8 bits of data into the array */
	for(u8IterationLoc = 0; u8IterationLoc < DATA_LEN; u8IterationLoc++)
	{
		au8DataLoc[u8IterationLoc] = GET_BIT(u8DataCpy, u8IterationLoc);
	}

	/* Write data on data pins */
	DIO_u8SetPinVal(DATA_PORT, D0_PIN, au8DataLoc[0]);
	DIO_u8SetPinVal(DATA_PORT, D1_PIN, au8DataLoc[1]);
	DIO_u8SetPinVal(DATA_PORT, D2_PIN, au8DataLoc[2]);
	DIO_u8SetPinVal(DATA_PORT, D3_PIN, au8DataLoc[3]);
	DIO_u8SetPinVal(DATA_PORT, D4_PIN, au8DataLoc[4]);
	DIO_u8SetPinVal(DATA_PORT, D5_PIN, au8DataLoc[5]);
	DIO_u8SetPinVal(DATA_PORT, D6_PIN, au8DataLoc[6]);
	DIO_u8SetPinVal(DATA_PORT, D7_PIN, au8DataLoc[7]);
}
