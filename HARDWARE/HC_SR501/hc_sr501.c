#include "hc_sr501.h"

void SR501_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(SR501_RCC,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = SR501_PIN;
	GPIO_InitStructure.GPIO_Mode = SR501_MODE;
 	GPIO_Init(SR501_GPIO, &GPIO_InitStructure);
}


u8 SR501_Check(void)
{

	if(SR501_STATUS  == 1)
	{
		return 1;			//检测到人
	}
	else
	{
		return 0;
	}
}


