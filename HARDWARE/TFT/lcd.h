#ifndef __LCD_H
#define __LCD_H
#include "stm32f10x.h"

// STM32接口------->TFT接口
// PB0 				连接至TFT -LED
// PB1					连接至TFT --RS
// PB12 				连接至TFT --CS
// RST(也可以IO控制)	TFT--RST
// PB13				连接至TFT -- CLK
// PB15				连接至TFT - SDI


#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111


//////////////////////////////////////////////////////////////////////
////-----------------LCD端口定义---------------- 
////采用了三极管控制背光亮灭，用户也可以接PWM调节背光亮度
//#define LCD_LED        	GPIO_Pin_0  //PB0 连接至TFT -LED
////接口定义在LCD_Driver.h内定义，请根据接线修改并修改相应IO初始化LCD_GPIO_Init()
//#define LCD_CTRL   	  	GPIOB		//定义TFT数据端口
//#define LCD_RS         	GPIO_Pin_1	//PB1连接至TFT --RS
//#define LCD_CS        	GPIO_Pin_12 //PB12 连接至TFT --CS
//#define LCD_RST     		GPIO_Pin_14	//直接和单片机的RST连接，或者可以通过IO控制
//#define LCD_SCL        	GPIO_Pin_13	//PB13连接至TFT -- CLK
//#define LCD_SDA        	GPIO_Pin_15	//PB15连接至TFT - SDI


////////////////////////////////////////////////////////////////////
//-----------------LCD端口定义---------------- 
//接口定义在LCD_Driver.h内定义，请根据接线修改并修改相应IO初始化LCD_GPIO_Init()
#define LCD_CTRL   	  	GPIOB		//定义TFT数据端口

//#define LCD_CS        	GPIO_Pin_12 //PB12 连接至TFT --CS
////#define LCD_RST     	GPIO_Pin_13	//直接和单片机的RST连接，或者可以通过IO控制
//#define LCD_RS         	GPIO_Pin_13	//PB14连接至TFT --RS
//#define LCD_SDA        	GPIO_Pin_14	//PB15连接至TFT - SDI
//#define LCD_SCL        	GPIO_Pin_15	//PB1连接至TFT -- CLK

#define LCD_RS         	GPIO_Pin_15	//PB14连接至TFT --RS
//#define LCD_RST     	GPIO_Pin_13	//直接和单片机的RST连接，或者可以通过IO控制
#define LCD_CS        	GPIO_Pin_14 //PB12 连接至TFT --CS
#define LCD_SCL        	GPIO_Pin_13	//PB1连接至TFT -- CLK
#define LCD_SDA        	GPIO_Pin_12	//PB15连接至TFT - SDI

//#define LCD_CS_SET(x) LCD_CTRL->ODR=(LCD_CTRL->ODR&~LCD_CS)|(x ? LCD_CS:0)

//液晶控制口置1操作语句宏定义
#define	LCD_CS_SET  	LCD_CTRL->BSRR=LCD_CS    
#define	LCD_RS_SET  	LCD_CTRL->BSRR=LCD_RS    
#define	LCD_SDA_SET  	LCD_CTRL->BSRR=LCD_SDA    
#define	LCD_SCL_SET  	LCD_CTRL->BSRR=LCD_SCL

#ifdef LCD_RST
#define	LCD_RST_SET  	LCD_CTRL->BSRR=LCD_RST 
#endif

#define	LCD_LED_SET  	LCD_CTRL->BSRR=LCD_LED   

//液晶控制口置0操作语句宏定义
#define	LCD_CS_CLR  	LCD_CTRL->BRR=LCD_CS    
#define	LCD_RS_CLR  	LCD_CTRL->BRR=LCD_RS    
#define	LCD_SDA_CLR  	LCD_CTRL->BRR=LCD_SDA    
#define	LCD_SCL_CLR  	LCD_CTRL->BRR=LCD_SCL  
#ifdef LCD_RST
#define	LCD_RST_CLR  	LCD_CTRL->BRR=LCD_RST  
#endif
#define	LCD_LED_CLR  	LCD_CTRL->BRR=LCD_LED 


#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //数据输出
#define LCD_DATAIN     LCD_DATA->IDR;   //数据输入

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 



void LCD_GPIO_Init(void);
void LCD_WriteIndex(u8 Index);
void LCD_WriteData(u8 Data);
void LCD_WriteReg(u8 Index,u8 Data);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_Reset(void);
void LCD_Init(void);
void LCD_Clear(u16 Color);
void LCD_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
unsigned int LCD_ReadPoint(u16 x,u16 y);
void LCD_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void LCD_WriteData_16Bit(u16 Data);


#endif

