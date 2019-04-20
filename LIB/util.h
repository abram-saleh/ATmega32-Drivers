/*
 * util.h
 *
 *  Created on: Apr 15, 2019
 *      Author: Abram Saleh
 */

#ifndef LIB_UTIL_H_
#define LIB_UTIL_H_

/**********************************************************************************/
/*************************** Utilities Definitions ********************************/
/**********************************************************************************/

/* Bit Math */
#define CLR_BIT(REG, BITNO) ( (REG) &= ~( (0x01) << (BITNO) ) )
#define SET_BIT(REG, BITNO) ( (REG) |=  ( (0x01) << (BITNO) ) )
#define TOG_BIT(REG, BITNO) ( (REG) ^=  ( (0x01) << (BITNO) ) )
#define GET_BIT(REG, BITNO) ( ( (REG) >> (BITNO) ) & (0x01) )

/* Lower Nibble Math */
#define CLR_LOW_NIB(REG) ( (REG) &= ~(0x0F) )
#define SET_LOW_NIB(REG) ( (REG) |=  (0x0F) )
#define TOG_LOW_NIB(REG) ( (REG) ^=  (0x0F) )
#define GET_LOW_NIB(REG) ( (REG) &   (0x0F) )

/* Higher Nibble Math */
#define CLR_HIGH_NIB(REG) ( (REG) &= ~(0xF0) )
#define SET_HIGH_NIB(REG) ( (REG) |=  (0xF0) )
#define TOG_HIGH_NIB(REG) ( (REG) ^=  (0xF0) )
#define GET_HIGH_NIB(REG) ( ( (REG) >> (0x04) ) &  (0x0F) )

/* 8-bit Register Math */
#define CLR_REG(REG) ( (REG) &= ~(0xFF) )
#define SET_REG(REG) ( (REG) |=  (0xFF) )
#define TOG_REG(REG) ( (REG) ^=  (0xFF) )
#define GET_REG(REG)		(REG)

#endif /* LIB_UTIL_H_ */
