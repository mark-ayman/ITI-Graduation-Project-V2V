/*
 * TIMER_private.h
 *
 *  Created on: Aug 15, 2023
 *      Author: alibo
 */

#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_

#define TCCR0_REG      *(( volatile u8*)(0x53))
#define TCNT0_REG      *(( volatile u8*)(0x52))
#define OCR0_REG       *(( volatile u8*)(0x5C))
#define TIMSK_REG      *(( volatile u8*)(0x59))
#define TIFR_REG       *(( volatile u8*)(0x58))


#define TCCR1A_REG     *(( volatile u8*)(0x4F))
#define TCCR1B_REG     *(( volatile u8*)(0x4E))
#define TCNTI_REG      *(( volatile u16*)(0x4C))
#define OCR1A_REG      *(( volatile u16*)(0x4A))
#define OCR1B_REG      *(( volatile u16*)(0x48))
#define ICR1_REG       *(( volatile u16*)(0x46))


#define TOIE0_BIT     0
#define OCIE0_BIT     1

#define TOV0_BIT      0
#define OCF0_BIT      1


#endif /* MCAL_TIMER_TIMER_PRIVATE_H_ */
