#include "stm32f10x.h"
#include "LCD.h"
#include "LCD_Config.h"
#include "delay.h"



//液晶IO初始化配置
void LCD_GPIO_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	      
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB ,ENABLE);
	
#ifdef	LCD_RST
		GPIO_InitStructure.GPIO_Pin = LCD_RS| LCD_CS | LCD_SCL | LCD_SDA | LCD_RST;	
#else
		GPIO_InitStructure.GPIO_Pin = LCD_RS| LCD_CS | LCD_SCL | LCD_SDA;
#endif
	

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
      
}
//向SPI总线传输一个8位数据
void  SPI_WriteData(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
	  LCD_SDA_SET; //输出数据
      else LCD_SDA_CLR;
	   
      LCD_SCL_CLR;       
      LCD_SCL_SET;
      Data<<=1; 
	}
}

//向液晶屏写一个8位指令
void LCD_WriteIndex(u8 Index)
{
   //SPI 写命令时序开始
   LCD_CS_CLR;
   LCD_RS_CLR;
	 SPI_WriteData(Index);
   LCD_CS_SET;
}

//向液晶屏写一个8位数据
void LCD_WriteData(u8 Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   SPI_WriteData(Data);
   LCD_CS_SET; 
}
//向液晶屏写一个16位数据
void LCD_WriteData_16Bit(u16 Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
	 SPI_WriteData(Data>>8); 	//写入高8位数据
	 SPI_WriteData(Data); 			//写入低8位数据
   LCD_CS_SET; 
}

void LCD_WriteReg(u8 Index,u8 Data)
{
	LCD_WriteIndex(Index);
  LCD_WriteData(Data);
}

void LCD_Reset(void)
{

#ifdef LCD_RST
	LCD_RST_CLR;
#endif
	delay_ms(100);
#ifdef LCD_RST
	LCD_RST_SET;
#endif
	delay_ms(50);
	
}

//LCD Init For 1.44Inch LCD Panel with ST7735R.
void LCD_Init(void)
{	
	LCD_GPIO_Init();
	LCD_Reset(); //Reset before LCD Init.

	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	LCD_WriteIndex(0x11);//Sleep exit 
	delay_ms (120);
		
	//ST7735R Frame Rate
	LCD_WriteIndex(0xB1); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x2C); 
	LCD_WriteData(0x2D); 

	LCD_WriteIndex(0xB2); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x2C); 
	LCD_WriteData(0x2D); 

	LCD_WriteIndex(0xB3); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x2C); 
	LCD_WriteData(0x2D); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x2C); 
	LCD_WriteData(0x2D); 
	
	LCD_WriteIndex(0xB4); //Column inversion 
	LCD_WriteData(0x07); 
	
	//ST7735R Power Sequence
	LCD_WriteIndex(0xC0); 
	LCD_WriteData(0xA2); 
	LCD_WriteData(0x02); 
	LCD_WriteData(0x84); 
	LCD_WriteIndex(0xC1); 
	LCD_WriteData(0xC5); 

	LCD_WriteIndex(0xC2); 
	LCD_WriteData(0x0A); 
	LCD_WriteData(0x00); 

	LCD_WriteIndex(0xC3); 
	LCD_WriteData(0x8A); 
	LCD_WriteData(0x2A); 
	LCD_WriteIndex(0xC4); 
	LCD_WriteData(0x8A); 
	LCD_WriteData(0xEE); 
	
	LCD_WriteIndex(0xC5); //VCOM 
	LCD_WriteData(0x0E); 
	
	LCD_WriteIndex(0x36); //MX, MY, RGB mode 
	LCD_WriteData(0xC8); 
	
	//ST7735R Gamma Sequence
	LCD_WriteIndex(0xe0); 
	LCD_WriteData(0x0f); 
	LCD_WriteData(0x1a); 
	LCD_WriteData(0x0f); 
	LCD_WriteData(0x18); 
	LCD_WriteData(0x2f); 
	LCD_WriteData(0x28); 
	LCD_WriteData(0x20); 
	LCD_WriteData(0x22); 
	LCD_WriteData(0x1f); 
	LCD_WriteData(0x1b); 
	LCD_WriteData(0x23); 
	LCD_WriteData(0x37); 
	LCD_WriteData(0x00); 	
	LCD_WriteData(0x07); 
	LCD_WriteData(0x02); 
	LCD_WriteData(0x10); 

	LCD_WriteIndex(0xe1); 
	LCD_WriteData(0x0f); 
	LCD_WriteData(0x1b); 
	LCD_WriteData(0x0f); 
	LCD_WriteData(0x17); 
	LCD_WriteData(0x33); 
	LCD_WriteData(0x2c); 
	LCD_WriteData(0x29); 
	LCD_WriteData(0x2e); 
	LCD_WriteData(0x30); 
	LCD_WriteData(0x30); 
	LCD_WriteData(0x39); 
	LCD_WriteData(0x3f); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x03); 
	LCD_WriteData(0x10);  
	
	LCD_WriteIndex(0x2a);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x7f);

	LCD_WriteIndex(0x2b);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x9f);
	
	LCD_WriteIndex(0xF0); //Enable test command  
	LCD_WriteData(0x01); 
	LCD_WriteIndex(0xF6); //Disable ram power save mode 
	LCD_WriteData(0x00); 
	
	LCD_WriteIndex(0x3A); //65k mode 
	LCD_WriteData(0x05); 
	
	
	LCD_WriteIndex(0x29);//Display on	 
}


/*************************************************
函数名：LCD_Set_Region
功能：设置LCD显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void LCD_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end)
{		
	LCD_WriteIndex(0x2a);
	LCD_WriteData(0x00);
	LCD_WriteData(x_start+2);
	LCD_WriteData(0x00);
	LCD_WriteData(x_end+2);

	LCD_WriteIndex(0x2b);
	LCD_WriteData(0x00);
	LCD_WriteData(y_start+3);
	LCD_WriteData(0x00);
	LCD_WriteData(y_end+3);
	
	LCD_WriteIndex(0x2c);

}

/*************************************************
函数名：LCD_Set_XY
功能：设置LCD显示起始点
入口参数：xy坐标
返回值：无
*************************************************/
void LCD_SetXY(u16 x,u16 y)
{
  	LCD_SetRegion(x,y,x,y);
}

	
/*************************************************
函数名：LCD_DrawPoint
功能：画一个点
入口参数：无
返回值：无
*************************************************/
void Gui_DrawPoint(u16 x,u16 y,u16 Data)
{
	LCD_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}    

/*****************************************
 函数功能：读TFT某一点的颜色                          
 出口参数：color  点颜色值                                 
******************************************/
unsigned int LCD_ReadPoint(u16 x,u16 y)
{
  unsigned int Data;
  LCD_SetXY(x,y);

  //LCD_ReadData();//丢掉无用字节
  //Data=LCD_ReadData();
  LCD_WriteData(Data);
  return Data;
}
/*************************************************
函数名：LCD_Clear
功能：全屏清屏函数
入口参数：填充颜色COLOR
返回值：无
*************************************************/
void LCD_Clear(u16 Color)               
{	
   unsigned int i,m;
   LCD_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   LCD_WriteIndex(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	LCD_WriteData_16Bit(Color);
    }   
}

