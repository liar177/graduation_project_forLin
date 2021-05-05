#include "stm32f10x.h"
#include "LCD.h"
#include "LCD_Config.h"
#include "delay.h"



//Һ��IO��ʼ������
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
//��SPI���ߴ���һ��8λ����
void  SPI_WriteData(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
	  LCD_SDA_SET; //�������
      else LCD_SDA_CLR;
	   
      LCD_SCL_CLR;       
      LCD_SCL_SET;
      Data<<=1; 
	}
}

//��Һ����дһ��8λָ��
void LCD_WriteIndex(u8 Index)
{
   //SPI д����ʱ��ʼ
   LCD_CS_CLR;
   LCD_RS_CLR;
	 SPI_WriteData(Index);
   LCD_CS_SET;
}

//��Һ����дһ��8λ����
void LCD_WriteData(u8 Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   SPI_WriteData(Data);
   LCD_CS_SET; 
}
//��Һ����дһ��16λ����
void LCD_WriteData_16Bit(u16 Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
	 SPI_WriteData(Data>>8); 	//д���8λ����
	 SPI_WriteData(Data); 			//д���8λ����
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
��������LCD_Set_Region
���ܣ�����LCD��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�
����ֵ����
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
��������LCD_Set_XY
���ܣ�����LCD��ʾ��ʼ��
��ڲ�����xy����
����ֵ����
*************************************************/
void LCD_SetXY(u16 x,u16 y)
{
  	LCD_SetRegion(x,y,x,y);
}

	
/*************************************************
��������LCD_DrawPoint
���ܣ���һ����
��ڲ�������
����ֵ����
*************************************************/
void Gui_DrawPoint(u16 x,u16 y,u16 Data)
{
	LCD_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}    

/*****************************************
 �������ܣ���TFTĳһ�����ɫ                          
 ���ڲ�����color  ����ɫֵ                                 
******************************************/
unsigned int LCD_ReadPoint(u16 x,u16 y)
{
  unsigned int Data;
  LCD_SetXY(x,y);

  //LCD_ReadData();//���������ֽ�
  //Data=LCD_ReadData();
  LCD_WriteData(Data);
  return Data;
}
/*************************************************
��������LCD_Clear
���ܣ�ȫ����������
��ڲ����������ɫCOLOR
����ֵ����
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

