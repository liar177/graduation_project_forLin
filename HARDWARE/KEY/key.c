#include "key.h"

								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(KEY_RCC, ENABLE);//使能PORTA时钟

	GPIO_InitStructure.GPIO_Pin  = KEY_PIN;//KEY
	GPIO_InitStructure.GPIO_Mode = KEY_PIN_MODE; //设置成上拉输入
 	GPIO_Init(KEY_PORT, &GPIO_InitStructure);//初始化GPIO
	
}

