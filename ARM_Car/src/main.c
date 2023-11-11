#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/EXTI/EXTI_interface.h"
#include "MCAL/GPIO/GPIO_int.h"
#include "MCAL/RCC/RCC_int.h"
#include "MCAL/UART/UART_int.h"
#include "MCAL/NVIC/NVIC_int.h"
#include "HAL/IR/IR_interface.h"
#include "MCAL/SYSTICK/Systick_interface.h"
#include "MCAL/TIMER/Timer_init.h"
#include "HAL/Motor_H_Bridge/Motor_H_Bridge_Interface.h"
#include "HAL/Ultrasonic/Ultrasonic_interface.h"

volatile u32 Distance;
extern  volatile u8 Data ;
extern USART_InitType uart2_cfg ;
extern USART_InitType uart1_cfg ;
u8 Current_state;
u8 previous_state;
u8 idle_flag=0;
void IR_APP(void);
double mapPWMToSpeed(int pwm);
void send_to_GUI(u8 PWM);

GPIO_cfg_t LED ;
GPIO_cfg_t Buzzer;
void main(void)
{
	/*1- system clock ...MHZ from HSI */
	MRCC_vInit();
	/*2- Enable GPIO peripheral clock for port B , A */
	MRCC_vEnableClock(RCC_AHB1,RCC_EN_GPIOB);
	MRCC_vEnableClock(RCC_AHB1,RCC_EN_GPIOA);
	MRCC_vEnableClock(RCC_APB1,RCC_EN_TIM3);
	MRCC_vEnableClock(RCC_APB1,RCC_EN_TIM2);
	MRCC_vEnableClock(RCC_APB1,RCC_EN_UART2);
	MRCC_vEnableClock(RCC_APB1,RCC_EN_UART1);
	MRCC_vEnableClock(RCC_APB2,RCC_EN_SYSCFG);
	/*3- Enable Systick peripheral clock */
	MSTK_vInit();
	/*4-Enable Pin Configuration*/
	GPIO_cfg_t ECHO_PA6 = {.port = GPIO_PORTA ,.pin =GPIO_PIN6 , .mode=GPIO_MODE_ALTFUN , .A_u8Altfun=2};
	MGPIO_vInit(&ECHO_PA6);
	GPIO_cfg_t TRIG_PA4 = {.port = GPIO_PORTA ,.pin =GPIO_PIN4 , .mode=GPIO_MODE_OUTPUT };
	MGPIO_vInit(&TRIG_PA4);
	GPIO_cfg_t TX={.port=GPIO_PORTA,.pin=GPIO_PIN2,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun=7};
	MGPIO_vInit(&TX);
	GPIO_cfg_t RX={.port=GPIO_PORTA,.pin=GPIO_PIN3,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun=7};
	MGPIO_vInit(&RX);
	GPIO_cfg_t TX_1={.port=GPIO_PORTA,.pin=GPIO_PIN9,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun=7};
	MGPIO_vInit(&TX_1);
	GPIO_cfg_t RX_1={.port=GPIO_PORTA,.pin=GPIO_PIN10,.mode=GPIO_MODE_ALTFUN,.out_type=GPIO_OUTPUTTYPE_PUSHPULL,.speed=GPIO_OUTSPEED_LOW,.A_u8Altfun=7};
	MGPIO_vInit(&RX_1);
	GPIO_cfg_t LED = { .port =GPIO_PORTA , .pin =GPIO_PIN8 , .mode = GPIO_MODE_OUTPUT , .speed = GPIO_OUTSPEED_LOW ,.out_type = GPIO_OUTPUTTYPE_PUSHPULL };
	MGPIO_vInit(&LED);
	GPIO_cfg_t Buzzer = { .port =GPIO_PORTA , .pin =GPIO_PIN1 , .mode = GPIO_MODE_OUTPUT , .speed = GPIO_OUTSPEED_LOW ,.out_type = GPIO_OUTPUTTYPE_PUSHPULL };
	MGPIO_vInit(&Buzzer);
	GPIO_cfg_t IR = { .port =GPIO_PORTA , .pin =GPIO_PIN0 , .mode = GPIO_MODE_INPUT , .speed = GPIO_OUTSPEED_LOW ,.input_type = GPIO_INPUTTYPE_PU };
	MGPIO_vInit(&IR);
	/*5-Enable ICU Capture unit*/
	MNVIC_vSetPriority(29, 1 ,0);
	MNVIC_vSetPriority(6 , 0 ,0);
	/*7-IR Initialization*/
	MEXTI_vSetCallBack(EXTI_LINE0,Read_time);
	MEXTI_vEnableLine(EXTI_LINE0,EXTI_FAILING);
	MNVIC_vEnableInteruptPeripheral(6);
	/*************************************************/
	MTimerICU_voidInit(TIM3_TYPE);
	MTimerICU_voidStartTimer(TIM3_TYPE);
	MNVIC_vEnableInteruptPeripheral(29);

	/*6-Enable USART Peripheral*/
	uart2_cfg.BaudRate = 9600 ;
	MUSART_vInit(&uart2_cfg,USART2);
	MUSART_vEnable(USART2);

	/*7-Enable USART Peripheral*/
	uart1_cfg.BaudRate = 9600 ;
	MUSART_vInit(&uart1_cfg,USART1);
	MUSART_vEnable(USART1);


	/*8-TIMER 2 INitialization*/
	//Read_data(IR_APP);
	MTimer_voidInit(TIM2_TYPE,TIM_CHANNEL_1);
	MTimer_voidInit(TIM2_TYPE,TIM_CHANNEL_3);
	/*9-Motor Initialization*/
	H_Motor_H_Bridge_voidInit();
	H_Motor_H_Bridge_voidStop();
	/*10-Delay...............*/
	//MTimer_voidDelayInit(TIM4_TYPE,TIM_CHANNEL_1);
	//MNVIC_vEnableInteruptPeripheral(50);
	/*11-Start Timer ICU*/

	MTimerICU_voidStartTimer(TIM3_TYPE);

	while(1)
	{

		Ultrasonic_voidTrigger();

		for (u32 i = 0; i < 40 * 300; i++)
		{
			asm("NOP");
		}
		if(Distance>35 && idle_flag==1)
		{
			MGPIO_vSetPinValue(Buzzer.port,Buzzer.pin,GPIO_LOW);
			MGPIO_vSetPinValue(LED.port,LED.pin,GPIO_LOW);

			H_Motor_H_Bridge_voidForward();
			MUSART_vTransmitByteSynch(USART2,'F');


		}
		if ( ( Distance>5 && Distance<=35 ) && idle_flag==1 )
		{

			MGPIO_vSetPinValue(LED.port,LED.pin,GPIO_HIGH);
			H_Motor_H_Bridge_voidForwardLowSpeed();


		}
		if( ( Distance<=5 ) && idle_flag==1 )
		{
			H_Motor_H_Bridge_voidStop();
			MUSART_vTransmitByteSynch(USART2,'S');
			MGPIO_vSetPinValue(Buzzer.port,Buzzer.pin,GPIO_HIGH);
			MGPIO_vSetPinValue(LED.port,LED.pin,GPIO_HIGH);
		}
		if ( ( Distance>=10 ) && idle_flag==2 )
		{

			MGPIO_vSetPinValue(LED.port,LED.pin,GPIO_LOW);
			MGPIO_vSetPinValue(Buzzer.port,Buzzer.pin,GPIO_LOW);
			H_Motor_H_Bridge_voidForward();


		}
		if( ( Distance<10 ) && idle_flag==2 )
		{
			H_Motor_H_Bridge_voidStop();
			MUSART_vTransmitByteSynch(USART2,'S');
			MGPIO_vSetPinValue(Buzzer.port,Buzzer.pin,GPIO_HIGH);
			MGPIO_vSetPinValue(LED.port,LED.pin,GPIO_HIGH);
		}
		if(idle_flag==3 && Distance<15 )
		{
			H_Motor_H_Bridge_voidForwardLowSpeed();
			MUSART_vTransmitByteSynch(USART2,'k');
		}
		if(idle_flag==3 && Distance>=15)
		{
			H_Motor_H_Bridge_voidForward();
			MUSART_vTransmitByteSynch(USART2,'F');
		}
		if(idle_flag==4)
		{
			for (u8 counter= 9 ; counter>0 ; counter--)
			{
				MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_3 ,counter);
				MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_1 ,counter);
				MUSART_vTransmitNumSynch(USART1,counter);
				//send_to_GUI(counter);
				for (u32 i = 0; i < 2000 * 300; i++)
				{
					asm("NOP");
				}
			}
			for (u8 counter= 0 ; counter<9 ; counter++)
			{
				MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_3 ,counter);
				MTimer_voidPWM(TIM2_TYPE , TIM_CHANNEL_1 ,counter);
				MUSART_vTransmitNumSynch(USART1,counter);
				//send_to_GUI(counter);
				for (u32 i = 0; i < 2000 * 300; i++)
				{
					asm("NOP");
				}
			}
		}
	}
}


