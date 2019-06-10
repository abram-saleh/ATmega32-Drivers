/*
 * KPD_prog.c
 *
 *  Created on: Jun 10, 2019
 *      Author: Abram Saleh
 */

#include "../../LIB/types.h"
#include "../../LIB/util.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "avr/delay.h"
#include "KPD_int.h"
#include "KPD_cfg.h"

/* Error Codes */
typedef enum
{
	NO_ERROR,
	ERR_NULL_PTR
}ERROR;

/* Call the keypad array from the configuration file */
extern u8 au8KeypadMatrixGbl[KPD_MAX][KPD_MAX];

/* Define two global arrays to store pins of rows and columns */
u8 au8ColumnGbl[KPD_MAX] = {C1_PIN, C2_PIN, C3_PIN, C4_PIN};
u8 au8RowGbl[KPD_MAX]    = {R1_PIN, R2_PIN, R3_PIN, R4_PIN};

/**********************************************************************************/
/**************************** Public Functions ************************************/
/**********************************************************************************/

/**********************************************************************************/
// Description: Initialize the keypad
// Input	  : Nothing
// Output	  : Nothing
/**********************************************************************************/
extern void KPD_vidInit(void)
{
	/* Declare a local variable for the loop iterations */
	u8 u8IterationLoc;

	/* Set R1~R4 pins as input */
	for(u8IterationLoc = KPD_MIN; u8IterationLoc < KPD_MAX; u8IterationLoc++)
	{
		DIO_u8SetPinDir(KPD_PORT, au8RowGbl[u8IterationLoc], PIN_INPUT);
	}

	/* Activate pull-up resistors in R1~R4 pins */
	for(u8IterationLoc = KPD_MIN; u8IterationLoc < KPD_MAX; u8IterationLoc++)
	{
		DIO_u8SetPinVal(KPD_PORT, au8RowGbl[u8IterationLoc], PIN_HIGH);
	}

	/* Set C1~C4 pins as output */
	for(u8IterationLoc = KPD_MIN; u8IterationLoc < KPD_MAX; u8IterationLoc++)
	{
		DIO_u8SetPinDir(KPD_PORT, au8ColumnGbl[u8IterationLoc], PIN_OUTPUT);
	}
}

/**********************************************************************************/
// Description: Keep scanning all keys to detect pressed key
// Input	  : Pointer to return pressed key
// Output	  : Error Index
/**********************************************************************************/
extern u8 KPD_u8GetKey(u8* pu8KeyCpy)
{
	/* Make sure the input pointer does not point to NULL */
	if(pu8KeyCpy != NULL)
	{
		/* Define a local variable to store the current value of input pins */
		u8 u8CurrentLoc = NOT_PRESSED;

		/* Declare local variables for the loop iterations */
		u8 u8ColumnLoc, u8RowLoc;

		/* Deactivate all columns */
		for(u8ColumnLoc = KPD_MIN; u8ColumnLoc < KPD_MAX; u8ColumnLoc++)
		{
			DIO_u8SetPinVal(KPD_PORT, au8ColumnGbl[u8ColumnLoc], NOT_PRESSED);
		}

		/* Start the keypad scanning algorithm until a key is pressed */
		while(u8CurrentLoc == NOT_PRESSED)
		{
			for(u8ColumnLoc = KPD_MIN; u8ColumnLoc < KPD_MAX; u8ColumnLoc++)
			{
				/* Activate the current column */
				DIO_u8SetPinVal(KPD_PORT, au8ColumnGbl[u8ColumnLoc], PRESSED);

				for(u8RowLoc = KPD_MIN; u8RowLoc < KPD_MAX; u8RowLoc++)
				{
					/* Check to see if the the key in the current row and column is pressed */
					DIO_u8GetPinVal(KPD_PORT, au8RowGbl[u8RowLoc], &u8CurrentLoc);
					if(u8CurrentLoc == PRESSED)
					{
						*pu8KeyCpy = au8KeypadMatrixGbl[u8RowLoc][u8ColumnLoc];

						/* Delay to avoid bouncing */
						_delay_ms(200);

						return NO_ERROR;
					}
					else
					{
						/* Do nothing */
					}
				}

				/* Deactivate the current column */
				DIO_u8SetPinVal(KPD_PORT, au8ColumnGbl[u8ColumnLoc], NOT_PRESSED);
			}
		}
	}
	else
	{
		/* The input pointer points to NULL */
		return ERR_NULL_PTR;
	}
}
