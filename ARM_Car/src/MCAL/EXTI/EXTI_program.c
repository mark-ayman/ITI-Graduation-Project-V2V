/*
 * EXTI_prg.c
 *
 *  Created on: Aug 14, 2023
 *      Author: admin
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"

void (*CallBack[16])(void) = {0};
void MEXTI_vEnableLine(u8 A_u8Line,u8 A_u8Trigger)
{
	if(A_u8Line<16)
	{
		SET_BIT(EXTI->IMR,A_u8Line);
		MEXTI_vSetTrigger(A_u8Line,A_u8Trigger);
	}
}

void MEXTI_vDisableLine(u8 A_u8Line)
{
	if(A_u8Line<16)
		{
			CLR_BIT(EXTI->IMR,A_u8Line);
		}
}

void MEXTI_vSetTrigger(u8 A_u8Line,u8 A_u8Trigger)
{
	if(A_u8Line<16)
	{
		switch(A_u8Trigger)
		{
		case EXTI_RISING:
			SET_BIT(EXTI->RTSR,A_u8Line);
			CLR_BIT(EXTI->FTSR,A_u8Line);
			break;
		case EXTI_FAILING:
			CLR_BIT(EXTI->RTSR,A_u8Line);
			SET_BIT(EXTI->FTSR,A_u8Line);
			break;
		case EXTI_ONCHANGE:
			SET_BIT(EXTI->RTSR,A_u8Line);
			SET_BIT(EXTI->FTSR,A_u8Line);
			break;
		}
	}
}

void MEXTI_vSoftwareTrigger(u8 A_u8Line)
{
	SET_BIT(EXTI->SWIER,A_u8Line);
}
void MEXTI_vClearFlage(u8 A_u8Line)
{
	SET_BIT(EXTI->PR,A_u8Line);
}
void MEXTI_vSetCallBack (u8 A_u8Line ,void (*A_ptr)(void))//0,100
{
	switch(A_u8Line)
	{
	case EXTI_LINE0 :
		CallBack[0] = A_ptr;
		break;
	case EXTI_LINE1 :
		CallBack[1] = A_ptr;
		break;
	}
}
void EXTI0_IRQHandler (void)
{
	MEXTI_vClearFlage(EXTI_LINE0);
	if(CallBack[EXTI_LINE0]!=0) CallBack[EXTI_LINE0]();//100
}
void EXTI1_IRQHandler(void)
{
	MEXTI_vClearFlage(EXTI_LINE1);
	if(CallBack[1]!=0) CallBack[1]();//100
}
void EXTI9_5_IRQHandler (void)
{

}
