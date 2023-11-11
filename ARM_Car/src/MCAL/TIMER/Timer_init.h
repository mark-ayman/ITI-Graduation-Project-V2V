

#ifndef MCAL_TIMER_TIMER_INIT_H_
#define MCAL_TIMER_TIMER_INIT_H_

/*
 * define A_u8TimerSelected
 */
#define TIM1_TYPE     1
#define TIM2_TYPE     2
#define TIM3_TYPE     3
#define TIM4_TYPE     4
#define TIM5_TYPE     5

/*
 * define A_u8Channel
 *
 * note that for TIM1 to TIM5 there are 4 channels
 */
#define TIM_CHANNEL_1  1
#define TIM_CHANNEL_2  2
#define TIM_CHANNEL_3  3
#define TIM_CHANNEL_4  4

/* define Trigger edges */
#define TIM_EDGE_RISE  0
#define TIM_EDGE_FALL  1
#define TIM_EDGE_BOTH  2

/* Define Incapture Mode  */
#define TIM_IC_Output	0
#define TIM_IC_T1		1
#define TIM_IC_T2		2
#define TIM_IC_TRC		3


void MTimer_voidInit (u8 A_u8TimerSelected , u8 A_u8Channel ) ;

void MTimer_voidPWM (u8 A_u8TimerSelected , u8 A_u8Channel , u16 A_u16CompareValue) ;

void MTimerICU_voidInit (u8 A_u8TimerSelected );

void MTimerICU_voidSetTrigEdge (u8 A_u8TimerICUEdge );

void MTimerICU_voidStartTimer(u8 A_u8TimerSelected);

void MTimer_voidClearCounterReg(u8 A_u8TimerSelected);

u32 MTimer_u32ReadCaptureReg(u8 A_u8TimerSelected , u8 A_u8Channel);

void MTimer_voidDelayInit(u8 A_u8TimerSelected , u8 A_u8Channel);

void MTimer_Delay_us(u8 A_u8TimerSelected , u64 us);

void MTimer_Delay_ms(u8 A_u8TimerSelected , u64 ms);

void MTimer_vSetCallBack(void (*copy_ptr)(void));

void MTimer_voidSetIntervalSingle(u8 A_u8TimerSelected ,u32 ms , void (*CallBackFunc) (void));

void delay(u16 ms);

void H_Motor_H_Bridge_voidForwardLowSpeed();

void H_Motor_H_Bridge_voidForwardHighSpeed();

#endif /* MCAL_TIMER_TIMER_INIT_H_ */


