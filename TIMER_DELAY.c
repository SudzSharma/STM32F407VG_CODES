#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stdio.h"

int main(void)
{
	//int i=0;
	TIM_TimeBaseInitTypeDef Timer_5;

	//TIM_OCInitTypeDef Timer_5_OC;

	GPIO_InitTypeDef GPIO_Initial,X;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);//Enables the Ahb2 Peripheral clock For GPIOA.Used For Register Read Or write Access.If Not Enabled After Reset it will stop.
	//GPIO_DeInit(GPIOA);//Deintializes The Alternate Functions OF the Pin And Sets The Pins To Default input and floating


	X.GPIO_Pin=GPIO_Pin_14;//Setting The GPIO pin As 1,2,3.
		X.GPIO_Mode=GPIO_Mode_OUT;//Setting The GPIO Mode as OUTPut.
		X.GPIO_Speed=GPIO_Speed_25MHz;
		X.GPIO_OType=GPIO_OType_PP ;//open drain or push pull mode.Selected Push Pull because In It Transistors
		//Are Connected to Both High and Low and One Operates at a Time.
		X.GPIO_PuPd=GPIO_PuPd_NOPULL;//No Pull-Neither Pull Up Or Pull Down.

		GPIO_Init(GPIOD,&X);//Initialising The GPIO POrt A PIN 1 As output.




/*

	GPIO_Initial.GPIO_Pin=GPIO_Pin_12;//Setting The GPIO pin As 1,2,3.
	GPIO_Initial.GPIO_Mode=GPIO_Mode_OUT;//Setting The GPIO Mode as OUTPut.
	GPIO_Initial.GPIO_Speed=GPIO_Speed_25MHz;
	GPIO_Initial.GPIO_OType=GPIO_OType_PP ;//open drain or push pull mode.Selected Push Pull because In It Transistors
	//Are Connected to Both High and Low and One Operates at a Time.
	GPIO_Initial.GPIO_PuPd=GPIO_PuPd_NOPULL;//No Pull-Neither Pull Up Or Pull Down.

	GPIO_Init(GPIOD,&GPIO_Initial);//Initialising The GPIO POrt A PIN 1 As output.


	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM5);//Alternate Function TIMER 5 for GPIOA pin1.

*/


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);



	Timer_5.TIM_ClockDivision=TIM_CKD_DIV1;//No Clock Division.
	Timer_5.TIM_CounterMode=TIM_CounterMode_Up;//Upcounting Mode
	Timer_5.TIM_Period=200000;//The Top Value That is loaded to the Auto reload register.//the default value.
	Timer_5.TIM_Prescaler=84;//Prescaler is 16 bit.

	Timer_5.TIM_RepetitionCounter=0;// For Timer 1 and 8.


	TIM_TimeBaseInit(TIM5,&Timer_5);



TIM_Cmd(TIM5,ENABLE);


//uint32_t timerc=TIM4->CNT;


TIM_SetCounter(TIM5,0);


    while(1)
    {

    if(TIM5->CNT<100000)
    {

     GPIO_SetBits(GPIOD,GPIO_Pin_14);

    }
    else
    {
    	GPIO_ResetBits(GPIOD,GPIO_Pin_14);

    }

    }


}
