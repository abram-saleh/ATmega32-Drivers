/*
 * KPD_cfg.h
 *
 *  Created on: Jun 10, 2019
 *      Author: Abram Saleh
 */

#ifndef HAL_KPD_KPD_CFG_H_
#define HAL_KPD_KPD_CFG_H_

/**********************************************************************************/
/*********************** Software Configuration Definitions ***********************/
/**********************************************************************************/

/************** Keypad Matrix ***************/
/*        C1       C2      C3      C4       */
/*	                                        */
/* R1     1        2       3       A        */
/*	                                        */
/* R2  	  4        5       6       B        */
/*	                                        */
/* R3	  7        8       9       C        */
/*	                                        */
/* R4	  *        0       #       D        */
/********************************************/

/* Declare two-dimensional array to store key values */
u8 au8KeypadMatrixGbl[KPD_MAX][KPD_MAX] =
{
		{ '1' , '2' , '3' , 'A' },
		{ '4' , '5' , '6' , 'B' },
		{ '7' , '8' , '9' , 'C' },
		{ '*' , '0' , '#' , 'D' }
};

/**********************************************************************************/
/***************************** Hardware Connections *******************************/
/**********************************************************************************/

/* Keypad Port */
// Range: PORTA, PORTB, PORTC, PORTD
#define KPD_PORT PORTB

/* 4x4 Keypad Pins */
// Range: PIN0 -> PIN7
#define C1_PIN PIN0
#define C2_PIN PIN1
#define C3_PIN PIN2
#define C4_PIN PIN3
#define R1_PIN PIN4
#define R2_PIN PIN5
#define R3_PIN PIN6
#define R4_PIN PIN7

#endif /* HAL_KPD_KPD_CFG_H_ */
