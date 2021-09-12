#include "usart.h"
#include "stm32f10x.h"
#include <stdio.h>

/**
  * @brief  USARTxʱ�ӳ�ʼ������
  * @param  None
  * @retval None
  */
static void USART1_RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
}

/**
  * @brief  USART��GPIO��ʼ������
  * @param  None
  * @retval None
  */
static void USART1_GPIO_Configuration(void)
{
    /*����GPIO��ʼ���ṹ��*/
    GPIO_InitTypeDef GPIO_InitStructure;
    /*��ʼ���ṹ��*/
//    GPIO_StructInit(&GPIO_InitStructure);    
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

/**
  * @brief  USART1���ڳ�ʼ������
  * @param  None
  * @retval None
  */
void USART1_Configuration()
{
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    /*USART���ʱ�ӳ�ʼ������*/
    USART1_RCC_Configuration();

    /*USART���GPIO��ʼ������*/
    USART1_GPIO_Configuration();

  /* ʹ��USART1�ж�*/
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�0�� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
  NVIC_Init(&NVIC_InitStructure);

	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	
}

#if 1
/**
  * @brief  �ض���C�����е�printf������USART  sprintf();
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (u8)ch);

  /* ѭ��ֱ�����ͽ��� */
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {
  }
  return ch;
}
#endif
