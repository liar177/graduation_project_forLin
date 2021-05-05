#include "mq7.h"
#include "timer.h"
#include "adc_dma.h"
#include "stdio.h"
#include "math.h"
#include "delay.h"

#define CAL_PPM  10  // У׼������PPMֵ
#define RL	5.1 // RL��ֵ
static float R0_MQ7 = 3.21;
uint32_t times_mq7 = 0;
//�õ�ADC�����ڲ���������ֵ
//ȡ10��,Ȼ��ƽ��
vu16 Get_ADCValue_MQ7(void)
{
	u32 val = 0;
	u8 times = 10;
	u8 count;
	for(count = 0; count < times; count++)
	{
		val += ADC_ConvertedValue[1];
		delay_ms(5);
	}
	return val/times;
}

/****************************************
 *  RS/R0        ppm				*
 *  1.6		     50                 *
 *  1	         100                *
 *  0.6		     200                *
 *  0.46	     300                *
 *  0.39	     400                *
 *  0.28	     600                *
 *  0.21	     1000               *
 * ppm = 98.322f * pow(RS/R0, -1.458f)  *
 ***************************************/


 
 // ������У׼����
void MQ7_PPM_Calibration(float RS)
{
	
    R0_MQ7 = RS / pow(CAL_PPM / 98.322, 1 / -1.458f);
}
 
 // ��ȡ��������ֵ
float MQ7_GetPPM(void)
{
    float Vrl = 3.3f * Get_ADCValue_MQ7() / 4096.f;
	Vrl = ( (float)( (int)( (Vrl+0.005)*100 ) ) )/100;
    float RS = (3.3f - Vrl) / Vrl * RL;

    if(times_mq7 < 3000) // ��ȡϵͳִ��ʱ�䣬3sǰ����У׼
    {
		MQ7_PPM_Calibration(RS);
    }
	
    float ppm = 98.322f * pow(RS/R0_MQ7, -1.458f);
//	printf("\nMQ7_R0 = %.2f\t", R0_MQ7);
//	printf("MQ7_ppm = %.2f\n", ppm);
    return  ppm;
}

