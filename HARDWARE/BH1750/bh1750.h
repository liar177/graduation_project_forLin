#ifndef __BH1750_H
#define __BH1750_H	 
#include "stm32f10x.h"
 
//BH1750�ĵ�ַ
#define BH1750_Addr			0x46

//BH1750ָ����
#define POWER_OFF			0x00
#define POWER_ON			0x01
#define MODULE_RESET		0x07
#define	CONTINUE_H_MODE		0x10
#define CONTINUE_H_MODE2	0x11
#define CONTINUE_L_MODE		0x13
#define ONE_TIME_H_MODE		0x20
#define ONE_TIME_H_MODE2	0x21
#define ONE_TIME_L_MODE		0x23

//����ģʽ
#define Measure_Mode			CONTINUE_H_MODE

//�ֱ���	����ǿ�ȣ���λlx��=��High Byte  + Low Byte��/ 1.2 * ��������
#if ((Measure_Mode==CONTINUE_H_MODE2)|(Measure_Mode==ONE_TIME_H_MODE2))
	#define Resolurtion		0.5
#elif ((Measure_Mode==CONTINUE_H_MODE)|(Measure_Mode==ONE_TIME_H_MODE))
	#define Resolurtion		1
#elif ((Measure_Mode==CONTINUE_L_MODE)|(Measure_Mode==ONE_TIME_L_MODE))
	#define Resolurtion		4
#endif

#define BH1750_I2C_WR	0		/* д����bit */
#define BH1750_I2C_RD	1		/* ������bit */


/* ����I2C�������ӵ�GPIO�˿�, ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */
#define BH1750_GPIO_PORT_I2C	GPIOB			/* GPIO�˿� */
#define BH1750_RCC_I2C_PORT 	RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define BH1750_I2C_SCL_PIN		GPIO_Pin_6			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define BH1750_I2C_SDA_PIN		GPIO_Pin_7			/* ���ӵ�SDA�����ߵ�GPIO */


/* �����дSCL��SDA�ĺ꣬�����Ӵ���Ŀ���ֲ�ԺͿ��Ķ��� */
#if 0	/* �������룺 1 ѡ��GPIO�Ŀ⺯��ʵ��IO��д */
	#define BH1750_I2C_SCL_1()  GPIO_SetBits(BH1750_GPIO_PORT_I2C, BH1750_I2C_SCL_PIN)		/* SCL = 1 */
	#define BH1750_I2C_SCL_0()  GPIO_ResetBits(BH1750_GPIO_PORT_I2C, BH1750_I2C_SCL_PIN)		/* SCL = 0 */
	
	#define BH1750_I2C_SDA_1()  GPIO_SetBits(BH1750_GPIO_PORT_I2C, BH1750_I2C_SDA_PIN)		/* SDA = 1 */
	#define BH1750_I2C_SDA_0()  GPIO_ResetBits(BH1750_GPIO_PORT_I2C, BH1750_I2C_SDA_PIN)		/* SDA = 0 */
	
	#define BH1750_I2C_SDA_READ()  GPIO_ReadInputDataBit(BH1750_GPIO_PORT_I2C, BH1750_I2C_SDA_PIN)	/* ��SDA����״̬ */
#else	/* �����֧ѡ��ֱ�ӼĴ�������ʵ��IO��д */
    /*��ע�⣺����д������IAR��߼����Ż�ʱ���ᱻ�����������Ż� */
	#define BH1750_I2C_SCL_1()  BH1750_GPIO_PORT_I2C->BSRR = BH1750_I2C_SCL_PIN				/* SCL = 1 */
	#define BH1750_I2C_SCL_0()  BH1750_GPIO_PORT_I2C->BRR = BH1750_I2C_SCL_PIN				/* SCL = 0 */
	
	#define BH1750_I2C_SDA_1()  BH1750_GPIO_PORT_I2C->BSRR = BH1750_I2C_SDA_PIN				/* SDA = 1 */
	#define BH1750_I2C_SDA_0()  BH1750_GPIO_PORT_I2C->BRR = BH1750_I2C_SDA_PIN				/* SDA = 0 */
	
	#define BH1750_I2C_SDA_READ()  ((BH1750_GPIO_PORT_I2C->IDR & BH1750_I2C_SDA_PIN) != 0)	/* ��SDA����״̬ */
#endif


void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
uint8_t i2c_CheckDevice(uint8_t _Address);

void BH1750_Init(void);			//δ����IIC��ʼ��
float LIght_Intensity(void);	//��ȡ����ǿ�ȵ�ֵ
uint8_t BH1750_Byte_Write(uint8_t data);
uint16_t BH1750_Read_Measure(void);
void BH1750_Power_ON(void);
void BH1750_Power_OFF(void);
void BH1750_RESET(void);

		 				    
#endif
