#include "key_exti.h"
#include "stm32f10x.h"

static void EXTI_Key_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   			//��NVIC�ж����ȼ���������Ϊ��һ��
  
  /* ����P[A|B|C|D|E]���ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;            //���õ�ΪEXTI��5~9���ж�����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;            //���õ�ΪEXTI��10~15���ж�����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}

/*
 * ��������EXTI_Key_GPIO_Configuration
 * ����  �����ö���������ʹ�õ�GPIO�˿ڼ�ģʽ
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
static void EXTI_Key_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
    /* EXTI line gpio config(PD8,PD9,PD10,PD11) */	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_3;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
}

/*
 * ��������EXTI_Key_init
 * ����  ����ʼ����������������������ж϶˿ڼ�ģʽ
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void EXTI_Key_init(void)
{	
	EXTI_InitTypeDef EXTI_InitStructure;												

    /* config the extiline(PD) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,ENABLE);	//ʹ���ж����Ҫ��������ʱ��
    /* config the GPIO(PD) */
  EXTI_Key_GPIO_Configuration();
    /* config the NVIC(PD) */
	EXTI_Key_NVIC_Configuration();

	/* EXTI line mode config */
	/*�����ⲿ�ж�8��9��10��11���½���ʱ�����ж�*/

  EXTI_InitStructure.EXTI_Line=EXTI_Line3|EXTI_Line4;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	
	EXTI_Init(&EXTI_InitStructure);
    
}   
    
    
    
    
    
    
    



