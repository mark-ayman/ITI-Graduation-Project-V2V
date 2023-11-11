

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../RCC/RCC_int.h"
#include "../GPIO/GPIO_int.h"

#include "Timer_init.h"
#include "Timer_register.h"
#include "Timer_private.h"
#include "Timer_conf.h"

u64 Ticks=0;

u8 CallBackFlag=0;

static volatile void (*MTimer_CallBackPTR) (void) = NULL ;

static void  MTimer_voidSetTimer_Channel(u8 A_u8TimerSelected , u8 A_u8Channel );

static void  MTimer_voidSetTimer_Channel(u8 A_u8TimerSelected , u8 A_u8Channel )
{
	switch (A_u8TimerSelected)
	{
	case TIM1_TYPE:
		/* Enable of TIM1 from RCC */
		MRCC_vEnableClock(RCC_AHB1, RCC_EN_GPIOA);
		MRCC_vEnableClock(RCC_APB2 , 0);

		GPIO_cfg_t PIN8 ={.port=GPIO_PORTA ,.pin =GPIO_PIN8,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =GPIO_AF1};
		GPIO_cfg_t PIN9 ={.port=GPIO_PORTA ,.pin =GPIO_PIN9,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =GPIO_AF1};
		GPIO_cfg_t PIN10 ={.port=GPIO_PORTA ,.pin =GPIO_PIN10,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =GPIO_AF1};
		GPIO_cfg_t PIN11 ={.port=GPIO_PORTA ,.pin =GPIO_PIN11,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =GPIO_AF1};

		switch (A_u8Channel){
		/*configer PA8 as alt fun (T1C1)*/
		case TIM_CHANNEL_1: MGPIO_vInit(&PIN8); break;
		/*configer PA9 as alt fun (T1C2)*/
		case TIM_CHANNEL_2: MGPIO_vInit(&PIN9); break;
		/*configer PA10 as alt fun (T1C3)*/
		case TIM_CHANNEL_3:MGPIO_vInit(&PIN10); break;
		/*configer PA11 as alt fun (T1C4)*/
		case TIM_CHANNEL_4:MGPIO_vInit(&PIN11);break;
		}
		break;
	case TIM2_TYPE :
		/* Enable of TIM2 from RCC */
		MRCC_vEnableClock(RCC_APB1 ,0);
		/*Configure pins without initialze them */
		/*Inialization is according to choosing the channel */
		GPIO_cfg_t PIN5 ={.port=GPIO_PORTA ,.pin =GPIO_PIN5,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =GPIO_AF1};
		GPIO_cfg_t PIN3_B ={.port=GPIO_PORTB ,.pin =GPIO_PIN3,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =GPIO_AF1};
		GPIO_cfg_t PIN10_B ={.port=GPIO_PORTB ,.pin =GPIO_PIN10,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =GPIO_AF1};
		GPIO_cfg_t PIN3 ={.port=GPIO_PORTA ,.pin =GPIO_PIN3,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =GPIO_AF1};
		switch(A_u8Channel)
		{
		/*configer PA0 as alt fun (T2C1 , T2ET)*/
		case TIM_CHANNEL_1:MGPIO_vInit(&PIN5);break;
		/*configer PA1 as alt fun (T2C2)*/
		case TIM_CHANNEL_2:MGPIO_vInit(&PIN3_B);break;
		/*configer PA2 as alt fun (T2C3)*/
		case TIM_CHANNEL_3:MGPIO_vInit(&PIN10_B);break;
		/*configer PA4 as alt fun (T2C)*/
		case TIM_CHANNEL_4:MGPIO_vInit(&PIN3);break;
		}
		break;
	case TIM3_TYPE :
		/* Enable of TIM3 from RCC */
		MRCC_vEnableClock(RCC_APB1 , 1);
		/*Configure pins without initialze them */
		/*Inialization is according to choosing the channel */
		GPIO_cfg_t PIN6 ={.port=GPIO_PORTA ,.pin =GPIO_PIN6,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =2};
		GPIO_cfg_t PIN7 ={.port=GPIO_PORTA ,.pin =GPIO_PIN7,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =2};
		GPIO_cfg_t PIN0_B ={.port=GPIO_PORTB ,.pin =GPIO_PIN0,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =2};
		GPIO_cfg_t PIN1_B ={.port=GPIO_PORTB ,.pin =GPIO_PIN1,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =2};
		switch(A_u8Channel)
		{
		/*configer PA6 as alt fun (T3C1 , T2ET)*/
		case TIM_CHANNEL_1: MGPIO_vInit(&PIN6);break;
		/*configer PA7 as alt fun (T3C2)*/
		case TIM_CHANNEL_2:MGPIO_vInit(&PIN7);break;
		/*configer PA8 as alt fun (T3C3)*/
		case TIM_CHANNEL_3:MGPIO_vInit(&PIN0_B);break;
		/*configer PA9 as alt fun (T3C4)*/
		case TIM_CHANNEL_4:MGPIO_vInit(&PIN1_B);break;
		}
		break;
	case TIM4_TYPE :
		/* Enable of TIM4 from RCC */
		MRCC_vEnableClock(RCC_APB1, 2);
		/*Configure pins without initialze them */
		/*Inialization is according to choosing the channel */
		GPIO_cfg_t PIN6_B ={.port=GPIO_PORTB ,.pin =GPIO_PIN6,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =2};
		GPIO_cfg_t PIN7_B ={.port=GPIO_PORTB ,.pin =GPIO_PIN7,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =2};
		GPIO_cfg_t PIN8_B ={.port=GPIO_PORTB ,.pin =GPIO_PIN8,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =2};
		GPIO_cfg_t PIN9_B ={.port=GPIO_PORTB ,.pin =GPIO_PIN9,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =2};
		switch(A_u8Channel)
		{
		/*configer PB6 as alt fun (T4C1)*/
		case TIM_CHANNEL_1 :MGPIO_vInit(&PIN6_B);break;
		/*configer PB7 as alt fun (T4C2)*/
		case TIM_CHANNEL_2 :MGPIO_vInit(&PIN7_B);break;
		/*configer PB8 as alt fun (T4C3)*/
		case TIM_CHANNEL_3 :MGPIO_vInit(&PIN8_B);break;
		/*configer PB9 as alt fun (T4C4)*/
		case TIM_CHANNEL_4 :MGPIO_vInit(&PIN9_B);break;
		}
		break;
	case TIM5_TYPE :
		/* Enable of TIM5 from RCC */
		MRCC_vEnableClock(RCC_APB1,3);
		GPIO_cfg_t PIN0_A ={.port=GPIO_PORTA ,.pin =GPIO_PIN0,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =2};
		GPIO_cfg_t PIN1_A ={.port=GPIO_PORTA ,.pin =GPIO_PIN1,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =2};
		GPIO_cfg_t PIN2_A ={.port=GPIO_PORTA ,.pin =GPIO_PIN2,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =2};
		GPIO_cfg_t PIN3_A ={.port=GPIO_PORTA ,.pin =GPIO_PIN3,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun =2};
		switch(A_u8Channel)
		{
		/*configer PA0 as alt fun (T5C1)*/
		case TIM_CHANNEL_1 :MGPIO_vInit(&PIN0_A);break;
		/*configer PA1 as alt fun (T5C2)*/
		case TIM_CHANNEL_2 :MGPIO_vInit(&PIN1_A);break;
		/*configer PA2 as alt fun (T5C3)*/
		case TIM_CHANNEL_3 :MGPIO_vInit(&PIN2_A);break;
		/*configer PA3 as alt fun (T5C4)*/
		case TIM_CHANNEL_4 :MGPIO_vInit(&PIN3_A);break;
		}
		break;
	}
}

