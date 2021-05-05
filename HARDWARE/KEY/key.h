#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 

#define KEY_PORT		GPIOA
#define KEY_RCC			RCC_APB2Periph_GPIOA
#define KEY_PIN			GPIO_Pin_8
#define KEY_PIN_MODE	GPIO_Mode_IPU
//#define KEY0 PAin(8)   	//PA8

#define KEY  GPIO_ReadInputDataBit(KEY_PORT,KEY_PIN)//读取按键

#define KEY_PRES 	0	//KEY0按下

void KEY_Init(void);//IO初始化
				    
#endif
