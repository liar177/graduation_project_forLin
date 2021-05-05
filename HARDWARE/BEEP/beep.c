#include "beep.h"

//���������״̬ȫ�ֱ���		1 ��  0�ر�
u8 BEEP_Status = BEEP_OFF;
	    
//��������ʼ��,Ĭ��Ϊ�ر�
void BEEP_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BEEP_RCC, ENABLE);	 		//ʹ�ܷ������˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;				 //���Ŷ˿�����
	GPIO_InitStructure.GPIO_Mode = BEEP_PIN_MODE; 		 //�����ʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);	 		 //���ݲ�����ʼ��GPIO

	BEEP = BEEP_OFF;//�رշ��������
}

//�رջ�򿪷�����	onoffΪ 1 ��  onoffΪ 0 �ر�
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

