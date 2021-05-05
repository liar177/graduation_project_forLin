#ifndef _ESP8266_H_
#define _ESP8266_H_

#include "sys.h"



#define REV_OK		0	//������ɱ�־
#define REV_WAIT	1	//����δ��ɱ�־


void ESP8266_Init(void);
void Usart2_Init(unsigned int baud);
void ESP8266_Clear(void);

void ESP8266_SendData(unsigned char *data, unsigned short len);

unsigned char *ESP8266_GetIPD(unsigned short timeOut);
void Usart2_SendString(unsigned char *str, unsigned short len);

#endif
