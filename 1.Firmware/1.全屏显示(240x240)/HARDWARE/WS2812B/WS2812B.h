#ifndef __WS2812B_H__
#define __WS2812B_H__

#define WS2812B_DATAIN		PAout(1)

#define WS2812B_ARR	105	//TIM2���Զ���װֵ//ʹ��PWM���Ƶ����800kHz
#define T0H	35	//0����ߵ�ƽʱ��ռ1/3
#define T1H 70	//1����ߵ�ƽʱ��ռ2/3

/*ʹ�õ���ĸ���*/
#define WS2812B_NUM	1	
#define	 DATA_SIZE 	24	//WS2812B����һ�����ݵĴ�С��3���ֽڣ�24bit��


void PWM_WS2812B_Init(uint16_t arr);
void WS2812B_Write_24Bits(uint16_t num,uint32_t GRB_Data);
void WS2812B_Show(void);
void PWM_WS2812B_Red(uint16_t num);
void PWM_WS2812B_Green(uint16_t num);
void PWM_WS2812B_Blue(uint16_t num);

void WS2812B_Write_24Bits_independence(uint16_t num, uint32_t *GRB_Data);//����д���ص���ɫ
void set_ws2812_breathing(uint8_t index);//������

#endif


