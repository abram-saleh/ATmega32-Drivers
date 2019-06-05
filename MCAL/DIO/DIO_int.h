/*
 * DIO_int.h
 *
 *  Created on: Apr 15, 2019
 *      Author: Abram Saleh
 */

#ifndef MCAL_DIO_DIO_INT_H_
#define MCAL_DIO_DIO_INT_H_

/**********************************************************************************/
/*************************** Public Definitions ***********************************/
/**********************************************************************************/

/* Ports */
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

/* Pins */
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

/* Port Direction */
#define PORT_INPUT  0x00
#define PORT_OUTPUT 0xFF

/* Pin Direction */
#define PIN_INPUT  0
#define PIN_OUTPUT 1

/* Port Value */
#define PORT_LOW  0x00
#define PORT_HIGH 0xFF

/* Pin Value */
#define PIN_LOW  0
#define PIN_HIGH 1

/* Port and Pin Limits */
#define PORT_MIN 0
#define PORT_MAX 3
#define PIN_MIN  0
#define PIN_MAX  7

/**********************************************************************************/
/**************************** Public Functions ************************************/
/**********************************************************************************/

/**********************************************************************************/
// Description: Set port direction
// Input	  : Port index and port direction
// Output	  : Error index
/**********************************************************************************/
extern u8 DIO_u8SetPortDir(u8 u8PortIndexCpy, u8 u8PortDirCpy);

/**********************************************************************************/
// Description: Set port value
// Input	  : Port index and port value
// Output	  : Error index
/**********************************************************************************/
extern u8 DIO_u8SetPortVal(u8 u8PortIndexCpy, u8 u8PortValCpy);

/**********************************************************************************/
// Description: Set pin direction
// Input	  : Port index, pin index and pin direction
// Output	  : Error index
/**********************************************************************************/
extern u8 DIO_u8SetPinDir(u8 u8PortIndexCpy, u8 u8PinIndexCpy, u8 u8PinDirCpy);

/**********************************************************************************/
// Description: Set pin value
// Input	  : Port index, pin index and pin value
// Output	  : Error index
/**********************************************************************************/
extern u8 DIO_u8SetPinVal(u8 u8PortIndexCpy, u8 u8PinIndexCpy, u8 u8PinValCpy);

/**********************************************************************************/
// Description: Get pin value
// Input	  : Port index, pin index and pin value
// Output	  : Error index
/**********************************************************************************/
extern u8 DIO_u8GetPinVal(u8 u8PortIndexCpy, u8 u8PinIndexCpy, u8* pu8PinValCpy);

#endif /* MCAL_DIO_DIO_INT_H_ */
