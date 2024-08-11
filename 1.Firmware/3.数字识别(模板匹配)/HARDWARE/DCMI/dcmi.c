#include "sys.h"
#include "dcmi.h"
#include "lcd.h"
#include "led.h"
#include "ov2640.h"
#include "lcd.h"
#include "EasyTracered.h"
#include "usart.h"
#include "string.h"
#include "malloc.h"

u8 ov_frame = 0; // 帧率

uint8_t Number2[8 * 16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t Number3[8 * 16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 0, 255, 255, 255, 255, 0, 0};
uint8_t Number4[8 * 16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 255, 0, 255, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0};
uint8_t Number5[8 * 16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0};
uint8_t Number6[8 * 16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 255, 255, 255, 0, 0, 255, 0, 255, 0, 0, 255, 255, 0, 255, 255, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 255, 0, 255, 0, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t Number7[8 * 16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0};
uint8_t Number9[8 * 16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

extern uint16_t lcd_buff[240 * 120];
extern uint8_t tmp_buff[240 * 120];
uint8_t cut_buff[80 * 100];
uint8_t reduc_buff[8 * 16]; // 缩小后的模板
uint16_t tmpgrey;
extern uint8_t press_flag;

uint8_t trace_result; // 跟踪算法的标志

DCMI_InitTypeDef DCMI_InitStructure;

uint16_t Color_Block_y1, Color_Block_y2; // 色块的四边框坐标值

void Find_color_block_pos_y1(void)
{
	uint16_t thisline_black_pixel = 0; // 当前行的黑色像素总数
	uint16_t lastline_black_pixel = 0; // 上一行的黑色像素总数
	uint16_t temp = 80;
	uint8_t find_frame_flag = 0;
	for (uint16_t i = 0; i < 80 * 60; i++) // 上半框横轴查找
	{
		if (i % 80 == 0 && i != 0)
		{
			temp += 161;
		}
		else
			temp++;
		if (lcd_buff[temp] == 0x0) // 找到黑色像素
			thisline_black_pixel++;

		if (temp % 80 == 0)
		{
			if (thisline_black_pixel - lastline_black_pixel > 5 && lastline_black_pixel < 5)
			{
				find_frame_flag = 1;
			}

			if (find_frame_flag && thisline_black_pixel < 5)
			{
				Color_Block_y1 = (uint16_t)(i / 80.0f);
				find_frame_flag = 0;
				break;
			}
			else
			{
				lastline_black_pixel = thisline_black_pixel;
				thisline_black_pixel = 0;
			}
		}
	}
}

void Find_color_block_pos_y2(void)
{
	uint16_t thisline_black_pixel = 0; // 当前行的黑色像素总数
	uint16_t lastline_black_pixel = 0; // 上一行的黑色像素总数
	uint16_t temp = 28640;
	uint8_t find_frame_flag = 0;
	for (uint16_t i = 0; i < 80 * 60; i++) // 上半框横轴查找
	{
		if (i % 80 == 0 && i != 0)
		{
			temp -= 320;
		}
		else
			temp++;
		if (lcd_buff[temp] == 0x0) // 找到黑色像素
			thisline_black_pixel++;

		if (temp % 80 == 0)
		{
			if (thisline_black_pixel - lastline_black_pixel > 5 && lastline_black_pixel < 1)
			{
				find_frame_flag = 1;
			}

			if (find_frame_flag && thisline_black_pixel < 5)
			{
				Color_Block_y2 = (uint16_t)(120 - (i / 80.0f));
				find_frame_flag = 0;
				break;
			}
			else
			{
				lastline_black_pixel = thisline_black_pixel;
				thisline_black_pixel = 0;
			}
		}
	}
}

uint16_t Color_Block_CenterY;

void Find_final_y1(void)
{
	Color_Block_CenterY = (Color_Block_y1 + Color_Block_y2) / 2;
	uint16_t thisline_black_pixel = 0; // 当前行的黑色像素总数
	uint16_t lastline_black_pixel = 0; // 上一行的黑色像素总数
	uint16_t temp = Color_Block_CenterY * 240 - 150;
	// uint8_t find_frame_flag = 0;
	for (uint16_t i = 0; i < 60 * Color_Block_CenterY; i++) // 上半框横轴查找
	{
		if (i % 60 == 0 && i != 0)
		{
			temp -= 300;
		}
		else
			temp++;
		if (lcd_buff[temp] == 0x0) // 找到黑色像素
			thisline_black_pixel++;

		if (temp % 60 == 0) // 换行
		{
			if (lastline_black_pixel - thisline_black_pixel > 30 && thisline_black_pixel <= 0)
			{
				Color_Block_y1 = Color_Block_CenterY - (uint16_t)(i / 60.0f);
				break;
			}
			else
			{
				lastline_black_pixel = thisline_black_pixel;
				thisline_black_pixel = 0;
			}
		}
	}
}

void Find_final_y2(void)
{
	Color_Block_CenterY = (Color_Block_y1 + Color_Block_y2) / 2;
	uint16_t thisline_black_pixel = 0; // 当前行的黑色像素总数
	uint16_t lastline_black_pixel = 0; // 上一行的黑色像素总数
	uint16_t temp = Color_Block_CenterY * 240 - 150;
	// uint8_t find_frame_flag = 0;
	for (uint16_t i = 0; i < 60 * (120 - Color_Block_CenterY); i++) // 上半框横轴查找
	{
		if (i % 60 == 0 && i != 0)
		{
			temp += 181;
		}
		else
			temp++;
		if (lcd_buff[temp] == 0x0) // 找到黑色像素
			thisline_black_pixel++;

		if (temp % 60 == 0) // 换行
		{
			if (lastline_black_pixel - thisline_black_pixel > 30 && thisline_black_pixel <= 0)
			{
				Color_Block_y2 = Color_Block_CenterY + (uint16_t)(i / 60.0f);
				break;
			}
			else
			{
				lastline_black_pixel = thisline_black_pixel;
				thisline_black_pixel = 0;
			}
		}
	}
}

void Template_cut(void) // 模板裁剪
{
	// uint16_t temp = 80;
	// for (uint16_t i = 0; i < 80 * 100; i++) // 对240*120的中心区域80*100进行裁剪
	// {
	// 	if (i % 80 == 0 && i != 0)
	// 	{
	// 		temp += 161;
	// 	}
	// 	else
	// 		temp++;
	// 	cut_buff[i] = lcd_buff[temp];
	// }

	// for (uint16_t i = 0; i < 16; i++) // 最近邻域插值法对图像进行缩放80*100 -> 8*16
	// {
	// 	for (uint16_t j = 0; j < 8; j++)
	// 	{
	// 		reduc_buff[i * 8 + j] = cut_buff[i * 6 * 80 + j * 10];
	// 	}
	// }
	uint16_t temp = 88 + Color_Block_y1 * 240;
	float SrcY = 0;
	for (uint16_t i = 0; i < 72 * (Color_Block_y2 - Color_Block_y1); i++) // 对240*120的中心区域80*100进行裁剪
	{
		if (i % 72 == 0 && i != 0)
		{
			temp += 169;
		}
		else
			temp++;
		cut_buff[i] = lcd_buff[temp];
	}

	// for (uint16_t i = 0; i < 72 * (Color_Block_y2 - Color_Block_y1); i++)
	// {
	// 	if (i % 72 == 0)
	// 	{
	// 		printf("\r\n");
	// 	}
	// 	if (cut_buff[i] == 0x0)
	// 		printf("@");
	// 	else
	// 		printf(" ");
	// }

	SrcY = (Color_Block_y2 - Color_Block_y1) / 16.0f;

	for (uint16_t i = 0; i < 16; i++) // 最近邻域插值法对图像进行缩放80*100 -> 8*16
	{
		for (uint16_t j = 0; j < 8; j++)
		{
			reduc_buff[i * 8 + j] = cut_buff[i * (uint16_t)SrcY * 72 + j * 9];
		}
	}
}

void Template_match(void) // 模板匹配
{
	float var = 0;
	uint16_t err;
	for (uint16_t i = 0; i < 8 * 16; i++)
	{
		err = reduc_buff[i] - Number2[i];
		if (err > 255)
			err = 255;
		var += err * err;
		// printf("err:%d ",err);
	}
	var /= 8 * 16;
	// printf("var /= 8 * 16; = %.2f\r\n", var);

	if (var > 57000.0f)
	{
		Camera_ShowString(80, 0, "2", 0X05FF, 0X7fe0, 24, 0);
		return;
	}

	/* number3 */
	var = 0;
	for (uint16_t i = 0; i < 8 * 16; i++)
	{
		err = reduc_buff[i] - Number3[i];
		if (err > 255)
			err = 255;
		var += err * err;
		// printf("err:%d ",err);
	}
	// printf("var = %.2f\r\n", var);
	var /= 8 * 16;
	// printf("var /= 8 * 16; = %.2f\r\n", var);

	if (var > 55000.0f)
	{
		Camera_ShowString(80, 0, "3", 0X05FF, 0X7fe0, 24, 0);
		return;
	}

	/* number4 */
	var = 0;
	for (uint16_t i = 0; i < 8 * 16; i++)
	{
		err = reduc_buff[i] - Number4[i];
		if (err > 255)
			err = 255;
		var += err * err;
		// printf("err:%d ",err);
	}
	// printf("var = %.2f\r\n", var);
	var /= 8 * 16;
	printf("var /= 8 * 16; = %.2f\r\n", var);

	if (var > 53000.0f)
	{
		Camera_ShowString(80, 0, "4", 0X05FF, 0X7fe0, 24, 0);
		return;
	}

	// /* number5 */
	var = 0;
	for (uint16_t i = 0; i < 8 * 16; i++)
	{
		err = reduc_buff[i] - Number5[i];
		if (err > 255)
			err = 255;
		var += err * err;
		// printf("err:%d ",err);
	}
	// printf("var = %.2f\r\n", var);
	var /= 8 * 16;
	printf("var /= 8 * 16; = %.2f\r\n", var);

	if (var > 50000.0f)
	{
		Camera_ShowString(80, 0, "5", 0X05FF, 0X7fe0, 24, 0);
		return;
	}

	/* number7 */
	var = 0;
	for (uint16_t i = 0; i < 8 * 16; i++)
	{
		err = reduc_buff[i] - Number7[i];
		if (err > 255)
			err = 255;
		var += err * err;
		// printf("err:%d ",err);
	}
	// printf("var = %.2f\r\n", var);
	var /= 8 * 16;
	printf("var /= 8 * 16; = %.2f\r\n", var);

	if (var > 56500.0f)
	{
		Camera_ShowString(80, 0, "7", 0X05FF, 0X7fe0, 24, 0);
		return;
	}

	/* number9 */
	var = 0;
	for (uint16_t i = 0; i < 8 * 16; i++)
	{
		err = reduc_buff[i] - Number9[i];
		if (err > 255)
			err = 255;
		var += err * err;
		// printf("err:%d ",err);
	}
	// printf("var = %.2f\r\n", var);
	var /= 8 * 16;
	// printf("var /= 8 * 16; = %.2f\r\n", var);

	if (var > 50000.0f)
	{
		Camera_ShowString(80, 0, "9", 0X05FF, 0X7fe0, 24, 0);
	}
}

// DCMI中断服务函数
void DCMI_IRQHandler(void)
{
	if (DCMI_GetITStatus(DCMI_IT_FRAME) == SET) // 捕获到一帧图像
	{
		DCMI_ClearITPendingBit(DCMI_IT_FRAME); // 清除帧中断
		// DMA_Cmd(DMA2_Stream1, DISABLE); // 关掉dcmi的dma好让spi的dma可以运行
		DCMI_Stop();

		for (uint16_t i = 0; i < 240 * 120; i++)
		{
			tmpgrey = (u8)((((lcd_buff[i] & 0x00f100) >> 8) * 77 + ((lcd_buff[i] & 0x07e0) >> 3) * 150 + ((lcd_buff[i] & 0x001f) << 3) * 29 + 128) / 256);
			tmp_buff[i] = ((tmpgrey >> 3) | ((tmpgrey & ~3) << 3) | ((tmpgrey & ~7) << 8));
			if (tmpgrey > 110)
			{
				lcd_buff[i] = 0xffff;
			}
			else
			{
				lcd_buff[i] = 0x0000;
			}

			// if (lcd_buff[i] > 0x6800)
			// {
			// 	lcd_buff[i] = 0xffff;
			// }
			// else
			// {
			// 	lcd_buff[i] = 0x0000;
			// }
		} // 转灰度
		// Camera_DrawRectangle(80, 0, 160, 100, 0X7fe0); // 80*100

		Find_color_block_pos_y1();
		Find_color_block_pos_y2();

		Template_cut();
		Template_match();
		// Find_final_y1();
		// Find_final_y2();

		
		
		// Camera_DrawLine(90, Color_Block_y1, 150, Color_Block_y1, 0xf800);
		// Camera_DrawLine(90, Color_Block_y2, 150, Color_Block_y2, 0xf800);

		Camera_DrawRectangle(84, Color_Block_y1, 156, Color_Block_y2, 0X7fe0);

		// Camera_DrawLine(Color_Block_x1, Color_Block_y1, Color_Block_x1, Color_Block_y2, 0x005f);

		LCD_Camera_Fill(0, 0, 240, 120);

		if (press_flag)
		{
			Template_cut();

			for (uint16_t i = 0; i < 8 * 16; i++) // 打印出来
			{
				if (i % 8 == 0)
					printf("\r\n");
				if (reduc_buff[i] == 0x0)
				{
					printf("@");
				}
				else
					printf(" ");
			}
			for (uint16_t i = 0; i < 8 * 16; i++) // 打印出来
			{
				if (reduc_buff[i] == 0x0)
				{
					printf("%d,", i);
				}
			}
			printf("\r\n");
			for (uint16_t i = 0; i < 8 * 16; i++) // 打印出来
			{
				if (reduc_buff[i] == 0x0)
				{
					printf("255,");
				}
				else
					printf("0,");
			}
			press_flag = !press_flag;
		}

		LED0 = !LED0;
		ov_frame++;

		DCMI_Start();
		// DMA_Cmd(DMA2_Stream1, ENABLE); // spi的dma搬运完了就轮到dcmi的dma来搬运啦
	}
}
// DCMI DMA配置
// DMA_Memory0BaseAddr:存储器地址    将要存储摄像头数据的内存地址(也可以是外设地址)
// DMA_BufferSize:存储器长度    0~65535
// DMA_MemoryDataSize:存储器位宽
// DMA_MemoryDataSize:存储器位宽    @defgroup DMA_memory_data_size :DMA_MemoryDataSize_Byte/DMA_MemoryDataSize_HalfWord/DMA_MemoryDataSize_Word
// DMA_MemoryInc:存储器增长方式  @defgroup DMA_memory_incremented_mode  /** @defgroup DMA_memory_incremented_mode : DMA_MemoryInc_Enable/DMA_MemoryInc_Disable
void DCMI_DMA_Init(u32 DMA_Memory0BaseAddr, u16 DMA_BufferSize, u32 DMA_MemoryDataSize, u32 DMA_MemoryInc)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); // DMA2时钟使能
	DMA_DeInit(DMA2_Stream1);
	while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE)
	{
	} // 等待DMA2_Stream1可配置

	/* 配置 DMA Stream */
	DMA_InitStructure.DMA_Channel = DMA_Channel_1;							// 通道1 DCMI通道
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&DCMI->DR;				// 外设地址为:DCMI->DR
	DMA_InitStructure.DMA_Memory0BaseAddr = DMA_Memory0BaseAddr;			// DMA 存储器0地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					// 外设到存储器模式
	DMA_InitStructure.DMA_BufferSize = DMA_BufferSize;						// 数据传输量
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		// 外设非增量模式
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc;						// 存储器增量模式
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; // 外设数据长度:32位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize;				// 存储器数据长度
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							// 使用循环模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						// 高优先级
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;					// FIFO模式
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;			// 使用全FIFO
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;				// 外设突发单次传输
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;		// 存储器突发单次传输
	DMA_Init(DMA2_Stream1, &DMA_InitStructure);								// 初始化DMA Stream
}
// DCMI初始化
/**
 * VSYNC->PB7
 * HREF->PA4
 * RESET->PC10
 * PCLK->PA6
 * PWDN->PD2
 * SCL->PB0
 * SDA->PB1
 * D0~D7->PC6,PC7,PC8,PC9,PC11,PB6,PB8,PB9
 * XCLK->PC12
 */
