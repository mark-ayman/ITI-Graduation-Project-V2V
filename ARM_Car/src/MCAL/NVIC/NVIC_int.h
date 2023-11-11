/*
 * NVIC_int.h
 *
 *  Created on: Aug 13, 2023
 *      Author: admin
 */

#ifndef MCAL_NVIC_NVIC_INT_H_
#define MCAL_NVIC_NVIC_INT_H_

#define NVIC_16_GROUPS   0b011  // 3
#define NVIC_8_GROUPS    0b100  // 4
                                // 5   6  7


#define  NVIC_SYSTICK       -5
#define  NVIC_PEND_SV       -6

#define  NVIC_SV_CALL       -4

#define NVIC_USAGE_FAULT    -1
#define NVIC_BUS_FAULT      -2
#define NVIC_MEMORY_MANAGE  -3

void MNVIC_vEnableInteruptPeripheral(u8 A_u8IntId);

void MNVIC_vDisableInteruptPeripheral(u8 A_u8IntId);

/*Test SW int*/
void MNVIC_vSetPending(u8 A_u8IntId);

void MNVIC_vClearPending(u8 A_u8IntId);

//to check

u8 MNVIC_u8GetActive(u8 A_u8IntId);


void MNVIC_vSetPriorityCfg(u8 A_u8Group);

void MNVIC_vSetPriority(s8 A_s8IntId , u8 A_u8GroupPriority,u8 A_u8SubPriority);

#endif /* MCAL_NVIC_NVIC_INT_H_ */
