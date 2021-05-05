/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LCD.h"
#include "GUI.h"
#include "SysTick.h"
#include "Picture.h"
#include "TFT_demo.h"
//unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};
//void Redraw_Mainmenu(void)
//{

//	LCD_Clear(GRAY0);
//	
// 	Gui_DrawFont_GBK16(8,4,BLACK,GRAY0,"大学生电子商铺");
//		
//	Gui_DrawFont_GBK16(24,30,BLUE,GRAY0,"《静夜思》");
//	
//	DisplayButtonUp(15,48,113,66); //x1,y1,x2,y2
//	Gui_DrawFont_GBK16(16,50,RED,GRAY0,"床前明月光,");

//	DisplayButtonUp(15,68,113,86); //x1,y1,x2,y2
//	Gui_DrawFont_GBK16(16,70,GREEN,GRAY0,"疑是地上霜。");

//	DisplayButtonUp(15,88,113,106); //x1,y1,x2,y2
//	Gui_DrawFont_GBK16(16,90,BLUE,GRAY0,"举头望明月，");

//	DisplayButtonUp(15,108,113,126); //x1,y1,x2,y2
//	Gui_DrawFont_GBK16(16,110,RED,GRAY0,"低头思故乡。");
//	delay_ms(1500);

//	
//}

//void Num_Test(void)
//{
//	u8 i=0;
//	LCD_Clear(GRAY0);
//	Gui_DrawFont_GBK16(16,20,RED,GRAY0,"Num Test");
//	delay_ms(1000);
//	LCD_Clear(GRAY0);

//	for(i=0;i<10;i++)
//	{
//		Gui_DrawFont_Num32((i%3)*40,32*(i/3)+5,RED,GRAY0,Num[i+1]);
//		delay_ms(100);
//	}
//	
//}

void Font_Test(void)
{
	LCD_Clear(GRAY0);

	Gui_DrawFont_GBK16(16,10,RED,GRAY0,"《静夜思》");
	Gui_DrawFont_GBK16(60,30,BLACK,GRAY0,"李白");
	Gui_DrawFont_GBK16(16,50,BLUE,GRAY0,"床前明月光,");
	Gui_DrawFont_GBK16(16,70,RED,GRAY0, "疑是地上霜。");
	Gui_DrawFont_GBK16(16,90,BLUE,GRAY0,"举头望明月，");
	Gui_DrawFont_GBK16(16,110,RED,GRAY0, "低头思故乡。");	
	delay_ms(1800);	
}

//void Color_Test(void)
//{
//	u8 i=1;
//	LCD_Clear(GRAY0);
//	
//	Gui_DrawFont_GBK16(20,10,BLUE,GRAY0,"Color Test");
//	delay_ms(200);

//	while(i--)
//	{
//			LCD_Clear(WHITE);
//			LCD_Clear(BLACK);
//			LCD_Clear(RED);
//	  	LCD_Clear(GREEN);
//	  	LCD_Clear(BLUE);
//	}		
//}

////取模方式 水平扫描 从左到右 低位在前
//void showimage(const unsigned char *p) //显示126*128图片
//{
//  	int i;
//	unsigned char picH,picL;
//	LCD_Clear(WHITE); //清屏  
//	

//	LCD_SetRegion(0,0,127,125);		//坐标设置
//		for(i=0;i<126*128;i++)
//	 {	
//		picL=*(p+i*2);	//数据低位在前
//		picH=*(p+i*2+1);				
//		LCD_WriteData_16Bit(picH<<8|picL);  						
//	 }

//}
//void TFT_Test_Demo(void)
//{
//	LCD_Init();			
//	Redraw_Mainmenu();//绘制主菜单(部分内容由于分辨率超出物理值可能无法显示)
//	Color_Test();//简单纯色填充测试
//	Num_Test();//数码管字体测试
//	Font_Test();//中英文显示测试		
//	showimage(gImage_lbxx);//图片显示示例
//	delay_ms(1200);
//}