void My_DCMI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE); // 使能GPIOA B C E 时钟
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);																	   // 使能DCMI时钟
	// PA4/6初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6; // PA4,PA6复用功能输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		   // 复用功能输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		   // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	   // 100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		   // 上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   // 初始化

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6; // PB6,PB7,PB8,PB9复用功能输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);											 // 初始化

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11; // PC6,PC7,PC8,PC9,PC11复用功能输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);														   // 初始化

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);	 // PA4,AF13  DCMI_HSYNC
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);	 // PA6,AF13  DCMI_PCLK
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);	 // PB7,AF13  DCMI_VSYNC
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);	 // PC6,AF13  DCMI_D0
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI);	 // PC7,AF13  DCMI_D1
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_DCMI);	 // PC8,AF13  DCMI_D2
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_DCMI);	 // PC9,AF13  DCMI_D3
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_DCMI); // PC11,AF13 DCMI_D4
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);	 // PB6,AF13  DCMI_D5
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_DCMI);	 // PB8,AF13  DCMI_D6
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_DCMI);	 // PB9,AF13  DCMI_D7

	DCMI_DeInit(); // 清除原来的设置

	DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;	 // 连续模式
	DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;	 // 全帧捕获
	DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b; // 8位数据格式
	DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_Low;			 // HSYNC 低电平有效
	DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Rising;		 // PCLK 上升沿有效
	DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;	 // 硬件同步HSYNC,VSYNC
	DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_Low;			 // VSYNC 低电平有效
	DCMI_Init(&DCMI_InitStructure);

	DCMI_ITConfig(DCMI_IT_FRAME, ENABLE); // 开启帧中断

	DCMI_Cmd(ENABLE); // DCMI使能

	NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  // 子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);							  // 根据指定的参数初始化VIC寄存器、
}
// DCMI,启动传输
void DCMI_Start(void)
{
	DMA_Cmd(DMA2_Stream1, ENABLE); // 开启DMA2,Stream1
	DCMI_CaptureCmd(ENABLE);	   // DCMI捕获使能
}
// DCMI,关闭传输
void DCMI_Stop(void)
{
	DCMI_CaptureCmd(DISABLE); // DCMI捕获使关闭

	while (DCMI->CR & 0X01)
		; // 等待传输结束

	DMA_Cmd(DMA2_Stream1, DISABLE); // 关闭DMA2,Stream1
}
////////////////////////////////////////////////////////////////////////////////
// 以下两个函数,供usmart调用,用于调试代码

