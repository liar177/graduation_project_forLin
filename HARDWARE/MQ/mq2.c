#include "mq2.h"
#include "timer.h"
#include "adc_dma.h"
#include "stdio.h"
#include "math.h"
#include "delay.h"

#define CAL_PPM 	15  	// У׼������PPMֵ
#define RL			5.1		// RL��ֵ
static float R0_MQ2 = 4.77; 	// Ԫ���ڽྻ�����е���ֵ

uint32_t times_mq2 = 0;

//�õ�ADC�����ڲ���������ֵ
//ȡ10��,Ȼ��ƽ��
vu16 Get_ADCValue_MQ2(void)
{
	u32 val = 0;
	u8 times = 10;
	u8 count;
	for(count = 0; count < times; count++)
	{
		val += ADC_ConvertedValue[0];//��ȡDMAͨ��ֵ
		delay_ms(5);
	}
	return val/times;
}


/********************************************
 * 1.651428	          200               *
 * 1.437143	          300               *
 * 1.257143	          400               *
 * 1.137143	          500               *
 * 1		              600               *
 * 0.928704	          700               *
 * 0.871296	          800               *
 * 0.816667	          900               *
 * 0.785714	          1000              *
 * 0.574393	          2000              *
 * 0.466047	          3000              *
 * 0.415581	          4000              *
 * 0.370478	          5000              *
 * 0.337031	          6000              *
 * 0.305119	          7000              *
 * 0.288169	          8000              *
 * 0.272727	          9000              *
 * 0.254795	          10000             *
 *                                      *
 * ppm = 613.9f * pow(RS/RL, -2.074f)   *
 ***************************************/
 
// ������У׼����
void MQ2_PPM_Calibration(float RS)
{
    R0_MQ2 = RS / pow(CAL_PPM / 613.9f, 1 / -2.074f);
}
 
// MQ2���������ݴ���
float MQ2_GetPPM(void)
{	
    float Vrl = 3.3f * Get_ADCValue_MQ2() / 4096.f;
	Vrl = ( (float)( (int)( (Vrl+0.005)*100 ) ) )/100;
    float RS = (3.3f - Vrl) / Vrl * RL; 
	
	if(times_mq2 < 6000) // ��ȡϵͳִ��ʱ�䣬300msǰ����У׼
    {
		R0_MQ2 = RS / pow(CAL_PPM / 613.9f, 1 / -2.074f);
    }
	
    float ppm = 613.9f * pow(RS/R0_MQ2, -2.074f);
	
//	printf("\nMQ2_R0 = %.2f\t", R0_MQ2);
//	printf("MQ2_ppm = %.2f\n", ppm);
    return  ppm;
}
		 







