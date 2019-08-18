#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
 

 int main(void)

 {

	u16 LED0pwmval=0;
	u8 dir=1;
	delay_init();                 //��ʼ����ʱ����
	LED_Init();                   //��ʼ���� LED ���ӵ�Ӳ���ӿ�

	TIM3_PWM_Init(899,0);         //PWM Ƶ��=72000/(899+1)=80Khz 
	   while(1)
		 {
		
			 delay_ms(10); 
			 
			 if(dir) 
				 LED0pwmval++;
			 else 
				 LED0pwmval--;
			 
			 if(LED0pwmval>300)dir=0; 
			 if(LED0pwmval==0)dir=1;
			 TIM_SetCompare2(TIM3,LED0pwmval);
		 }
 }