// DCMI设置显示窗口
// sx,sy;LCD的起始坐标
// width,height:LCD显示范围.
void DCMI_Set_Window(u16 sx, u16 sy, u16 width, u16 height)
{
	DCMI_Stop();

	OV2640_OutSize_Set(width, height);

	DMA_Cmd(DMA2_Stream1, ENABLE); // 开启DMA2,Stream1

	DCMI_CaptureCmd(ENABLE); // DCMI捕获使能
}

// 通过usmart调试,辅助测试用.
// pclk/hsync/vsync:三个信号的有限电平设置
void DCMI_CR_Set(u8 pclk, u8 hsync, u8 vsync)
{
	DCMI_DeInit(); // 清除原来的设置

	DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;	 // 连续模式
	DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;	 // 全帧捕获
	DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b; // 8位数据格式
	DCMI_InitStructure.DCMI_HSPolarity = hsync << 6;					 // HSYNC 低电平有效
	DCMI_InitStructure.DCMI_PCKPolarity = pclk << 5;					 // PCLK 上升沿有效
	DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;	 // 硬件同步HSYNC,VSYNC
	DCMI_InitStructure.DCMI_VSPolarity = vsync << 7;					 // VSYNC 低电平有效
	DCMI_Init(&DCMI_InitStructure);

	DCMI_CaptureCmd(ENABLE); // DCMI捕获使能
	DCMI_Cmd(ENABLE);		 // DCMI使能
}
