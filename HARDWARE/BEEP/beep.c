#include "beep.h"

//定义蜂鸣器状态全局变量		1 打开  0关闭
u8 BEEP_Status = BEEP_OFF;
	    
//蜂鸣器初始化,默认为关闭
void BEEP_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BEEP_RCC, ENABLE);	 		//使能蜂鸣器端口时钟
	
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;				 //引脚端口配置
	GPIO_InitStructure.GPIO_Mode = BEEP_PIN_MODE; 		 //输出方式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);	 		 //根据参数初始化GPIO

	BEEP = BEEP_OFF;//关闭蜂鸣器输出
}

//关闭或打开蜂鸣器	onoff为 1 打开  onoff为 0 关闭
void BEEP_SetOnOff(u8 onoff)
{
	if(onoff == 1)
	{
		BEEP = BEEP_ON;
		BEEP_Status = 1;
	}
	else if(onoff == 0)
	{
		BEEP = BEEP_OFF;
		BEEP_Status = 0;
	}
}

