#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

//STM32F103核心板例程
//库函数版本例程
/********** mcudev.taobao.com 出品  ********/


//使用SysTick的普通计数模式对延迟进行管理
//包括delay_us,delay_ms

////////////////////////////////////////////////////////////////////////////////// 	 
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif





