void MTimer_voidInit (u8 A_u8TimerSelected ,  u8 A_u8Channel)
{

	/* initialization RCC */
	MRCC_vInit();

	/* Enable pinout of ADC (PortA , PORTB) from RCC */

	MRCC_vEnableClock(RCC_AHB1, RCC_EN_GPIOA);
	MRCC_vEnableClock(RCC_AHB1 , RCC_EN_GPIOB) ;



	switch (A_u8TimerSelected)
	{
	case TIM1_TYPE  :
		/******************************************************************************/
		/**                             Init TIM1                                    **/
		/******************************************************************************/
		MTimer_voidSetTimer_Channel(A_u8TimerSelected,A_u8Channel);
		/* Select the Direction */
#if   TIM1_DIRECTION == UP_COUNTER
		CLR_BIT(TIM_1->CR1 , TIM1_CR1_DIR_BIT) ;
#elif TIM1_DIRECTION == DOWN_COUNTER
		SET_BIT(TIM_1 , TIM1_CR1_DIR_BIT) ;
#else
#error "Invalid Selection of TIM1_DIRECTION"
#endif

		/* Edge-aligned mode */
		CLR_BIT(TIM_1->CR1 , TIM1_CR1_CMS_BIT0) ;
		CLR_BIT(TIM_1->CR1 , TIM1_CR1_CMS_BIT1) ;

		/* set the timer division */
#if   TIM1_DIVISION == tCK_INT_x_1
		CLR_BIT(TIM_1->CR1 , TIM1_CR1_CKD_BIT0) ;
		CLR_BIT(TIM_1->CR1 , TIM1_CR1_CKD_BIT1) ;
#elif TIM1_DIVISION == tCK_INT_x_2
		SET_BIT(TIM_1->CR1 , TIM1_CR1_CKD_BIT0) ;
		CLR_BIT(TIM_1->CR1 , TIM1_CR1_CKD_BIT1) ;
#elif TIM1_DIVISION == tCK_INT_x_4
		CLR_BIT(TIM_1->CR1 , TIM1_CR1_CKD_BIT0) ;
		SET_BIT(TIM_1->CR1 , TIM1_CR1_CKD_BIT1) ;
#else
#error "Invalid Selection of TIM1_DIVISION"
#endif

		/* set the timer prescaller */
#if    TIM1_PRESCALLER <= MAX_TIM_PRESCALLER
		TIM_1 ->PSC = TIM1_PRESCALLER ;
#else
#error "TIM1_PRESCALLER out of range"
#endif

		/* Enable auto-reload preload */
		SET_BIT(TIM_1->CR1 , TIM1_CR1_ARPE_BIT) ;

		/* Set the Auto-reload value */
#if  TIM1_PRELOAD_VALUE <= MAX_TIM_PRELOAD_VALUE
		TIM_1->ARR = TIM1_PRELOAD_VALUE ;
#else
#error "TIM1_PRELOAD_VALUE out of range"
#endif

		/* Set the Repetition Counter value */
#if REPETATION_COUNTER <= MAX_TIM_REPETATION_COUNTER
		TIM_1 -> RCR = REPETATION_COUNTER ;
#else
#error "REPETATION_COUNTER out of range"
#endif

		/* Generate an update event to reload the Prescaler
            and the repetition counter(only for TIM1 and TIM5) value immediately */
		SET_BIT(TIM_1->EGR , TIM1_EGR_UG_BIT );

		break ;
	case TIM2_TYPE  :
		/******************************************************************************/
		/**                             Init TIM2                                    **/
		/******************************************************************************/

		MTimer_voidSetTimer_Channel(A_u8TimerSelected,A_u8Channel);

		/* Disable slave mode to clock the prescaler directly with the internal clock */
		SET_BIT(TIM_2 -> SMCR , TIM2_TO_TIM5_SMCR_MSM_BIT );

		/* Select the Direction */
#if   TIM2_DIRECTION == UP_COUNTER
		CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
#elif TIM2_DIRECTION == DOWN_COUNTER
		SET_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
#else
#error "Invalid Selection of TIM2_DIRECTION"
#endif

		/* Edge-aligned mode */
		CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT0) ;
		CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT1) ;

		/* set the timer division */
