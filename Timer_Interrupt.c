#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

int main(void)
{
	GPIO_InitTypeDef B;
	GPIO_InitTypeDef C;
	TIM_TimeBaseInitTypeDef tim;
	NVIC_InitTypeDef nvic;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);



	B.GPIO_Pin=GPIO_Pin_12;
	B.GPIO_Mode=GPIO_Mode_OUT;
	B.GPIO_OType=GPIO_OType_PP;
	B.GPIO_PuPd=GPIO_PuPd_NOPULL;
	B.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&B);

	C.GPIO_Pin=GPIO_Pin_15;
	C.GPIO_Mode=GPIO_Mode_OUT;
	C.GPIO_OType=GPIO_OType_PP;
	C.GPIO_PuPd=GPIO_PuPd_NOPULL;
	C.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&C);


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//32bit timer

	tim.TIM_ClockDivision=TIM_CKD_DIV1;
	tim.TIM_CounterMode=TIM_CounterMode_Up;
	tim.TIM_Period=1000000-1;
	tim.TIM_Prescaler=41;

	TIM_TimeBaseInit(TIM2,&tim);

	TIM_Cmd(TIM2,ENABLE);

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	 nvic.NVIC_IRQChannel=TIM2_IRQn;
	 nvic.NVIC_IRQChannelCmd=ENABLE;
	 nvic.NVIC_IRQChannelPreemptionPriority=1;;
	 nvic.NVIC_IRQChannelSubPriority=1;

	 NVIC_Init(&nvic);

	 TIM_SetCounter(TIM2,0);


	while(1)
	{
     GPIO_SetBits(GPIOD,GPIO_Pin_12);
	}

}


	void TIM2_IRQHandler(void)
	{
		//If doesnot Works Give The Condition Check For Timer Update Event Interrupt Status
		if(TIM_GetITStatus(TIM2,TIM_IT_Update))
		{
	GPIO_ToggleBits(GPIOD,GPIO_Pin_15);
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		}

	}

