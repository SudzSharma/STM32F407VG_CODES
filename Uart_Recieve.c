#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "misc.h"

USART_InitTypeDef usart;
GPIO_InitTypeDef gpio;
NVIC_InitTypeDef nvic;

void gpio_init(void);

volatile uint16_t i;

void USART1_IRQHandler(void)
{

	while(USART_GetITStatus(USART1, USART_IT_RXNE) == RESET);
	 	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==RESET);
		i = USART_ReceiveData(USART1);
}

int main(void)
{
	gpio_init();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	usart.USART_BaudRate = 9600;
	usart.USART_WordLength = USART_WordLength_8b;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_Init(USART1, &usart); // USART configuration

	USART_Cmd(USART1, ENABLE); // Enable USART

	nvic.NVIC_IRQChannel = USART1_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&nvic);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	GPIO_SetBits(GPIOD, GPIO_Pin_12);





	while(1)
    {
		if(i=='a')
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			i=0;
		}
    }
}

void gpio_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	gpio.GPIO_Pin = GPIO_Pin_12;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &gpio);



	gpio.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	gpio.GPIO_Mode = GPIO_Mode_AF;

	GPIO_Init(GPIOB, &gpio);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);//Tx
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);//Rx
}
