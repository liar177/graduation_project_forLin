#ifndef __HC_SR04
#define __HC_SR04
#include "sys.h"

//超声波硬件接口定义
#define HCSR04_PORT       	GPIOA
#define HCSR04_CLK         	RCC_APB2Periph_GPIOB
#define HCSR04_TRIG			GPIO_Pin_7  
#define HCSR04_ECHO 		GPIO_Pin_6 

#define TRIG_Send 			PAout(7)   
#define ECHO_Reci 			PAin(6)  


void Hcsr04Init(void);
float Hcsr04GetLength(void );
#endif
