#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "Key.h"
#include "malloc.h"
// #include "mmc_sd.h"
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
uint16_t lcd_buff[240 * 240]; // lcd存放camera_buff缓存区
int8_t Encoder_Num, Key_Num = 0;

int main(void)
{
	// FRESULT res;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置系统中断优先级分组2
	delay_init(168);								// 初始化延时函数
	uart_init(115200);								// 初始化串口波特率为115200
	LED_Init();										// 初始化LED
	while (OV2640_Init())
	{
		printf("Camera init ERR\r\n");
	}
	Encoder_Init();
	W25QXX_Init();		 // 初始化W25Q128
	my_mem_init(SRAMIN); // 初始化内部内存池
	PWM_WS2812B_Init(WS2812B_ARR - 1);
	// exfuns_init(); // 为fatfs相关变量申请内存

	// res = f_mount(fs[1], "1:", 1); // 挂载FLASH.
	// if (res == FR_OK)
	// 	printf("flash挂载成功!\r\n");
	// else if (res == 0X0D) // FLASH磁盘,FAT文件系统错误,重新格式化FLASH
	// {
	// 	// 格式化FLASH
	// 	res = f_mkfs("1:", 1, 4096); // 格式化FLASH,1,盘符;1,不需要引导区,8个扇区为1个簇
	// 	if (res == 0)
	// 	{
	// 		f_setlabel((const TCHAR *)"1:Hugo");	// 设置Flash磁盘的名字为：ALIENTEK
	// 		printf("Flash Disk Format Finish\r\n"); // 格式化完成
	// 	}
	// 	else
	// 		printf("Flash Disk Format Error!\r\n"); // 格式化失败
	// 	delay_ms(1000);
	// }

	Key_Init(); // 按键初始化
	// Beeper_Init();
	TIM4_Random_Init(1000 - 1, 84 - 1);
	ST7789_Init();
	LCD_Color_Fill(0, 0, 240, 240, 0x4e99);

	WS2812B_Write_24Bits(1, 0x880055);
	WS2812B_Show();

	My_DCMI_Init();																						// DCMI配置
	DCMI_DMA_Init((u32)lcd_buff, 240 * 240 * 2 / 4, DMA_MemoryDataSize_HalfWord, DMA_MemoryInc_Enable); // DCMI DMA配置
	// OV2640_ImageWin_Set(0, 0, 240, 240);
	OV2640_OutSize_Set(240, 240);
	DCMI_Start(); // 启动传输

	while (1)
	{

	}
}
