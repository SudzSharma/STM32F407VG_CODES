#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"

int cnt=0;
int main(void)
{
	GPIO_InitTypeDef A;
	EXTI_InitTypeDef ext1;
	GPIO_InitTypeDef B;
	GPIO_InitTypeDef D;
	NVIC_InitTypeDef nvic;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

		 B.GPIO_Pin=GPIO_Pin_12;
		 B.GPIO_OType=GPIO_OType_PP;
		 B.GPIO_Mode=GPIO_Mode_OUT;
		 B.GPIO_PuPd=GPIO_PuPd_NOPULL;
		 B.GPIO_Speed=GPIO_Speed_100MHz;

		 GPIO_Init(GPIOD,&B);

		      D.GPIO_Pin=GPIO_Pin_15;
				 D.GPIO_OType=GPIO_OType_PP;
				 D.GPIO_Mode=GPIO_Mode_OUT;
				 D.GPIO_PuPd=GPIO_PuPd_NOPULL;
				 D.GPIO_Speed=GPIO_Speed_100MHz;

				 GPIO_Init(GPIOD,&D);




	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	 A.GPIO_Pin=GPIO_Pin_0;
	 A.GPIO_OType=GPIO_OType_PP;
	 A.GPIO_Mode=GPIO_Mode_IN;
	 A.GPIO_PuPd=GPIO_PuPd_DOWN;
	 A.GPIO_Speed=GPIO_Speed_100MHz;

	 GPIO_Init(GPIOA,&A);

	 SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);

	ext1.EXTI_Mode=EXTI_Mode_Interrupt;
	ext1.EXTI_Line=EXTI_Line0;
	ext1.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//Falling Edge Interrupt Enable..
	ext1.EXTI_LineCmd=ENABLE;

	EXTI_Init(&ext1);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

nvic.NVIC_IRQChannel=EXTI0_IRQn;
nvic.NVIC_IRQChannelCmd=ENABLE;
nvic.NVIC_IRQChannelPreemptionPriority=1;
nvic.NVIC_IRQChannelSubPriority=1;

NVIC_Init(&nvic);

GPIO_SetBits(GPIOA,GPIO_Pin_0);


 while(1)
    {

    }
}

void EXTI0_IRQHandler(void)//In startup_stm32f4xx.c
{

	GPIO_ToggleBits(GPIOD,GPIO_Pin_15);

	EXTI_ClearITPendingBit(EXTI_Line0);
}



