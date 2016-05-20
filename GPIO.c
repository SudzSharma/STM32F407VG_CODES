#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"


int main(void)
{
	int i=0;
	GPIO_InitTypeDef GPIO_Initial;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);//Enables the Ahb1 Peripheral clock For GPIOA.Used For Register Read Or write Access.If Not Enabled After Reset it will stop.
	//GPIO_DeInit(GPIOD);//Deintializes The Alternate Functions OF the Pin And Sets The Pins To Default input and floating


	GPIO_Initial.GPIO_Pin=GPIO_Pin_15;//|GPIO_Pin_13|GPIO_Pin_14;//Setting The GPIO pin As 1,2,3.
	GPIO_Initial.GPIO_Mode=GPIO_Mode_OUT;//Setting The GPIO Mode as OUTPut.
	GPIO_Initial.GPIO_Speed=GPIO_Speed_25MHz;
	GPIO_Initial.GPIO_OType=GPIO_OType_PP ;//open drain or push pull mode.Selected Push Pull because In It Transistors
	//Are Connected to Both High and Low and One Operates at a Time.
	GPIO_Initial.GPIO_PuPd=GPIO_PuPd_NOPULL;//No Pull-Neither Pull Up Or Pull Down.

	GPIO_Init(GPIOD,&GPIO_Initial);//Initialising The GPIO POrt A PIN 1 As output.

    while(1)
    {
    	GPIO_SetBits(GPIOD,GPIO_Pin_15);
/*
    	GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
        for(i=0;i<20000;i++);
    	GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
    	for(i=0;i<20000;i++);
    	GPIO_ToggleBits(GPIOD,GPIO_Pin_14);
    	for(i=0;i<20000;i++);
    	*/
    }
}
