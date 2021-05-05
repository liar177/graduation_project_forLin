#ifndef __HC_SR501
#define __HC_SR501
#include "stm32f10x.h"

#define SR501_GPIO 		GPIOA
#define SR501_RCC   	RCC_APB2Periph_GPIOA
#define SR501_PIN		GPIO_Pin_5
#define SR501_MODE		GPIO_Mode_IPD
#define SR501_SPEED		GPIO_Speed_50MHz

#define SR501_STATUS  	GPIO_ReadInputDataBit(SR501_GPIO, SR501_PIN)//读取按键2 



void SR501_Init(void); //IO初始化
u8 Sound_Check(void);
u8 Light_Check(void);
u8 SR501_Check(void);


#endif
