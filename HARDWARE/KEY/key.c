#include "key.h"

								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(KEY_RCC, ENABLE);//ʹ��PORTAʱ��

	GPIO_InitStructure.GPIO_Pin  = KEY_PIN;//KEY
	GPIO_InitStructure.GPIO_Mode = KEY_PIN_MODE; //���ó���������
 	GPIO_Init(KEY_PORT, &GPIO_InitStructure);//��ʼ��GPIO
	
}

