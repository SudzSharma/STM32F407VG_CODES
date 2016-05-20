#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

int main(void)
{
	GPIO_InitTypeDef A,B,C;
	USART_InitTypeDef usart;
	uint16_t data;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	A.GPIO_Mode=GPIO_Mode_AF;
	A.GPIO_OType=GPIO_OType_PP;
	A.GPIO_Pin=GPIO_Pin_6;
	A.GPIO_PuPd=GPIO_PuPd_UP;
	A.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOB,&A);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1);

	    B.GPIO_Mode=GPIO_Mode_AF;
		B.GPIO_OType=GPIO_OType_PP;
		B.GPIO_Pin=GPIO_Pin_7;
		B.GPIO_PuPd=GPIO_PuPd_UP;
		B.GPIO_Speed=GPIO_Speed_100MHz;

		GPIO_Init(GPIOB,&B);

		GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);

		C.GPIO_Mode=GPIO_Mode_OUT;
			C.GPIO_OType=GPIO_OType_PP;
			C.GPIO_Pin=GPIO_Pin_15;
			C.GPIO_PuPd=GPIO_PuPd_NOPULL;
			C.GPIO_Speed=GPIO_Speed_100MHz;

			GPIO_Init(GPIOD,&C);


		usart.USART_BaudRate=9600;
		usart.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		usart.USART_Mode=USART_Mode_Tx;
		usart.USART_Parity=USART_Parity_No;
		usart.USART_StopBits=USART_StopBits_1;
		usart.USART_WordLength=USART_WordLength_8b;

		USART_Init(USART1,&usart);

		USART_Cmd(USART1,ENABLE);

        data=10;
        char ch='c';
//long i=0;
        int i=0;
    while(1)
    {


    	while(!(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==SET))
    	{

    	}

    	//if(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==SET)
    	//{
            USART_SendData(USART1,i);
            i++;

            if(i==100)
            {
            	i=0;
            }

        	//USART_ClearFlag(USART1,USART_FLAG_TC);
    		//GPIO_SetBits(GPIOD,GPIO_Pin_15);

/*
    		for(i=0;i<200000;i++)
    		{

    		}
    				GPIO_ResetBits(GPIOD,GPIO_Pin_15);

    				for(i=0;i<200000;i++)
    				{

    				}


*/

    //	}
/*
    	while(!(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==SET))
    	{

    	}

    	USART_SendData(USART1,'\r');

    	while(!(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==SET))
    	    	{

    	    	}
    	USART_SendData(USART1,'\n');

*/

    }
}