#if   TIM2_DIVISION == tCK_INT_x_1
		CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
#elif TIM1_DIVISION == tCK_INT_x_2
		SET_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
#elif TIM1_DIVISION == tCK_INT_x_4
		CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		SET_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
#else
#error "Invalid Selection of TIM2_DIVISION"
#endif

		/* set the timer prescaller */
#if    TIM2_PRESCALLER <= MAX_TIM_PRESCALLER
		TIM_2 ->PSC = TIM2_PRESCALLER ;
#else
#error "TIM2_PRESCALLER out of range"
#endif

		/* Enable auto-reload preload */
		SET_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_ARPE_BIT) ;

		/* Set the Auto-reload value */
#if  TIM2_PRELOAD_VALUE <= MAX_TIM_PRELOAD_VALUE
		TIM_2->ARR = TIM2_PRELOAD_VALUE ;
#else
#error "TIM2_PRELOAD_VALUE out of range"
#endif

		/* Generate an update event to reload the Prescaler
	         and the repetition counter(only for TIM1 and TIM5) value immediately */
		SET_BIT(TIM_2->EGR , TIM2_TO_TIM5_EGR_UG_BIT );

		break ;
	case TIM3_TYPE  :
		/******************************************************************************/
		/**                             Init TIM3                                    **/
		/******************************************************************************/
		MTimer_voidSetTimer_Channel(A_u8TimerSelected,A_u8Channel);
		/* Disable slave mode to clock the prescaler directly with the internal clock */
		SET_BIT(TIM_3 -> SMCR , TIM2_TO_TIM5_SMCR_MSM_BIT );

		/* Select the Direction */
#if   TIM3_DIRECTION == UP_COUNTER
		CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
#elif TIM3_DIRECTION == DOWN_COUNTER
		SET_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
#else
#error "Invalid Selection of TIM3_DIRECTION"
#endif

		/* Edge-aligned mode */
		CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT0) ;
		CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT1) ;

		/* set the timer division */
#if   TIM3_DIVISION == tCK_INT_x_1
		CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
#elif TIM3_DIVISION == tCK_INT_x_2
		SET_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
#elif TIM3_DIVISION == tCK_INT_x_4
		CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		SET_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
#else
#error "Invalid Selection of TIM3_DIVISION"
#endif

		/* set the timer prescaller */
#if    TIM3_PRESCALLER <= MAX_TIM_PRESCALLER
		TIM_3 ->PSC = TIM3_PRESCALLER ;
#else
#error "TIM3_PRESCALLER out of range"
#endif

		/* Enable auto-reload preload */
		SET_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_ARPE_BIT) ;

		/* Set the Auto-reload value */
#if  TIM3_PRELOAD_VALUE <= MAX_TIM_PRELOAD_VALUE
		TIM_3->ARR = TIM3_PRELOAD_VALUE ;
#else
#error "TIM3_PRELOAD_VALUE out of range"
#endif

		/* Generate an update event to reload the Prescaler
			 and the repetition counter(only for TIM1 and TIM5) value immediately */
		SET_BIT(TIM_3->EGR , TIM2_TO_TIM5_EGR_UG_BIT );

		break ;
	case TIM4_TYPE  :
		/******************************************************************************/
		/**                             Init TIM4                                    **/
		/******************************************************************************/
		MTimer_voidSetTimer_Channel(A_u8TimerSelected,A_u8Channel);
		/* Disable slave mode to clock the prescaler directly with the internal clock */
		SET_BIT(TIM_4 -> SMCR , TIM2_TO_TIM5_SMCR_MSM_BIT );

		/* Select the Direction */
#if   TIM4_DIRECTION == UP_COUNTER
		CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
#elif TIM4_DIRECTION == DOWN_COUNTER
		SET_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
#else
#error "Invalid Selection of TIM4_DIRECTION"
#endif

		/* Edge-aligned mode */
		CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT0) ;
		CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT1) ;

		/* set the timer division */
#if   TIM4_DIVISION == tCK_INT_x_1
		CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
#elif TIM4_DIVISION == tCK_INT_x_2
		SET_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
#elif TIM4_DIVISION == tCK_INT_x_4
		CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		SET_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
#else
#error "Invalid Selection of TIM4_DIVISION"
#endif

		/* set the timer prescaller */
#if    TIM4_PRESCALLER <= MAX_TIM_PRESCALLER
		TIM_4 ->PSC = TIM4_PRESCALLER ;
#else
#error "TIM4_PRESCALLER out of range"
#endif

		/* Enable auto-reload preload */
		SET_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_ARPE_BIT) ;

		/* Set the Auto-reload value */
#if  TIM4_PRELOAD_VALUE <= MAX_TIM_PRELOAD_VALUE
		TIM_4->ARR = TIM4_PRELOAD_VALUE ;
#else
#error "TIM4_PRELOAD_VALUE out of range"
#endif

		/* Generate an update event to reload the Prescaler
				    	  and the repetition counter(only for TIM1 and TIM5) value immediately */
		SET_BIT(TIM_4->EGR , TIM2_TO_TIM5_EGR_UG_BIT );
		break ;
	case TIM5_TYPE  :
		/******************************************************************************/
		/**                             Init TIM5                                    **/
		/******************************************************************************/
		MTimer_voidSetTimer_Channel(A_u8TimerSelected,A_u8Channel);

		/* Disable slave mode to clock the prescaler directly with the internal clock */
		SET_BIT(TIM_5 -> SMCR , TIM2_TO_TIM5_SMCR_MSM_BIT );

		/* Select the Direction */
