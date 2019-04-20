/*
 * DIO_priv.h
 *
 *  Created on: Apr 15, 2019
 *      Author: Abram Saleh
 */

#ifndef MCAL_DIO_DIO_PRIV_H_
#define MCAL_DIO_DIO_PRIV_H_

/**********************************************************************************/
/*************************** Private Definitions **********************************/
/**********************************************************************************/

/* States */
#define LOW  0
#define HIGH 1

/****************************** DIO Registers *************************************/

#define DDRA_REG  *( (volatile u8*) 0x3A ) // Port A Data Direction Register – DDRA
#define PORTA_REG *( (volatile u8*) 0x3B ) // Port A Data Register – PORTA
#define PINA_REG  *( (volatile u8*) 0x39 ) // Port A Input Pins Address – PINA

#define DDRB_REG  *( (volatile u8*) 0x37 ) // Port B Data Direction Register – DDRB
#define PORTB_REG *( (volatile u8*) 0x38 ) // Port B Data Register – PORTB
#define PINB_REG  *( (volatile u8*) 0x36 ) // Port B Input Pins Address – PINB

#define DDRC_REG  *( (volatile u8*) 0x34 ) // Port C Data Direction Register – DDRC
#define PORTC_REG *( (volatile u8*) 0x35 ) // Port C Data Register – PORTC
#define PINC_REG  *( (volatile u8*) 0x33 ) // Port C Input Pins Address – PINC

#define DDRD_REG  *( (volatile u8*) 0x31 ) // Port D Data Direction Register – DDRD
#define PORTD_REG *( (volatile u8*) 0x32 ) // Port D Data Register – PORTD
#define PIND_REG  *( (volatile u8*) 0x30 ) // Port D Input Pins Address – PIND


#endif /* MCAL_DIO_DIO_PRIV_H_ */
