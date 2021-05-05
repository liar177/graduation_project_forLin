//C��
#include <string.h>

//��Ƭ��ͷ�ļ�
#include "sys.h"

//����Э���
#include "onenet.h"

//�����豸
#include "esp8266.h"

//Ӳ������
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "LCD.h"	 
#include "dht11.h" 	
#include "adc_dma.h"
#include "mq2.h"
#include "mq7.h"
#include "timer.h"
#include "bh1750.h"
#include "gui.h"
#include "LCD.h"
#include "hc_sr501.h"
#include "hc_sr04.h"
#include "TFT_demo.h"
#include "pwm.h"
#include "key.h"
#include "beep.h"

uint32_t time = 0; // ms ��ʱ���� 
DHT11_Data_TypeDef DHT11_Data;

float value_light = 0.0; 	//���ն�
float value_mq2 = 0.0;		//����Ũ��
float value_mq7 = 0.0;		//һ����̼Ũ��
float value_sr04 = 0.0;		//����������
u8 status_sr501 = 0;		//��������⵽��ֵ
int max_mq7 = 50;			//����Ũ����ֵ
u8 LED_Light;				//PWM�ƹ�����

u8 opp;
//Ӳ����ʼ��
void Hardware_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	delay_init();			//��ʱ������ʼ��
	
	LCD_Init();	   //Һ������ʼ��
	LCD_Clear(GRAY0);
	Gui_DrawFont_GBK16(3,10,BLUE,GRAY0,(u8 *)"ϵͳ���ڳ�ʼ��");
	
	Usart1_Init(115200);	 		//����1��ʼ��Ϊ115200
	Usart2_Init(115200); 	//����2������ESP8266��
	LED_Init();				//LED��ʼ��
	SR501_Init();			//�������͵�
	Hcsr04Init();			//���������	
	ADCx_Init();			//ADC   DMA��ʼ��
	DHT11_GPIO_Config();	//DHT11��ʪ�ȴ�������ʼ��
	BH1750_Init();			//����
	KEY_Init();
	BEEP_Init();
	PWM_TIM_Init();			//PWMƵ��=72000K/20*180=20Khz
	TIM_SetCompare3(TIM3,0);	
		
	Gui_DrawFont_GBK16(4,30,RED,GRAY0,(u8*)"�豸��ʼ�����");
	Gui_DrawFont_GBK16(4,50,RED,GRAY0,(u8*)"�����������硣����");
}

void Net_Init()
{
	ESP8266_Init();					//��ʼ��ESP8266
	
	while(OneNet_DevLink())			//����OneNET
		delay_ms(500);
	LED1 = 0;						//�����ɹ�
	
	Gui_DrawFont_GBK16(4,70,RED,GRAY0,(u8*)"�����������");
	delay_ms(2000);
}

int main(void)
{
	unsigned char *dataPtr = NULL;
	unsigned short timeCount = 300;	//���ͼ������
	char str[] = "";
	
	Hardware_Init();				//��ʼ����ΧӲ��
	Net_Init();						//�����ʼ��
	GENERAL_TIM_Init();				//1MSϵͳ��ʱ
	
	LCD_Clear(BLACK);
 	Gui_DrawFont_GBK16(25,4,BLACK,GRAY0,(u8 *)" ϵͳ��� ");
  GUI_DrawRectangle(1, 1, 128-2, 128-2, WHITE);		//�߿�

	while(1)
	{	
		delay_ms(10);
		timeCount ++;
				
		//��������
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
		{
			OneNet_RevPro(dataPtr);
		}	
		
		if(timeCount >= 300)	//���ͼ��5s
		{	
			/* ��ʪ�ȴ�������ȡ����*/
			/*����Read_DHT11��ȡ��ʪ�ȣ����ɹ����������Ϣ*/
			if( Read_DHT11(&DHT11_Data)==SUCCESS)
			{
				sprintf(str, "�¶ȣ�%d.%d �� ",DHT11_Data.temp_int,DHT11_Data.temp_deci);
				Gui_DrawFont_GBK16(4,30,RED,BLACK,(u8 *)str);
				sprintf(str, "ʪ�ȣ�%d.%d %c ",DHT11_Data.humi_int,DHT11_Data.humi_deci,'%');
				Gui_DrawFont_GBK16(4,50,RED,BLACK,(u8 *)str);
			}
			else
			{
				printf("Read DHT11 ERROR!\r\n");//��ȡ����ʧ�ܣ����ڴ�ӡ��Read DHT11 ERROR.
				Gui_DrawFont_GBK16(4,30,RED,BLACK,(u8 *)"ERROR!");
				Gui_DrawFont_GBK16(4,50,RED,BLACK,(u8 *)"ERROR!");
			}			
			
			/*���նȴ�������ȡ����*/			
			value_light = LIght_Intensity();
			sprintf(str, "���գ�%.1flx  ",value_light);
			Gui_DrawFont_GBK16(4,70,YELLOW,BLACK,(u8 *)str);
			/*MQ2��������ȡ��������*/	
			value_mq2 = MQ2_GetPPM();
			sprintf(str, "����%.1f ppm ",value_mq2);
			Gui_DrawFont_GBK16(4,90,BLUE,BLACK,(u8 *)str);
			
			/*MQ7��������ȡһ����̼����*/	
			value_mq7 = MQ7_GetPPM();
			sprintf(str, " CO ��%.1f ppm ",value_mq7);
			Gui_DrawFont_GBK16(4,110,GREEN,BLACK,(u8 *)str);
			

			
			OneNet_SendData();	//��������
			
			timeCount = 0;
			ESP8266_Clear();
		}
		/*����������ȡ���루CM��*/	
		value_sr04 = Hcsr04GetLength();
		/*������*/	
		status_sr501 = SR501_Check();

		//�û�����
		//���ڵƹ�����
		PWM_Control(LED_Light);
		
		//�ж�һ����̼Ũ���Ƿ񳬹�����
		if((int)value_mq7 >= max_mq7)
		{
			BEEP = 0;	//����������
		}
		else
		{
			BEEP = 1;	//�������ر�
		}
	}
}



















