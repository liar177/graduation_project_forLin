#ifndef __PWM_H
#define __PWM_H


#include "stm32f10x.h"


/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������Ĭ��ʹ��TIM3

#define            PWM_TIM                   TIM3
#define            PWM_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            PWM_TIM_CLK               RCC_APB1Periph_TIM3
#define            PWM_TIM_Period            20-1
#define            PWM_TIM_Prescaler         180-1
// TIM3 ����Ƚ�ͨ��1
#define            PWM_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            PWM_TIM_CH1_PORT          GPIOA
#define            PWM_TIM_CH1_PIN           GPIO_Pin_6

// TIM3 ����Ƚ�ͨ��2
#define            PWM_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            PWM_TIM_CH2_PORT          GPIOA
#define            PWM_TIM_CH2_PIN           GPIO_Pin_7

// TIM3 ����Ƚ�ͨ��3
#define            PWM_TIM_CH3_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            PWM_TIM_CH3_PORT          GPIOB
#define            PWM_TIM_CH3_PIN           GPIO_Pin_0

// TIM3 ����Ƚ�ͨ��4
#define            PWM_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            PWM_TIM_CH4_PORT          GPIOB
#define            PWM_TIM_CH4_PIN           GPIO_Pin_1

/**************************��������********************************/

void PWM_TIM_Init(void);
void PWM_Control(int val);

#endif	/* __BSP_GENERALTIME_H */

//	printf("3. ΢������\r\n");
//	if(ESP8266_SendCmd("AT+RST\r\n", "WIFI GOT IP"))
//	{//WIFI���������ı�
//		while(ESP8266_SendCmd("AT+CWSTARTSMART\r\n", "OK"))
//			delay_ms(500);
//	}
