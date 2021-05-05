#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"

#define BEEP_PORT		GPIOA
#define BEEP_RCC		RCC_APB2Periph_GPIOA
#define BEEP_PIN		GPIO_Pin_11
#define BEEP_PIN_MODE	GPIO_Mode_Out_PP

//蜂鸣器端口定义
#define BEEP PAout(11)	// BEEP,蜂鸣器接口	

//本设计中，蜂鸣器驱动采取低电平驱动
#define BEEP_ON		0;
#define BEEP_OFF	1;

//申明蜂鸣器状态全局变量	1 打开  0关闭
//默认为关闭
extern u8 BEEP_Status;

//蜂鸣器初始化,蜂鸣器默认为关闭
void BEEP_Init(void);

//关闭或打开蜂鸣器	onoff为 1 打开  onoff为 0 关闭
void BEEP_SetOnOff(u8 onoff);
		 				    
#endif

