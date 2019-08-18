#include "timer.h"
#include "led.h"
	 
//定时器3中断初始化
void TIM3_Int_Init(u16 arr,u16 psc)
	{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;                         //定义变量

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);         //时钟使能
		
		//定时器TIM3初始化
		TIM_TimeBaseStructure.TIM_Period = arr;                      //下一个更新事件装入活动的自动重装载寄存器周期的值	
		TIM_TimeBaseStructure.TIM_Prescaler =psc;                    //用来作为TIMx时钟频率除数的预分频值
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //时钟分割:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);              //根据指定的参数初始化TIMx的时间基数单位
	 
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );                    //使能定时器TIM3中断,允许更新中断

		//中断优先级NVIC设置
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;              //TIM3中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    //先占优先级0级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;           //从优先级3级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //IRQ通道被使能
		NVIC_Init(&NVIC_InitStructure);                              //初始化NVIC寄存器

		TIM_Cmd(TIM3, ENABLE);                                       //使能定时器TIM3				 
	}

//定时器3中断服务程序
void TIM3_IRQHandler(void)                                           //TIM3中断
	{
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)             //判断TIM3更新中断是否发生
			{
				
				LED1=!LED1;
				LED0=!LED0;                                          //LED0,LED1同时反转
			    
				TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );        //清除更新中断标志 
			}
	}


//定时器3PMW初始化
void TIM3_PWM_Init(u16 arr,u16 psc)
	
    {
		
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        GPIO_InitTypeDef GPIO_InitStructure;
        TIM_OCInitTypeDef  TIM_OCInitStructure;		
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                         //使能定时器3时钟
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                              //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure); 
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		
		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);                         //Timer3部分重映射  TIM3_CH2->PB5    
	    
		//定时器TIM3初始化
		TIM_TimeBaseStructure.TIM_Period = arr;                                      //下一个更新事件装入活动的自动重装载寄存器周期的值	
		TIM_TimeBaseStructure.TIM_Prescaler =psc;                                    //用来作为TIM3时钟频率除数的预分频值
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                      //时钟分割:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                  //向上计数模式
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                              //根据指定的参数初始化TIMx的时间基数单位
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                            //定时器模式
 	    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                //比较输出使能
	    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                    //输出极性:TIM输出比较极性高
	    TIM_OC2Init(TIM3, &TIM_OCInitStructure);                                     //根据T指定的参数初始化外设TIM3 OC2

        TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);                            //使能TIM3在CCR2上的预装载寄存器
		

		TIM_Cmd(TIM3, ENABLE);                                                       //使能TIM3
	 
	}
