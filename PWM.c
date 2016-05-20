#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"

GPIO_InitTypeDef X,Y;
TIM_TimeBaseInitTypeDef Timer_4;
TIM_OCInitTypeDef Timer_OUT;

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
    X.GPIO_Pin=GPIO_Pin_12;
	X.GPIO_Mode=GPIO_Mode_AF;
	X.GPIO_OType=GPIO_OType_PP;
	X.GPIO_PuPd=GPIO_PuPd_NOPULL;
	X.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&X);


	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);

    Y.GPIO_Pin=GPIO_Pin_15;
	Y.GPIO_Mode=GPIO_Mode_OUT;
	Y.GPIO_OType=GPIO_OType_PP;
	Y.GPIO_PuPd=GPIO_PuPd_NOPULL;
	Y.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&Y);



	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);



	Timer_4.TIM_ClockDivision=TIM_CKD_DIV1;//No Clock Division.
	Timer_4.TIM_CounterMode=TIM_CounterMode_Up;//Upcounting Mode
	Timer_4.TIM_Period=2000;//The Top Value That is loaded to the Auto reload register.//the default value.
	Timer_4.TIM_Prescaler=42;//Prescaler is 16 bit.

	Timer_4.TIM_RepetitionCounter=0;// For Timer 1 and 8.

    TIM_TimeBaseInit(TIM4,&Timer_4);



    Timer_OUT.TIM_OCMode=TIM_OCMode_PWM1;//Set on Compare Match pwm2-means clear on compare match.
    Timer_OUT.TIM_OCPolarity=TIM_OCPolarity_High;
    Timer_OUT.TIM_OutputState=TIM_OutputState_Enable;
    Timer_OUT.TIM_Pulse=0;


    TIM_OC1Init(TIM4,&Timer_OUT);

    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);//enable the corresponding preload register by setting the
    //OCxPE bit in the TIMx_CCMRx register

    TIM_ARRPreloadConfig(TIM4,ENABLE);//setting the ARPE bit in the TIMx_CR1 register.


    TIM_Cmd(TIM4,ENABLE);//Starting the clock



    TIM_SetCounter(TIM4,0);

    int i,j;
    while(1)
    {

//GPIO_SetBits(GPIOD,GPIO_Pin_15);

for(i=0;i<2000;i++)
{
  //  Timer_OUT.TIM_Pulse=i;
	 TIM4->CCR1=i;
    for(j=0;j<2000;j++);
}


    }
}
