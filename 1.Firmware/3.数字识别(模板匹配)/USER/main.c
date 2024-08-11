#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "Key.h"
#include "malloc.h"
#include "mmc_sd.h"
#include "malloc.h"
#include "w25qxx.h"
#include "ff.h"
#include "exfuns.h"
#include "fattester.h"
#include "fontupd.h"
#include "text.h"
#include "WS2812B.h"
#include "Encoder.h"
#include "ST7789_Init.h"
#include "oled.h"
#include "BEEPER.h"
#include "Random.h"
#include "ov2640.h"
#include "dcmi.h"

uint32_t color[1] = {0};
uint8_t tmp_buff[240 * 120];
uint16_t lcd_buff[240 * 120]; // lcd���camera_buff������
uint8_t Encoder_Num, Key_Num = 0;
uint8_t press_flag;
extern uint8_t flag;
int main(void)
{
	FRESULT res;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // ����ϵͳ�ж����ȼ�����2
	delay_init(168);								// ��ʼ����ʱ����

	uart_init(115200);								// ��ʼ�����ڲ�����Ϊ115200
	LED_Init();										// ��ʼ��LED
	while (OV2640_Init())
	{
		printf("Camera init ERR\r\n");
	}
	Encoder_Init();
	W25QXX_Init();		 // ��ʼ��W25Q128
	my_mem_init(SRAMIN); // ��ʼ���ڲ��ڴ��
	PWM_WS2812B_Init(WS2812B_ARR - 1);
	exfuns_init(); // Ϊfatfs��ر��������ڴ�

	res = f_mount(fs[1], "1:", 1); // ����FLASH.
	if (res == FR_OK)
		printf("flash���سɹ�!\r\n");
	// else if (res == 0X0D) // FLASH����,FAT�ļ�ϵͳ����,���¸�ʽ��FLASH
	// {
	// 	// ��ʽ��FLASH
	// 	res = f_mkfs("1:", 1, 4096); // ��ʽ��FLASH,1,�̷�;1,����Ҫ������,8������Ϊ1����
	// 	if (res == 0)
	// 	{
	// 		f_setlabel((const TCHAR *)"1:Hugo");	// ����Flash���̵�����Ϊ��ALIENTEK
	// 		printf("Flash Disk Format Finish\r\n"); // ��ʽ�����
	// 	}
	// 	else
	// 		printf("Flash Disk Format Error!\r\n"); // ��ʽ��ʧ��
	// 	delay_ms(1000);
	// }

	Key_Init(); // ������ʼ��
	Beeper_Init();
	TIM4_Random_Init(1000 - 1, 84 - 1);
	ST7789_Init();
	LCD_Color_Fill(0, 0, 240, 240, 0x2a69);

	WS2812B_Write_24Bits(1, 0x880055);
	WS2812B_Show();

	My_DCMI_Init();																						   // DCMI����
	DCMI_DMA_Init((u32)lcd_buff, sizeof(lcd_buff) / 4, DMA_MemoryDataSize_HalfWord, DMA_MemoryInc_Enable); // DCMI DMA����
	OV2640_OutSize_Set(240, 120);
	DCMI_Start(); // ��������

	while (1)
	{

		Encoder_Num = Encoder_GetNum();

		if (Encoder_Num == 1)
			printf("1!");
		if (Encoder_Num == 2)
			printf("2!");
		Key_Num = Key_GetNum();
		if (Key_Num)
		{
			printf("ok!");
			press_flag = !press_flag;
		}
	}
}
