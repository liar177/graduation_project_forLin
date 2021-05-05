//C库
#include <string.h>

//单片机头文件
#include "sys.h"

//网络协议层
#include "onenet.h"

//网络设备
#include "esp8266.h"

//硬件驱动
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

uint32_t time = 0; // ms 计时变量 
DHT11_Data_TypeDef DHT11_Data;

float value_light = 0.0; 	//光照度
float value_mq2 = 0.0;		//烟雾浓度
float value_mq7 = 0.0;		//一氧化碳浓度
float value_sr04 = 0.0;		//超声波距离
u8 status_sr501 = 0;		//人体红外检测到的值
int max_mq7 = 50;			//烟雾浓度阈值
u8 LED_Light;				//PWM灯光亮度

//硬件初始化
void Hardware_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	
	delay_init();			//延时函数初始化
	
	LCD_Init();	   //液晶屏初始化
	LCD_Clear(GRAY0);
	Gui_DrawFont_GBK16(3,10,BLUE,GRAY0,(u8 *)"系统正在初始化");
	
	Usart1_Init(115200);	 		//串口1初始化为115200
	Usart2_Init(115200); 	//串口2，驱动ESP8266用
	LED_Init();				//LED初始化
	SR501_Init();			//红外热释电
	Hcsr04Init();			//超声波测距	
	ADCx_Init();			//ADC   DMA初始化
	DHT11_GPIO_Config();	//DHT11温湿度传感器初始化
	BH1750_Init();			//光照
	KEY_Init();
	BEEP_Init();
	PWM_TIM_Init();			//PWM频率=72000K/20*180=20Khz
	TIM_SetCompare3(TIM3,0);	
		
	Gui_DrawFont_GBK16(4,30,RED,GRAY0,(u8*)"设备初始化完成");
	Gui_DrawFont_GBK16(4,50,RED,GRAY0,(u8*)"正在连接网络。。。");
}

void Net_Init()
{
	ESP8266_Init();					//初始化ESP8266
	
	while(OneNet_DevLink())			//接入OneNET
		delay_ms(500);
	LED1 = 0;						//入网成功
	
	Gui_DrawFont_GBK16(4,70,RED,GRAY0,(u8*)"网络连接完成");
	delay_ms(2000);
}

int main(void)
{
	unsigned char *dataPtr = NULL;
	unsigned short timeCount = 300;	//发送间隔变量
	char str[] = "";
	
	Hardware_Init();				//初始化外围硬件
	Net_Init();						//网络初始化
	GENERAL_TIM_Init();				//1MS系统定时
	
	LCD_Clear(BLACK);
 	Gui_DrawFont_GBK16(25,4,BLACK,GRAY0,(u8 *)" 系统监控 ");
  GUI_DrawRectangle(1, 1, 128-2, 128-2, WHITE);		//边框

	while(1)
	{	
		delay_ms(10);
		timeCount ++;
				
		//接收数据
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
		{
			OneNet_RevPro(dataPtr);
		}	
		
		if(timeCount >= 300)	//发送间隔5s
		{	
			/* 温湿度传感器获取数据*/
			/*调用Read_DHT11读取温湿度，若成功则输出该信息*/
			if( Read_DHT11(&DHT11_Data)==SUCCESS)
			{
				sprintf(str, "温度：%d.%d ℃ ",DHT11_Data.temp_int,DHT11_Data.temp_deci);
				Gui_DrawFont_GBK16(4,30,RED,BLACK,(u8 *)str);
				sprintf(str, "湿度：%d.%d %c ",DHT11_Data.humi_int,DHT11_Data.humi_deci,'%');
				Gui_DrawFont_GBK16(4,50,RED,BLACK,(u8 *)str);
			}
			else
			{
				printf("Read DHT11 ERROR!\r\n");//读取数据失败，串口打印：Read DHT11 ERROR.
				Gui_DrawFont_GBK16(4,30,RED,BLACK,(u8 *)"ERROR!");
				Gui_DrawFont_GBK16(4,50,RED,BLACK,(u8 *)"ERROR!");
			}			
			
			/*光照度传感器获取数据*/			
			value_light = LIght_Intensity();
			sprintf(str, "光照：%.1flx  ",value_light);
			Gui_DrawFont_GBK16(4,70,YELLOW,BLACK,(u8 *)str);
			/*MQ2传感器获取烟雾数据*/	
			value_mq2 = MQ2_GetPPM();
			sprintf(str, "烟雾：%.1f ppm ",value_mq2);
			Gui_DrawFont_GBK16(4,90,BLUE,BLACK,(u8 *)str);
			
			/*MQ7传感器获取一氧化碳数据*/	
			value_mq7 = MQ7_GetPPM();
			sprintf(str, " CO ：%.1f ppm ",value_mq7);
			Gui_DrawFont_GBK16(4,110,GREEN,BLACK,(u8 *)str);
			

			
			OneNet_SendData();	//发送数据
			
			timeCount = 0;
			ESP8266_Clear();
		}
		/*超声波测距获取距离（CM）*/	
		value_sr04 = Hcsr04GetLength();
		/*人体检测*/	
		status_sr501 = SR501_Check();

		//用户处理
		//调节灯光亮度
		PWM_Control(LED_Light);
		
		//判断一氧化碳浓度是否超过上限
		if((int)value_mq7 >= max_mq7)
		{
			BEEP = 0;	//蜂鸣器报警
		}
		else
		{
			BEEP = 1;	//蜂鸣器关闭
		}
	}
}



















