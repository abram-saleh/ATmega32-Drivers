/*
 * KPD_int.h
 *
 *  Created on: Jun 10, 2019
 *      Author: Abram Saleh
 */

#ifndef HAL_KPD_KPD_INT_H_
#define HAL_KPD_KPD_INT_H_

/**********************************************************************************/
/*************************** Public Definitions ***********************************/
/**********************************************************************************/

/* Keypad Limits */
#define KPD_MIN 0
#define KPD_MAX 4

/* Key States */
#define PRESSED		0
#define NOT_PRESSED 1

/* Null */
#define NULL '\0'

/**********************************************************************************/
/**************************** Public Functions ************************************/
/**********************************************************************************/

/**********************************************************************************/
// Description: Initialize the keypad
// Input	  : Nothing
// Output	  : Nothing
/**********************************************************************************/
extern void KPD_vidInit(void);

/**********************************************************************************/
// Description: Keep scanning all keys to detect pressed key
// Input	  : Pointer to return pressed key
// Output	  : Error Index
/**********************************************************************************/
extern u8 KPD_u8GetKey(u8* pu8KeyCpy);

#endif /* HAL_KPD_KPD_INT_H_ */
