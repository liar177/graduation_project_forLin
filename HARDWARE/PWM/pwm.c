#include "pwm.h"

static void PWM_TIM_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

//	// ����Ƚ�ͨ��1 GPIO ��ʼ��
//	RCC_APB2PeriphClockCmd(PWM_TIM_CH1_GPIO_CLK, ENABLE);
//	GPIO_InitStructure.GPIO_Pin =  PWM_TIM_CH1_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(PWM_TIM_CH1_PORT, &GPIO_InitStructure);

//	// ����Ƚ�ͨ��2 GPIO ��ʼ��
//	RCC_APB2PeriphClockCmd(PWM_TIM_CH2_GPIO_CLK, ENABLE);
//	GPIO_InitStructure.GPIO_Pin =  PWM_TIM_CH2_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(PWM_TIM_CH2_PORT, &GPIO_InitStructure);

	// ����Ƚ�ͨ��3 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(PWM_TIM_CH3_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  PWM_TIM_CH3_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_TIM_CH3_PORT, &GPIO_InitStructure);

//	// ����Ƚ�ͨ��4 GPIO ��ʼ��
//	RCC_APB2PeriphClockCmd(PWM_TIM_CH4_GPIO_CLK, ENABLE);
//	GPIO_InitStructure.GPIO_Pin =  PWM_TIM_CH3_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(PWM_TIM_CH3_PORT, &GPIO_InitStructure);
}


///*
// * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
// * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
// * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            ����
// *	TIM_CounterMode			     TIMx,x[6,7]û�У���������
// *  TIM_Period               ����
// *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM�ź� ���ں�ռ�ձȵļ���--------------- */
// ARR ���Զ���װ�ؼĴ�����ֵ
// CLK_cnt����������ʱ�ӣ����� Fck_int / (psc+1) = 72M/(psc+1)
// PWM �źŵ����� T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// ռ�ձ�P=CCR/(ARR+1)

static void PWM_TIM_Mode_Config(void)
{
  // ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	PWM_TIM_APBxClock_FUN(PWM_TIM_CLK,ENABLE);

/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �������ڣ���������Ϊ100K
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=PWM_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= PWM_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(PWM_TIM, &TIM_TimeBaseStructure);

	/*--------------------����ȽϽṹ���ʼ��-------------------*/	
	// ռ�ձ�����
//	uint16_t CCR1_Val = 5;
//	uint16_t CCR2_Val = 4;
	uint16_t CCR3_Val = 0;
//	uint16_t CCR4_Val = 0;
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
//	// ����Ƚ�ͨ�� 1
//	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
//	TIM_OC1Init(PWM_TIM, &TIM_OCInitStructure);
//	TIM_OC1PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);
//	
//	// ����Ƚ�ͨ�� 2
//	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
//	TIM_OC2Init(PWM_TIM, &TIM_OCInitStructure);
//	TIM_OC2PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);
//	
	// ����Ƚ�ͨ�� 3
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
	TIM_OC3Init(PWM_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);
	
//	// ����Ƚ�ͨ�� 4
//	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
//	TIM_OC4Init(PWM_TIM, &TIM_OCInitStructure);
//	TIM_OC4PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);
	
	// ʹ�ܼ�����
	TIM_Cmd(PWM_TIM, ENABLE);
}

void PWM_TIM_Init(void)
{
	PWM_TIM_GPIO_Config();
	PWM_TIM_Mode_Config();		
}

void PWM_Control(int val)
{
	TIM_SetCompare3(TIM3,val);
}

/*********************************************END OF FILE**********************/
