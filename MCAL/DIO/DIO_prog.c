/*
 * DIO_prog.c
 *
 *  Created on: Apr 15, 2019
 *      Author: Abram Saleh
 */

#include "../../LIB/types.h"
#include "../../LIB/util.h"
#include "DIO_priv.h"
#include "DIO_int.h"

/* Error Codes */
typedef enum
{
	ERR_PORT_INDEX,
	ERR_PIN_INDEX,
	ERR_PORT_DIR,
	ERR_PIN_DIR,
	ERR_PORT_VAL,
	ERR_PIN_VAL,
}ERROR;

/**********************************************************************************/
// Description: Set port direction
// Input	  : Port index and port direction
// Output	  : Error index
/**********************************************************************************/
extern u8 DIO_u8SetPortDir(u8 u8PortIndexCpy, u8 u8PortDirCpy)
{
	/* Make sure port direction is correct */
	if((u8PortDirCpy == PORT_INPUT) || (u8PortDirCpy == PORT_OUTPUT))
	{
		switch(u8PortIndexCpy)
		{
		case PORTA: DDRA_REG = u8PortDirCpy; break;
		case PORTB: DDRB_REG = u8PortDirCpy; break;
		case PORTC: DDRC_REG = u8PortDirCpy; break;
		case PORTD: DDRD_REG = u8PortDirCpy; break;
		default:	return ERR_PORT_INDEX;	 break;	// Invalid Port Index
		}
	}
	else
	{
		/* Invalid Port Direction */
		return ERR_PORT_DIR;
	}
}

/**********************************************************************************/
// Description: Set port value
// Input	  : Port index and port value
// Output	  : Error index
/**********************************************************************************/
extern u8 DIO_u8SetPortVal(u8 u8PortIndexCpy, u8 u8PortValCpy)
{
	/* Make sure port value is correct */
	if((u8PortValCpy == PORT_HIGH) || (u8PortValCpy == PORT_LOW))
	{
		switch(u8PortIndexCpy)
		{
		case PORTA: PORTA_REG = u8PortValCpy; break;
		case PORTB: PORTB_REG = u8PortValCpy; break;
		case PORTC: PORTC_REG = u8PortValCpy; break;
		case PORTD: PORTD_REG = u8PortValCpy; break;
		default:	return ERR_PORT_INDEX;	  break;	// Invalid Port Index
		}
	}
	else
	{
		/* Invalid Port Value */
		return ERR_PORT_VAL;
	}
}

/**********************************************************************************/
// Description: Set pin direction
// Input	  : Port index, pin index and pin direction
// Output	  : Error index
/**********************************************************************************/
extern u8 DIO_u8SetPinDir(u8 u8PortIndexCpy, u8 u8PinIndexCpy, u8 u8PinDirCpy)
{
	/* Make sure pin index is within valid range */
	if((u8PinIndexCpy >= PIN_MIN) && (u8PinIndexCpy <= PIN_MAX))
	{
		if(u8PinDirCpy == LOW)
		{
			switch(u8PortIndexCpy)
			{
			case PORTA: CLR_BIT(DDRA_REG, u8PinIndexCpy); break;
			case PORTB: CLR_BIT(DDRB_REG, u8PinIndexCpy); break;
			case PORTC: CLR_BIT(DDRC_REG, u8PinIndexCpy); break;
			case PORTD: CLR_BIT(DDRD_REG, u8PinIndexCpy); break;
			default:	return ERR_PORT_INDEX;	  		  break;	// Invalid Port Index
			}
		}
		else if(u8PinDirCpy == HIGH)
		{
			switch(u8PortIndexCpy)
			{
			case PORTA: SET_BIT(DDRA_REG, u8PinIndexCpy); break;
			case PORTB: SET_BIT(DDRB_REG, u8PinIndexCpy); break;
			case PORTC: SET_BIT(DDRC_REG, u8PinIndexCpy); break;
			case PORTD: SET_BIT(DDRD_REG, u8PinIndexCpy); break;
			default:	return ERR_PORT_INDEX;	  		  break;	// Invalid Port Index
			}
		}
		else
		{
			/* Invalid Pin Direction */
			return ERR_PIN_DIR;
		}
	}
	else
	{
		/* Invalid Pin Index */
		return ERR_PIN_INDEX;
	}
}

/**********************************************************************************/
// Description: Set pin value
// Input	  : Port index, pin index and pin value
// Output	  : Error index
/**********************************************************************************/
extern u8 DIO_u8SetPinVal(u8 u8PortIndexCpy, u8 u8PinIndexCpy, u8 u8PinValCpy)
{
	/* Make sure pin index is within valid range */
	if((u8PinIndexCpy >= PIN_MIN) && (u8PinIndexCpy <= PIN_MAX))
	{
		if(u8PinValCpy == LOW)
		{
			switch(u8PortIndexCpy)
			{
			case PORTA: CLR_BIT(PORTA_REG, u8PinIndexCpy); break;
			case PORTB: CLR_BIT(PORTB_REG, u8PinIndexCpy); break;
			case PORTC: CLR_BIT(PORTC_REG, u8PinIndexCpy); break;
			case PORTD: CLR_BIT(PORTD_REG, u8PinIndexCpy); break;
			default:	return ERR_PORT_INDEX;	  		   break;	// Invalid Port Index
			}
		}
		else if(u8PinValCpy == HIGH)
		{
			switch(u8PortIndexCpy)
			{
			case PORTA: SET_BIT(PORTA_REG, u8PinIndexCpy); break;
			case PORTB: SET_BIT(PORTB_REG, u8PinIndexCpy); break;
			case PORTC: SET_BIT(PORTC_REG, u8PinIndexCpy); break;
			case PORTD: SET_BIT(PORTD_REG, u8PinIndexCpy); break;
			default:	return ERR_PORT_INDEX;	  		   break;	// Invalid Port Index
			}
		}
		else
		{
			/* Invalid Pin Direction */
			return ERR_PIN_VAL;
		}
	}
	else
	{
		/* Invalid Pin Index */
		return ERR_PIN_INDEX;
	}
}

/**********************************************************************************/
// Description: Get pin value
// Input	  : Port index, pin index and pin value
// Output	  : Error index
/**********************************************************************************/
extern u8 DIO_u8GetPinVal(u8 u8PortIndexCpy, u8 u8PinIndexCpy, u8* pu8PinValCpy)
{
	/* Make sure pin index is within valid range */
	if((u8PinIndexCpy >= PIN_MIN) && (u8PinIndexCpy <= PIN_MAX))
	{
		switch(u8PortIndexCpy)
		{
		case PORTA: *pu8PinValCpy = GET_BIT(PINA_REG, u8PinIndexCpy); break;
		case PORTB: *pu8PinValCpy = GET_BIT(PINB_REG, u8PinIndexCpy); break;
		case PORTC: *pu8PinValCpy = GET_BIT(PINC_REG, u8PinIndexCpy); break;
		case PORTD: *pu8PinValCpy = GET_BIT(PIND_REG, u8PinIndexCpy); break;
		default:	return ERR_PORT_INDEX;	  		   				  break;	// Invalid Port Index
		}
	}
	else
	{
		/* Invalid Pin Index */
		return ERR_PIN_INDEX;
	}
}