#if   TIM5_DIRECTION == UP_COUNTER
		CLR_BIT(TIM_5->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
#elif TIM5_DIRECTION == DOWN_COUNTER
		SET_BIT(TIM_5->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
#else
#error "Invalid Selection of TIM5_DIRECTION"
#endif

		/* Edge-aligned mode */
		CLR_BIT(TIM_5->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT0) ;
		CLR_BIT(TIM_5->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT1) ;

		/* set the timer division */
#if   TIM5_DIVISION == tCK_INT_x_1
		CLR_BIT(TIM_5->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		CLR_BIT(TIM_5->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
#elif TIM5_DIVISION == tCK_INT_x_2
		SET_BIT(TIM_5->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		CLR_BIT(TIM_5->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
#elif TIM5_DIVISION == tCK_INT_x_4
		CLR_BIT(TIM_5->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		SET_BIT(TIM_5->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
#else
#error "Invalid Selection of TIM5_DIVISION"
#endif

		/* set the timer prescaller */
#if    TIM5_PRESCALLER <= MAX_TIM_PRESCALLER
		TIM_5 ->PSC = TIM5_PRESCALLER ;
#else
#error "TIM5_PRESCALLER out of range"
#endif

		/* Enable auto-reload preload */
		SET_BIT(TIM_5->CR1 , TIM2_TO_TIM5_CR1_ARPE_BIT) ;

		/* Set the Auto-reload value */
#if  TIM5_PRELOAD_VALUE <= MAX_TIM_PRELOAD_VALUE
		TIM_5->ARR = TIM5_PRELOAD_VALUE ;
#else
#error "TIM5_PRELOAD_VALUE out of range"
#endif

		/* Generate an update event to reload the Prescaler
				     	  and the repetition counter(only for TIM1 and TIM5) value immediately */
		SET_BIT(TIM_5->EGR , TIM2_TO_TIM5_EGR_UG_BIT );

		break ;
	default :
		/*invalid selected type*/
		break ;
	}
}

void MTimer_voidPWM (u8 A_u8TimerSelected , u8 A_u8Channel , u16 A_u16CompareValue)
{
	if (A_u8TimerSelected == TIM1_TYPE)
	{
		if (A_u8Channel == TIM_CHANNEL_1)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 1: Reset the CC1E Bit */
			CLR_BIT(TIM_1->CCER , TIM1_CCER_CC1E_BIT) ;

			/* Get the TIM CCER register value */
			L_u32TempCCMRX = TIM_1->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_1->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_1->CCMR1;

			/* Reset the Output Compare Mode Bits */
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC1M_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC1M_BIT1) ;
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC1M_BIT2) ;
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_CC1S_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_CC1S_BIT1) ;
			/* Select the Output Compare Mode1 */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC1P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC1NP_BIT) ;
			/* Reset the Output N State */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC1NE_BIT) ;

			/* Reset the Output Compare and Output Compare N IDLE State */
			CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS1N_BIT) ;
			CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS1N_BIT) ;

			/* Write to TIM CR2 */
			TIM_1->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_1->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_1->CCR1 = A_u16CompareValue ;

			/* Write to TIM CCER */
			TIM_1->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel1 */
			SET_BIT (TIM_1->CCMR1 , TIM1_CCMR1_OC1PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_1->CCMR1 , TIM1_CCMR1_OC1FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_1-> CCER , TIM1_CCER_CC1E_BIT) ;

			/* Enable the main output */
			SET_BIT(TIM_1 ->BDTR , TIM1_BDTR_MOE_BIT ) ;

			/* Enable the timer */
			SET_BIT(TIM_1 -> CR1 , TIM1_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_2)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 2: Reset the CC2E Bit */
			CLR_BIT(TIM_1->CCER , TIM1_CCER_CC2E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_1->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_1->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_1->CCMR1;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC2M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC2M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_CC2S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_CC2S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC2P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC2NP_BIT) ;

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC2NP_BIT) ;
			/* Reset the Output N State */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC2NE_BIT);

			/* Reset the Output Compare and Output Compare N IDLE State */
			CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS2_BIT);
			CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS2N_BIT);

			/* Write to TIM CR2 */
			TIM_1->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_1->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_1->CCR2 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_1->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel2 */
			SET_BIT (TIM_1->CCMR1 , TIM1_CCMR1_OC2PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_1->CCMR1 , TIM1_CCMR1_OC2FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_1-> CCER , TIM1_CCER_CC2E_BIT) ;

			/* Enable the main output */
			SET_BIT(TIM_1 ->BDTR , TIM1_BDTR_MOE_BIT ) ;

			/* Enable the timer */
			SET_BIT(TIM_1 -> CR1 , TIM1_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_3)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 3: Reset the CC2E Bit */
			CLR_BIT(TIM_1->CCER , TIM1_CCER_CC3E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_1->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_1->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_1->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR2_OC3M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR2_OC3M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR2_CC3S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR2_CC3S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U);

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC3P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC3NP_BIT) ;

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC3NP_BIT) ;
			/* Reset the Output N State */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC3NE_BIT);

			/* Reset the Output Compare and Output Compare N IDLE State */
			CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS3_BIT);
			CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS3N_BIT);

			/* Write to TIM CR2 */
			TIM_1->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_1->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_1->CCR3 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_1->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel3 */
			SET_BIT (TIM_1->CCMR2 , TIM1_CCMR2_OC3PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_1->CCMR2 , TIM1_CCMR2_OC3FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_1-> CCER , TIM1_CCER_CC3E_BIT) ;

			/* Enable the main output */
			SET_BIT(TIM_1 ->BDTR , TIM1_BDTR_MOE_BIT ) ;

			/* Enable the timer */
			SET_BIT(TIM_1 -> CR1 , TIM1_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_4)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 4: Reset the CC2E Bit */
			CLR_BIT(TIM_1->CCER , TIM1_CCER_CC4E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_1->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_1->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_1->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC2M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC2M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_CC2S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_CC2S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC4P_BIT);

			/* Reset the Output Compare IDLE State */
			CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS4_BIT);

			/* Write to TIM CR2 */
			TIM_1->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_1->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_1->CCR4 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_1->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel4 */
			SET_BIT (TIM_1->CCMR2 , TIM1_CCMR2_OC4PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_1->CCMR2 , TIM1_CCMR2_OC4FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_1-> CCER , TIM1_CCER_CC4E_BIT) ;

			/* Enable the main output */
			SET_BIT(TIM_1 ->BDTR , TIM1_BDTR_MOE_BIT ) ;

			/* Enable the timer */
			SET_BIT(TIM_1 -> CR1 , TIM1_CR1_CEN_BIT) ;
		}
	}
	else if (A_u8TimerSelected == TIM2_TYPE)
	{
		if (A_u8Channel == TIM_CHANNEL_1)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 1: Reset the CC1E Bit */
			CLR_BIT(TIM_2->CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_2->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_2->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_2->CCMR1;

			/* Reset the Output Compare Mode Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT1) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT2) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT1) ;
			/* Select the Output Compare Mode1 */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			SET_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC1P_BIT);

			/* Write to TIM CR2 */
			TIM_2->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_2->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_2->CCR1 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_2->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel1 */
			SET_BIT (TIM_2->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_2->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_2-> CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_2 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_2)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 2: Reset the CC2E Bit */
			CLR_BIT(TIM_2->CCER , TIM2_TO_TIM5_CCER_CC2E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_2->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_2->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_2->CCMR1;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT2);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT1);
			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2NP_BIT) ;

			/* Write to TIM CR2 */
			TIM_2->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_2->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_2->CCR2 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_2->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel2 */
			SET_BIT (TIM_2->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_2->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_2-> CCER , TIM2_TO_TIM5_CCER_CC2E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_2 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_3)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 3: Reset the CC2E Bit */
			CLR_BIT(TIM_2->CCER , TIM2_TO_TIM5_CCER_CC3E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_2->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_2->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_2->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT2);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			SET_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3NP_BIT) ;

			/* Write to TIM CR2 */
			TIM_2->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_2->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_2->CCR3 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_2->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel3 */
			SET_BIT (TIM_2->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_2->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_2-> CCER , TIM2_TO_TIM5_CCER_CC3E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_2 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_4)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 4: Reset the CC2E Bit */
			CLR_BIT(TIM_2->CCER , TIM2_TO_TIM5_CCER_CC4E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_2->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_2->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_2->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC4M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC4M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC4M_BIT2);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC4S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC4S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC4P_BIT);

			/* Write to TIM CR2 */
			TIM_2->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_2->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_2->CCR4 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_2->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel4 */
			SET_BIT (TIM_2->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_2->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_2-> CCER , TIM2_TO_TIM5_CCER_CC4E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_2 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
	}
	else if (A_u8TimerSelected == TIM3_TYPE)
	{
		if (A_u8Channel == TIM_CHANNEL_1)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 1: Reset the CC1E Bit */
			CLR_BIT(TIM_3->CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Get the TIM CCER register value */
			L_u32TempCCMRX = TIM_3->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_3->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_3->CCMR1;

			/* Reset the Output Compare Mode Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT1) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT2) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT1) ;
			/* Select the Output Compare Mode1 */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC1P_BIT);

			/* Write to TIM CR2 */
			TIM_3->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_3->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_3->CCR1 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_3->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel1 */
			SET_BIT (TIM_3->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_3->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_3-> CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_3 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_2)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 2: Reset the CC2E Bit */
			CLR_BIT(TIM_3->CCER , TIM2_TO_TIM5_CCER_CC2E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_3->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_3->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_3->CCMR1;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2NP_BIT) ;

			/* Write to TIM CR2 */
			TIM_3->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_3->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_3->CCR2 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_3->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel2 */
			SET_BIT (TIM_3->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_3->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_3-> CCER , TIM2_TO_TIM5_CCER_CC2E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_3 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_3)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 3: Reset the CC2E Bit */
			CLR_BIT(TIM_3->CCER , TIM2_TO_TIM5_CCER_CC3E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_3->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_3->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_3->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 <<4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3NP_BIT) ;

			/* Write to TIM CR2 */
			TIM_3->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_3->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_3->CCR3 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_3->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel3 */
			SET_BIT (TIM_3->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_3->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_3-> CCER , TIM2_TO_TIM5_CCER_CC3E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_3 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_4)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 4: Reset the CC2E Bit */
			CLR_BIT(TIM_3->CCER , TIM2_TO_TIM5_CCER_CC4E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_3->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_3->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_3->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC4P_BIT);

			/* Write to TIM CR2 */
			TIM_3->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_3->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_3->CCR4 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_3->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel4 */
			SET_BIT (TIM_3->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_3->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_3-> CCER , TIM2_TO_TIM5_CCER_CC4E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_3 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
	}
	else if (A_u8TimerSelected == TIM4_TYPE)
	{
		if (A_u8Channel == TIM_CHANNEL_1)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 1: Reset the CC1E Bit */
			CLR_BIT(TIM_4->CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Get the TIM CCER register value */
			L_u32TempCCMRX = TIM_4->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_4->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_4->CCMR1;

			/* Reset the Output Compare Mode Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT1) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT2) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT1) ;
			/* Select the Output Compare Mode1 */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC1P_BIT);

			/* Write to TIM CR2 */
			TIM_4->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_4->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_4->CCR1 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_4->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel1 */
			SET_BIT (TIM_4->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_4->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_4-> CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_4 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_2)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 2: Reset the CC2E Bit */
			CLR_BIT(TIM_4->CCER , TIM2_TO_TIM5_CCER_CC2E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_4->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_4->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_4->CCMR1;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2NP_BIT) ;

			/* Write to TIM CR2 */
			TIM_4->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_4->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_4->CCR2 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_4->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel2 */
			SET_BIT (TIM_4->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_4->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_4-> CCER , TIM2_TO_TIM5_CCER_CC2E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_4 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_3)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 3: Reset the CC2E Bit */
			CLR_BIT(TIM_4->CCER , TIM2_TO_TIM5_CCER_CC3E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_4->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_4->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_4->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3NP_BIT) ;

			/* Write to TIM CR2 */
			TIM_4->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_4->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_4->CCR3 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_4->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel3 */
			SET_BIT (TIM_4->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_4->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_4-> CCER , TIM2_TO_TIM5_CCER_CC3E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_4 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_4)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 4: Reset the CC2E Bit */
			CLR_BIT(TIM_4->CCER , TIM2_TO_TIM5_CCER_CC4E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_4->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_4->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_4->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC4P_BIT);

			/* Write to TIM CR2 */
			TIM_4->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_4->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_4->CCR4 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_4->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel4 */
			SET_BIT (TIM_4->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_4->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_4-> CCER , TIM2_TO_TIM5_CCER_CC4E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_4 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
	}
	else if (A_u8TimerSelected == TIM5_TYPE)
	{
		if (A_u8Channel == TIM_CHANNEL_1)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 1: Reset the CC1E Bit */
			CLR_BIT(TIM_5->CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Get the TIM CCER register value */
			L_u32TempCCMRX = TIM_5->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_5->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_5->CCMR1;

			/* Reset the Output Compare Mode Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT1) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT2) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT1) ;
			/* Select the Output Compare Mode1 */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC1P_BIT);

			/* Write to TIM CR2 */
			TIM_5->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_5->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_5->CCR1 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_5->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel1 */
			SET_BIT (TIM_5->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_5->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_5-> CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_5 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_2)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 2: Reset the CC2E Bit */
			CLR_BIT(TIM_5->CCER , TIM2_TO_TIM5_CCER_CC2E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_5->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_5->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_5->CCMR1;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT2);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2NP_BIT) ;

			/* Write to TIM CR2 */
			TIM_5->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_5->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_5->CCR2 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_5->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel2 */
			SET_BIT (TIM_5->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_5->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_5-> CCER , TIM2_TO_TIM5_CCER_CC2E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_5 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_3)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 3: Reset the CC2E Bit */
			CLR_BIT(TIM_5->CCER , TIM2_TO_TIM5_CCER_CC3E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_5->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_5->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_5->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3NP_BIT) ;

			/* Write to TIM CR2 */
			TIM_5->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_5->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_5->CCR3 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_5->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel3 */
			SET_BIT (TIM_5->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_5->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_5-> CCER , TIM2_TO_TIM5_CCER_CC3E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_5 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_4)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 4: Reset the CC2E Bit */
			CLR_BIT(TIM_5->CCER , TIM2_TO_TIM5_CCER_CC4E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_5->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_5->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_5->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC4P_BIT);

			/* Write to TIM CR2 */
			TIM_5->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_5->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_5->CCR4 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_5->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel4 */
			SET_BIT (TIM_5->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_5->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_5-> CCER , TIM2_TO_TIM5_CCER_CC4E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_5 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
	}
	else
	{
		// error type of A_u8TimerSelected
	}
}

void MTimerICU_voidInit (u8 A_u8TimerSelected  )
{
	switch(A_u8TimerSelected)
	{
	case TIM1_TYPE :
		break;
	case TIM2_TYPE :
		break;
	case TIM3_TYPE :
		/*DIER Register*/
		// Capture/Compare interrupt enable
		SET_BIT(TIM_3-> DIER ,1);

		/*CCMR1 Register*/

		SET_BIT(TIM_3 -> CCMR1 , 0);	// configure timer3 ch1 as input
		CLR_BIT(TIM_3 -> CCMR1 , 1);

		CLR_BIT(TIM_3 -> CCMR1 , 2);	// configure timer3 ch1 to capture at every edge detected
		CLR_BIT(TIM_3 -> CCMR1 , 3);


		CLR_BIT(TIM_3 -> CCMR1 , 6);
		CLR_BIT(TIM_3 -> CCMR1 , 7);

		/*CCER Register*/

		SET_BIT(TIM_3 -> CCER , 0);	// Capture Enabled


		SET_BIT(TIM_3 -> CCER , 1);	// Capture/Compare channel captures on both edges (rising & falling)
		SET_BIT(TIM_3 -> CCER , 3);

		/*set prescaler for timer 3 from configration file*/
		TIM_3->PSC=0;
		TIM_3->PSC=TIM3_PRESCALLER-1;

		/*set preload 0xffff*/
		TIM_3-> ARR = 65535;


		break;
	case TIM4_TYPE :
		break;
	case TIM5_TYPE :
		break;

	}
}

void MTimerICU_voidStartTimer(u8 A_u8TimerSelected)
{
	switch(A_u8TimerSelected)
	{
	case TIM2_TYPE:
		SET_BIT(TIM_2 -> CR1, TIM1_CR1_CEN_BIT); break;
	case TIM3_TYPE:
		SET_BIT(TIM_3 -> CR1, TIM1_CR1_CEN_BIT); break;
	case TIM4_TYPE:
		SET_BIT(TIM_4 -> CR1, TIM1_CR1_CEN_BIT); break;
	case TIM5_TYPE:
		SET_BIT(TIM_5 -> CR1, TIM1_CR1_CEN_BIT); break;

	default:                               break;
	}
}

void MTimer_voidClearCounterReg(u8 A_u8TimerSelected)
{
	switch(A_u8TimerSelected)
	{
	case TIM2_TYPE:
		TIM_2->CNT=0; break;
	case TIM3_TYPE:
		TIM_3->CNT=0; break;
	case TIM4_TYPE:
		TIM_4->CNT=0; break;
	case TIM5_TYPE:
		TIM_5->CNT=0; break;

	default:                               break;
	}
}

u32 MTimer_u32ReadCaptureReg(u8 A_u8TimerSelected , u8 A_u8Channel)
{
	u32 reading = 0;
	switch(A_u8TimerSelected)
	{
	case TIM2_TYPE:


		break;
	case TIM3_TYPE:
		switch(A_u8Channel)
		{
		case TIM_CHANNEL_1:
			reading = TIM_3 -> CCR1;
			break;
		case TIM_CHANNEL_2:
			reading = TIM_3 -> CCR2;
			break;
		case TIM_CHANNEL_3:
			reading = TIM_3 -> CCR3;
			break;
		case TIM_CHANNEL_4:
			reading = TIM_3 -> CCR4;
			break;
		}
		break;
		case TIM4_TYPE:
			switch(A_u8Channel)
			{
			case TIM_CHANNEL_1:
				reading = TIM_4 -> CCR1;
				break;
			case TIM_CHANNEL_2:
				reading = TIM_4 -> CCR2;
				break;
			case TIM_CHANNEL_3:
				reading = TIM_4 -> CCR3;
				break;
			case TIM_CHANNEL_4:
				reading = TIM_4 -> CCR4;
				break;
			}
			break;
			default:            break;
	}
	return reading;

}

void MTimer_voidDelayInit(u8 A_u8TimerSelected , u8 A_u8Channel)
{

	//MTimer_voidSetTimer_Channel(A_u8TimerSelected,A_u8Channel);


	switch(A_u8TimerSelected)
	{
	case TIM1_TYPE:
		//implemented soon as possible
		break;
	case TIM2_TYPE:
		//set frequency of timer to be 1 Mhz to get 1 sec easily
		TIM_2->PSC=TIM2_PRESCALLER-1;
		//set preloadvalue to get 1 sec
		TIM_2->ARR=TIM2_PRELOAD_VALUE;
		//set timer to generate interrupt at overflow / underflow only
		SET_BIT(TIM_2->CR1,TIM2_TO_TIM5_CR1_URS_BIT);
		//update interrupt enable
		SET_BIT(TIM_2->DIER,TIM2_TO_TIM5_DIER_UIE_BIT);
		//update generation
		SET_BIT(TIM_2->EGR,TIM2_TO_TIM5_EGR_UG_BIT);
		break;
	case TIM3_TYPE:
		//set frequency of timer to be 1 Mhz to get 1 sec easily
		TIM_3->PSC=TIM3_PRESCALLER-1;
		//set preloadvalue to get 1 sec
		TIM_3->ARR=TIM3_PRELOAD_VALUE;
		//set timer to generate interrupt at overflow / underflow only
		SET_BIT(TIM_3->CR1,TIM2_TO_TIM5_CR1_URS_BIT);
		//update interrupt enable
		SET_BIT(TIM_3->DIER,TIM2_TO_TIM5_DIER_UIE_BIT);
		//update generation
		SET_BIT(TIM_3->EGR,TIM2_TO_TIM5_EGR_UG_BIT);
		break;
	case TIM4_TYPE:
		MRCC_vEnableClock(RCC_APB1, 2);
		//set frequency of timer to be 1 Mhz to get 1 sec easily
		TIM_4->PSC=TIM4_PRESCALLER-1;
		//set preloadvalue to get 1 sec
		TIM_4->ARR=TIM4_PRELOAD_VALUE;
		//set timer to generate interrupt at overflow / underflow only
		SET_BIT(TIM_4->CR1,TIM2_TO_TIM5_CR1_URS_BIT);
		//update interrupt enable
		SET_BIT(TIM_4->DIER,TIM2_TO_TIM5_DIER_UIE_BIT);
		//update generation
		SET_BIT(TIM_4->EGR,TIM2_TO_TIM5_EGR_UG_BIT);
		break;
	case TIM5_TYPE:
		MRCC_vEnableClock(RCC_APB1,RCC_EN_TIM5);
		//set frequency of timer to be 1 Mhz to get 1 sec easily
		TIM_5->PSC=TIM5_PRESCALLER-1;
		//set preloadvalue to get 1 sec
		TIM_5->ARR=TIM5_PRELOAD_VALUE;
		//set timer to generate interrupt at overflow / underflow only
		SET_BIT(TIM_5->CR1,TIM2_TO_TIM5_CR1_URS_BIT);
		//update interrupt enable
		SET_BIT(TIM_5->DIER,TIM2_TO_TIM5_DIER_UIE_BIT);
		//update generation
		SET_BIT(TIM_5->EGR,TIM2_TO_TIM5_EGR_UG_BIT);
		break;
	}
}

void MTimer_Delay_ms(u8 A_u8TimerSelected , u64 ms )
{
	u64 temp=0;
	switch(A_u8TimerSelected)
	{
	case TIM1_TYPE:
		break;
	case TIM2_TYPE:
		TIM_2->CR1|=TIM2_TO_TIM5_CR1_CEN_BIT;
		Ticks=0;
		while(Ticks<(ms*1000));
		TIM_2->CR1&=~TIM2_TO_TIM5_CR1_CEN_BIT;
		break;
	case TIM3_TYPE:
		TIM_3->CR1|=TIM2_TO_TIM5_CR1_CEN_BIT;
		Ticks=0;
		while(Ticks<(ms*1000));
		TIM_3->CR1&=~TIM2_TO_TIM5_CR1_CEN_BIT;
		break;
	case TIM4_TYPE:
		TIM_4->CR1|=TIM2_TO_TIM5_CR1_CEN_BIT;
		Ticks=0;
		while(Ticks<(/*ms**/1));
		TIM_4->CR1&=~TIM2_TO_TIM5_CR1_CEN_BIT;
		break;
	case TIM5_TYPE:
		Ticks=0;
		SET_BIT(TIM_5->CR1,TIM2_TO_TIM5_CR1_CEN_BIT);
		while((Ticks<(ms*1000)));
		TIM_5->CR1&=~TIM2_TO_TIM5_CR1_CEN_BIT;
		break;
	}
}

void MTimer_Delay_us(u8 A_u8TimerSelected , u64 us)
{
	switch(A_u8TimerSelected)
	{
	case TIM1_TYPE:
		break;
	case TIM2_TYPE:
		TIM_2->CR1|=TIM2_TO_TIM5_CR1_CEN_BIT;
		Ticks=0;
		while(Ticks<us);
		TIM_2->CR1&=~TIM2_TO_TIM5_CR1_CEN_BIT;
		break;
	case TIM3_TYPE:
		TIM_3->CR1|=TIM2_TO_TIM5_CR1_CEN_BIT;
		Ticks=0;
		while(Ticks<us);
		TIM_3->CR1&=~TIM2_TO_TIM5_CR1_CEN_BIT;
		break;
	case TIM4_TYPE:
		TIM_4->CR1|=TIM2_TO_TIM5_CR1_CEN_BIT;
		Ticks=0;
		while(Ticks<us);
		TIM_4->CR1&=~TIM2_TO_TIM5_CR1_CEN_BIT;
		break;
	case TIM5_TYPE:
		TIM_5->CR1|=TIM2_TO_TIM5_CR1_CEN_BIT;
		Ticks=0;
		while(Ticks<us);
		TIM_5->CR1&=~TIM2_TO_TIM5_CR1_CEN_BIT;
		break;
	}
}


u32 MTimer_u32GetElapsedTime (u8 A_u8TimerSelected )
{
	u32 ElapsedTime ;
	switch(A_u8TimerSelected)
	{
	case TIM1_TYPE:
		break;
	case TIM2_TYPE:
		break;
	case TIM3_TYPE:
		break;
	case TIM4_TYPE:
		break;
	case TIM5_TYPE:
		if(Ticks==0)
		{
			ElapsedTime=TIM_5->CNT-TIM_5->ARR;
		}
		else
		{
			ElapsedTime=TIM_5->CNT*Ticks;
		}
		break;
	}
	return ElapsedTime;
}

/*
u32 MTimer_u32GetRemainingTime (u8 A_u8TimerSelected )
{
	u32 RemainingTime ;
}
*/

void MTimer_voidSetIntervalSingle(u8 A_u8TimerSelected ,u32 ms , void (*CallBackFunc) (void))
{
	//0- SET CALLBACK FUNCTION
	MTimer_CallBackPTR = CallBackFunc;
	//Timer Number Chosen
	switch(A_u8TimerSelected)
	{
	case TIM1_TYPE:
		//Handled Later
		break;
	case TIM2_TYPE:
		TIM_2->CR1|=TIM2_TO_TIM5_CR1_CEN_BIT;
		Ticks=0;
		while(Ticks<(ms*1000))
		{
			if(Ticks==(ms*1000)-1)
			{
				CallBackFlag=1;
			}
		}
		TIM_2->CR1&=~TIM2_TO_TIM5_CR1_CEN_BIT;
		break;
	case TIM3_TYPE:
		TIM_3->CR1|=TIM2_TO_TIM5_CR1_CEN_BIT;
		Ticks=0;
		while(Ticks<(ms*1000-1))
		{
			if(Ticks==(ms*1000)-1)
			{
				CallBackFlag=1;
			}
		}
		TIM_3->CR1&=~TIM2_TO_TIM5_CR1_CEN_BIT;
		break;
	case TIM4_TYPE:
		TIM_4->CR1|=TIM2_TO_TIM5_CR1_CEN_BIT;
		Ticks=0;
		while(Ticks<(ms*1000))
		{
			if(Ticks==(ms*1000)-1)
			{
				CallBackFlag=1;
			}
		}
		TIM_4->CR1&=~TIM2_TO_TIM5_CR1_CEN_BIT;
		break;
	case TIM5_TYPE:
		TIM_5->CR1|=TIM2_TO_TIM5_CR1_CEN_BIT;
		Ticks=0;
		while(Ticks<(ms*1000))
		{
			if(Ticks==(ms*1000)-1)
			{
				CallBackFlag=1;
			}
		}
		TIM_5->CR1&=~TIM2_TO_TIM5_CR1_CEN_BIT;
		break;
	}
}

void MTimer_vSetCallBack(void (*copy_ptr)(void))
{
	MTimer_CallBackPTR = copy_ptr;
}


void TIM5_IRQHandler(void)
{
	Ticks++;
	/*if(MTimer_CallBackPTR != NULL)
	{
		if (CallBackFlag==1)
		{
		(*MTimer_CallBackPTR)();
		CallBackFlag=0;
		}
	}*/
	TIM_5->SR &=~TIM2_TO_TIM5_SR_UIF_BIT;
}


void delay(u16 ms)
{
	MRCC_vEnableClock(RCC_APB1,RCC_EN_TIM4);
	TIM_4->PSC=(8000-1); //8 000 000 Hz / 8 000 = 1 000 Hz (1 ms)
	TIM_4->ARR=(ms-1);   // desired delay
	//TIM_4->CR1|=TIM2_TO_TIM5_CR1_CEN_BIT;
	SET_BIT(TIM_4->CR1,TIM2_TO_TIM5_CR1_CEN_BIT);
	while(MGPIO_u8GetPinValue(TIM_4->SR,TIM2_TO_TIM5_SR_UIF_BIT)!=1); //wait UIF to be set
	TIM_4->SR&=~TIM2_TO_TIM5_SR_UIF_BIT; //reset UIF
	TIM_4->CR1&=~TIM2_TO_TIM5_CR1_CEN_BIT; // Disable the timer
}
