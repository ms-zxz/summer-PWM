#include "timer.h"
#include "led.h"
	 
//��ʱ��3�жϳ�ʼ��
void TIM3_Int_Init(u16 arr,u16 psc)
	{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;                         //�������

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);         //ʱ��ʹ��
		
		//��ʱ��TIM3��ʼ��
		TIM_TimeBaseStructure.TIM_Period = arr;                      //��һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
		TIM_TimeBaseStructure.TIM_Prescaler =psc;                    //������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //ʱ�ӷָ�:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);              //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	 
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );                    //ʹ�ܶ�ʱ��TIM3�ж�,��������ж�

		//�ж����ȼ�NVIC����
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;              //TIM3�ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    //��ռ���ȼ�0��
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;           //�����ȼ�3��
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //IRQͨ����ʹ��
		NVIC_Init(&NVIC_InitStructure);                              //��ʼ��NVIC�Ĵ���

		TIM_Cmd(TIM3, ENABLE);                                       //ʹ�ܶ�ʱ��TIM3				 
	}

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)                                           //TIM3�ж�
	{
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)             //�ж�TIM3�����ж��Ƿ���
			{
				
				LED1=!LED1;
				LED0=!LED0;                                          //LED0,LED1ͬʱ��ת
			    
				TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );        //��������жϱ�־ 
			}
	}


//��ʱ��3PMW��ʼ��
void TIM3_PWM_Init(u16 arr,u16 psc)
	
    {
		
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        GPIO_InitTypeDef GPIO_InitStructure;
        TIM_OCInitTypeDef  TIM_OCInitStructure;		
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                         //ʹ�ܶ�ʱ��3ʱ��
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                              //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure); 
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		
		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);                         //Timer3������ӳ��  TIM3_CH2->PB5    
	    
		//��ʱ��TIM3��ʼ��
		TIM_TimeBaseStructure.TIM_Period = arr;                                      //��һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
		TIM_TimeBaseStructure.TIM_Prescaler =psc;                                    //������ΪTIM3ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                      //ʱ�ӷָ�:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                  //���ϼ���ģʽ
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                              //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                            //��ʱ��ģʽ
 	    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                //�Ƚ����ʹ��
	    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                    //�������:TIM����Ƚϼ��Ը�
	    TIM_OC2Init(TIM3, &TIM_OCInitStructure);                                     //����Tָ���Ĳ�����ʼ������TIM3 OC2

        TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);                            //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
		

		TIM_Cmd(TIM3, ENABLE);                                                       //ʹ��TIM3
	 
	}