void IR_APP(void)
{

	if(Data == NUM_2 )  //Ultrasonic and two mode of speed
	{
		//Backward
		//H_Motor_H_Bridge_voidStop();
		H_Motor_H_Bridge_voidForward();
		MUSART_vTransmitByteSynch(USART2,'F');
		idle_flag=1;
		Data=0;

	}
	if(Data == NUM_0)
	{
		//stop
		H_Motor_H_Bridge_voidStop();
		MUSART_vTransmitByteSynch(USART2,'S');
		Data=0;
	}

	if(Data == NUM_7) //Mode V2V
	{
		//Forward
		H_Motor_H_Bridge_voidForward();
		MUSART_vTransmitByteSynch(USART2,'F');
		for (u32 i = 0; i < 5000 * 300; i++)
		{
			asm("NOP");
		}
		//Left
		H_Motor_H_Bridge_voidLeft();
		MUSART_vTransmitByteSynch(USART2,'L');
		for (u32 i = 0; i < 2500 * 300; i++)
		{
			asm("NOP");
		}
		H_Motor_H_Bridge_voidForward();
		MUSART_vTransmitByteSynch(USART2,'F');
		for (u32 i = 0; i < 3000 * 300; i++)
		{
			asm("NOP");
		}
		//Right
		H_Motor_H_Bridge_voidRight();
		MUSART_vTransmitByteSynch(USART2,'R');
		for (u32 i = 0; i < 2500 * 300; i++)
		{
			asm("NOP");
		}
		H_Motor_H_Bridge_voidForward();
		MUSART_vTransmitByteSynch(USART2,'F');
		for (u32 i = 0; i < 3000 * 300; i++)
		{
			asm("NOP");
		}
		//forward
		H_Motor_H_Bridge_voidForward();
		MUSART_vTransmitByteSynch(USART2,'F');
		for (u32 i = 0; i < 3000 * 300; i++)
		{
			asm("NOP");
		}
		//Right
		H_Motor_H_Bridge_voidRight();
		MUSART_vTransmitByteSynch(USART2,'R');
		for (u32 i = 0; i < 2500 * 300; i++)
		{
			asm("NOP");
		}
		H_Motor_H_Bridge_voidForward();
		MUSART_vTransmitByteSynch(USART2,'F');
		for (u32 i = 0; i < 3000 * 300; i++)
		{
			asm("NOP");
		}
		//Left
		H_Motor_H_Bridge_voidLeft();
		MUSART_vTransmitByteSynch(USART2,'L');
		for (u32 i = 0; i < 2500 * 300; i++)
		{
			asm("NOP");
		}
		H_Motor_H_Bridge_voidForward();
		MUSART_vTransmitByteSynch(USART2,'F');
		for (u32 i = 0; i < 3000 * 300; i++)
		{
			asm("NOP");
		}
		//forward
		H_Motor_H_Bridge_voidForward();
		MUSART_vTransmitByteSynch(USART2,'F');
		for (u32 i = 0; i < 5000 * 300; i++)
		{
			asm("NOP");
		}
		//stop
		H_Motor_H_Bridge_voidStop();
		MUSART_vTransmitByteSynch(USART2,'S');

		Data=0;
	}
	if(Data == NUM_9)	//Mode Emergency Braking
	{
		//stop
		H_Motor_H_Bridge_voidStop();
		MUSART_vTransmitByteSynch(USART2,'S');
		Data=0;
		//Forward
		H_Motor_H_Bridge_voidForward();
		MUSART_vTransmitByteSynch(USART2,'F');
		idle_flag=2;
	}
	if(Data==NUM_3)	//Mode AVR infront of ARM car V2V Ada[tive cursie control
	{
		idle_flag=3;
		H_Motor_H_Bridge_voidStop();
		MUSART_vTransmitByteSynch(USART2,'S');
		Data=0;
		//Forward
		H_Motor_H_Bridge_voidForward();
		MUSART_vTransmitByteSynch(USART2,'F');
	}
	if(Data==NUM_5)	//Mode ARM inrement and decrement of speed and GUI
	{
		idle_flag=4;
		//stop
		H_Motor_H_Bridge_voidStop();
		//Forward
		H_Motor_H_Bridge_voidForward();
		Data=0;
	}
}


void send_to_GUI(u8 PWM)
{

	u64 GUI_Speed;

	GUI_Speed=mapPWMToSpeed(PWM);

	MUSART_vTransmitNumSynch(USART1,GUI_Speed);

}


double mapPWMToSpeed(int pwm) {
	// Determine the mapping constant (k) experimentally
	double k = 50.0 / 128.0;

	// Calculate the speed based on the PWM value
	double speed = (1/k) * pwm;

	// Make sure the speed is within the valid range (0 to 100)
	if (speed < 0.0) {
		speed = 0.0;
	} else if (speed > 100.0) {
		speed = 100.0;
	}

	return speed;
}


