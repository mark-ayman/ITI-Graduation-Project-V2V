/*
 * TIMER_program.c
 *
 *  Created on: Aug 15, 2023
 *      Author: alibo
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_config.h"

static void (*Global_PtrToFun_Notification) (void) = NULL;



void Timer_voidT0Init(TIMER_CONFIG_T0 *Ptr_To_TIMERCONFIG)
{

	if( (Ptr_To_TIMERCONFIG->timer_mode) == NORMAL_MODE    ||  (Ptr_To_TIMERCONFIG->timer_mode) == CTC )
	{
		SET_BIT( TCCR0_REG , FOC0_BIT);
	}
	else
	{
		CLR_BIT( TCCR0_REG , FOC0_BIT);
	}

	switch (Ptr_To_TIMERCONFIG ->timer_mode)
	{
	case NORMAL_MODE:
		CLR_BIT(TCCR0_REG , WGMOO_BIT);
		CLR_BIT(TCCR0_REG , WGM01_BIT);
		break;

	case PWM_PHASE_CORRECT:
		SET_BIT(TCCR0_REG , WGMOO_BIT);
		CLR_BIT(TCCR0_REG , WGM01_BIT);
		break;

	case CTC:
		CLR_BIT(TCCR0_REG , WGMOO_BIT);
		SET_BIT(TCCR0_REG , WGM01_BIT);
		break;

	case FAST_PWM:
		SET_BIT(TCCR0_REG , WGMOO_BIT);
		SET_BIT(TCCR0_REG , WGM01_BIT);
		break;

	default :
		break;
	}

	TCCR0_REG &= 0xCF ;
	TCCR0_REG |= ( (Ptr_To_TIMERCONFIG->control_oc) << 4 );

	TCCR0_REG &= 0xF8 ;
	TCCR0_REG |= (Ptr_To_TIMERCONFIG->clock_source);

#if (TIMER0_TECHNIQUE == POLLING)

#elif (TIMER0_TECHNIQUE == INTRRUPT)
	switch (Ptr_To_TIMERCONFIG->timer_mode)
	{
	case NORMAL_MODE:
		SET_BIT(TIMSK_REG , TOIE0_BIT );
		break;

	case CTC:
		SET_BIT(TIMSK_REG , OCIE0_BIT );
		break;

	default:
		break;

	}
#endif

}


void Timer_voidT0Dinit (void)
{
	OCR0_REG   = 0;
	TCCR0_REG  = 0;
	TCNT0_REG  = 0;
	TIMSK_REG &= 0xFC;
}

void Timer_StartT0(TIMER_CONFIG_T0 *Ptr_To_TIMERCONFIG,u8 value)
{
#if (TIMER0_TECHNIQUE == POLLING)

	switch (Ptr_To_TIMERCONFIG->timer_mode)
	{
	case NORMAL_MODE:
		TCNT0_REG = Ptr_To_TIMERCONFIG->Preload_Value;

		while( GET_BIT(TIFR_REG , TOV0_BIT) == 0);
		//CLEARING THE FLAG:
		SET_BIT(TIFR_REG , TOV0_BIT);
		break;

	case CTC:
		TCNT0_REG = Ptr_To_TIMERCONFIG->Preload_Value;
		OCR0_REG = Ptr_To_TIMERCONFIG->Compare_Value;
		while( GET_BIT(TIFR_REG , OCF0_BIT) == 0);
		//CLEARING THE FLAG:
		SET_BIT(TIFR_REG , OCF0_BIT);
		break;
	case FAST_PWM:
		//OCR0_REG = Ptr_To_TIMERCONFIG->Compare_Value;
		OCR0_REG = value;
		break;

	case PWM_PHASE_CORRECT:
		OCR0_REG = Ptr_To_TIMERCONFIG->Compare_Value;
		break;

	default:
		break;
	}

#elif (TIMER0_TECHNIQUE == INTRRUPT)
	switch (Ptr_To_TIMERCONFIG->timer_mode)
	{
	case NORMAL_MODE:
		TCNT0_REG = Ptr_To_TIMERCONFIG->Preload_Value;
		break;

	case CTC:
		TCNT0_REG = Ptr_To_TIMERCONFIG->Preload_Value;
		OCR0_REG = Ptr_To_TIMERCONFIG->Compare_Value;
		break;
	case FAST_PWM:
		OCR0_REG = Ptr_To_TIMERCONFIG->Compare_Value;
		break;

	case PWM_PHASE_CORRECT:
		OCR0_REG = Ptr_To_TIMERCONFIG->Compare_Value;
		break;

	default:
		break;
	}

#endif

}



void Timer_voidCallBackFun(void(*Ptr_To_Fun)(void))
{
	if(Ptr_To_Fun != NULL)
	{
		Global_PtrToFun_Notification = Ptr_To_Fun;
	}
}


void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	//ctc
	if(Global_PtrToFun_Notification != NULL)
	(*Global_PtrToFun_Notification)();


}
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	// ovf
	if(Global_PtrToFun_Notification != NULL)
	(*Global_PtrToFun_Notification)();

}



void Timer_voidT1Init( TIMER_CONFIG_T1 *Ptr_To_TIMERCONFIG)
{
	// timer_mode
	TCCR1A_REG &= 0xFC ;
	TCCR1A_REG |= ( ( (Ptr_To_TIMERCONFIG->timer_mode_T1) & 0b0011) );

	TCCR1B_REG &= 0xE7 ;
	TCCR1B_REG |= ( ( (Ptr_To_TIMERCONFIG->timer_mode_T1) & 0b1100 ) << 1 );


	//oc control
	TCCR1A_REG &= 0x3F ;
	TCCR1A_REG |= ( (Ptr_To_TIMERCONFIG->control_oc_T1) << 6 );


	//clock source
	TCCR0_REG &= 0xF8 ;
	TCCR1B_REG |= (Ptr_To_TIMERCONFIG->clock_source_T1);

	Timer_voidSetICRValueT1(20000);
}

void Timer_voidSetCompareMatchValueT1A (u16 Copy)
{
	OCR1A_REG = Copy;
}

void Timer_voidSetICRValueT1 (u16 Copy)
{
	ICR1_REG = Copy;
}
