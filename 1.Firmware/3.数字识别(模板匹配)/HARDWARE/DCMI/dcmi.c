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

u8 ov_frame = 0; // ֡��

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
uint8_t reduc_buff[8 * 16]; // ��С���ģ��
uint16_t tmpgrey;
extern uint8_t press_flag;

uint8_t trace_result; // �����㷨�ı�־

DCMI_InitTypeDef DCMI_InitStructure;

uint16_t Color_Block_y1, Color_Block_y2; // ɫ����ı߿�����ֵ

void Find_color_block_pos_y1(void)
{
	uint16_t thisline_black_pixel = 0; // ��ǰ�еĺ�ɫ��������
	uint16_t lastline_black_pixel = 0; // ��һ�еĺ�ɫ��������
	uint16_t temp = 80;
	uint8_t find_frame_flag = 0;
	for (uint16_t i = 0; i < 80 * 60; i++) // �ϰ��������
	{
		if (i % 80 == 0 && i != 0)
		{
			temp += 161;
		}
		else
			temp++;
		if (lcd_buff[temp] == 0x0) // �ҵ���ɫ����
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
	uint16_t thisline_black_pixel = 0; // ��ǰ�еĺ�ɫ��������
	uint16_t lastline_black_pixel = 0; // ��һ�еĺ�ɫ��������
	uint16_t temp = 28640;
	uint8_t find_frame_flag = 0;
	for (uint16_t i = 0; i < 80 * 60; i++) // �ϰ��������
	{
		if (i % 80 == 0 && i != 0)
		{
			temp -= 320;
		}
		else
			temp++;
		if (lcd_buff[temp] == 0x0) // �ҵ���ɫ����
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
	uint16_t thisline_black_pixel = 0; // ��ǰ�еĺ�ɫ��������
	uint16_t lastline_black_pixel = 0; // ��һ�еĺ�ɫ��������
	uint16_t temp = Color_Block_CenterY * 240 - 150;
	// uint8_t find_frame_flag = 0;
	for (uint16_t i = 0; i < 60 * Color_Block_CenterY; i++) // �ϰ��������
	{
		if (i % 60 == 0 && i != 0)
		{
			temp -= 300;
		}
		else
			temp++;
		if (lcd_buff[temp] == 0x0) // �ҵ���ɫ����
			thisline_black_pixel++;

		if (temp % 60 == 0) // ����
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
	uint16_t thisline_black_pixel = 0; // ��ǰ�еĺ�ɫ��������
	uint16_t lastline_black_pixel = 0; // ��һ�еĺ�ɫ��������
	uint16_t temp = Color_Block_CenterY * 240 - 150;
	// uint8_t find_frame_flag = 0;
	for (uint16_t i = 0; i < 60 * (120 - Color_Block_CenterY); i++) // �ϰ��������
	{
		if (i % 60 == 0 && i != 0)
		{
			temp += 181;
		}
		else
			temp++;
		if (lcd_buff[temp] == 0x0) // �ҵ���ɫ����
			thisline_black_pixel++;

		if (temp % 60 == 0) // ����
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

void Template_cut(void) // ģ��ü�
{
	// uint16_t temp = 80;
	// for (uint16_t i = 0; i < 80 * 100; i++) // ��240*120����������80*100���вü�
	// {
	// 	if (i % 80 == 0 && i != 0)
	// 	{
	// 		temp += 161;
	// 	}
	// 	else
	// 		temp++;
	// 	cut_buff[i] = lcd_buff[temp];
	// }

	// for (uint16_t i = 0; i < 16; i++) // ��������ֵ����ͼ���������80*100 -> 8*16
	// {
	// 	for (uint16_t j = 0; j < 8; j++)
	// 	{
	// 		reduc_buff[i * 8 + j] = cut_buff[i * 6 * 80 + j * 10];
	// 	}
	// }
	uint16_t temp = 88 + Color_Block_y1 * 240;
	float SrcY = 0;
	for (uint16_t i = 0; i < 72 * (Color_Block_y2 - Color_Block_y1); i++) // ��240*120����������80*100���вü�
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

	for (uint16_t i = 0; i < 16; i++) // ��������ֵ����ͼ���������80*100 -> 8*16
	{
		for (uint16_t j = 0; j < 8; j++)
		{
			reduc_buff[i * 8 + j] = cut_buff[i * (uint16_t)SrcY * 72 + j * 9];
		}
	}
}

void Template_match(void) // ģ��ƥ��
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

// DCMI�жϷ�����
void DCMI_IRQHandler(void)
{
	if (DCMI_GetITStatus(DCMI_IT_FRAME) == SET) // ����һ֡ͼ��
	{
		DCMI_ClearITPendingBit(DCMI_IT_FRAME); // ���֡�ж�
		// DMA_Cmd(DMA2_Stream1, DISABLE); // �ص�dcmi��dma����spi��dma��������
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
		} // ת�Ҷ�
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

			for (uint16_t i = 0; i < 8 * 16; i++) // ��ӡ����
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
			for (uint16_t i = 0; i < 8 * 16; i++) // ��ӡ����
			{
				if (reduc_buff[i] == 0x0)
				{
					printf("%d,", i);
				}
			}
			printf("\r\n");
			for (uint16_t i = 0; i < 8 * 16; i++) // ��ӡ����
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
		// DMA_Cmd(DMA2_Stream1, ENABLE); // spi��dma�������˾��ֵ�dcmi��dma��������
	}
}
// DCMI DMA����
// DMA_Memory0BaseAddr:�洢����ַ    ��Ҫ�洢����ͷ���ݵ��ڴ��ַ(Ҳ�����������ַ)
// DMA_BufferSize:�洢������    0~65535
// DMA_MemoryDataSize:�洢��λ��
// DMA_MemoryDataSize:�洢��λ��    @defgroup DMA_memory_data_size :DMA_MemoryDataSize_Byte/DMA_MemoryDataSize_HalfWord/DMA_MemoryDataSize_Word
// DMA_MemoryInc:�洢��������ʽ  @defgroup DMA_memory_incremented_mode  /** @defgroup DMA_memory_incremented_mode : DMA_MemoryInc_Enable/DMA_MemoryInc_Disable
void DCMI_DMA_Init(u32 DMA_Memory0BaseAddr, u16 DMA_BufferSize, u32 DMA_MemoryDataSize, u32 DMA_MemoryInc)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); // DMA2ʱ��ʹ��
	DMA_DeInit(DMA2_Stream1);
	while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE)
	{
	} // �ȴ�DMA2_Stream1������

	/* ���� DMA Stream */
	DMA_InitStructure.DMA_Channel = DMA_Channel_1;							// ͨ��1 DCMIͨ��
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&DCMI->DR;				// �����ַΪ:DCMI->DR
	DMA_InitStructure.DMA_Memory0BaseAddr = DMA_Memory0BaseAddr;			// DMA �洢��0��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					// ���赽�洢��ģʽ
	DMA_InitStructure.DMA_BufferSize = DMA_BufferSize;						// ���ݴ�����
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		// ���������ģʽ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc;						// �洢������ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; // �������ݳ���:32λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize;				// �洢�����ݳ���
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							// ʹ��ѭ��ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						// �����ȼ�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;					// FIFOģʽ
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;			// ʹ��ȫFIFO
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;				// ����ͻ�����δ���
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;		// �洢��ͻ�����δ���
	DMA_Init(DMA2_Stream1, &DMA_InitStructure);								// ��ʼ��DMA Stream
}
// DCMI��ʼ��
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

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE); // ʹ��GPIOA B C E ʱ��
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);																	   // ʹ��DCMIʱ��
	// PA4/6��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6; // PA4,PA6���ù������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		   // ���ù������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		   // �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	   // 100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		   // ����
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   // ��ʼ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6; // PB6,PB7,PB8,PB9���ù������
	GPIO_Init(GPIOB, &GPIO_InitStructure);											 // ��ʼ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11; // PC6,PC7,PC8,PC9,PC11���ù������
	GPIO_Init(GPIOC, &GPIO_InitStructure);														   // ��ʼ��

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

	DCMI_DeInit(); // ���ԭ��������

	DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;	 // ����ģʽ
	DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;	 // ȫ֡����
	DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b; // 8λ���ݸ�ʽ
	DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_Low;			 // HSYNC �͵�ƽ��Ч
	DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Rising;		 // PCLK ��������Ч
	DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;	 // Ӳ��ͬ��HSYNC,VSYNC
	DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_Low;			 // VSYNC �͵�ƽ��Ч
	DCMI_Init(&DCMI_InitStructure);

	DCMI_ITConfig(DCMI_IT_FRAME, ENABLE); // ����֡�ж�

	DCMI_Cmd(ENABLE); // DCMIʹ��

	NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // ��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  // �����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);							  // ����ָ���Ĳ�����ʼ��VIC�Ĵ�����
}
// DCMI,��������
void DCMI_Start(void)
{
	DMA_Cmd(DMA2_Stream1, ENABLE); // ����DMA2,Stream1
	DCMI_CaptureCmd(ENABLE);	   // DCMI����ʹ��
}
// DCMI,�رմ���
void DCMI_Stop(void)
{
	DCMI_CaptureCmd(DISABLE); // DCMI����ʹ�ر�

	while (DCMI->CR & 0X01)
		; // �ȴ��������

	DMA_Cmd(DMA2_Stream1, DISABLE); // �ر�DMA2,Stream1
}
////////////////////////////////////////////////////////////////////////////////
// ������������,��usmart����,���ڵ��Դ���

// DCMI������ʾ����
// sx,sy;LCD����ʼ����
// width,height:LCD��ʾ��Χ.
void DCMI_Set_Window(u16 sx, u16 sy, u16 width, u16 height)
{
	DCMI_Stop();

	OV2640_OutSize_Set(width, height);

	DMA_Cmd(DMA2_Stream1, ENABLE); // ����DMA2,Stream1

	DCMI_CaptureCmd(ENABLE); // DCMI����ʹ��
}

// ͨ��usmart����,����������.
// pclk/hsync/vsync:�����źŵ����޵�ƽ����
void DCMI_CR_Set(u8 pclk, u8 hsync, u8 vsync)
{
	DCMI_DeInit(); // ���ԭ��������

	DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;	 // ����ģʽ
	DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;	 // ȫ֡����
	DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b; // 8λ���ݸ�ʽ
	DCMI_InitStructure.DCMI_HSPolarity = hsync << 6;					 // HSYNC �͵�ƽ��Ч
	DCMI_InitStructure.DCMI_PCKPolarity = pclk << 5;					 // PCLK ��������Ч
	DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;	 // Ӳ��ͬ��HSYNC,VSYNC
	DCMI_InitStructure.DCMI_VSPolarity = vsync << 7;					 // VSYNC �͵�ƽ��Ч
	DCMI_Init(&DCMI_InitStructure);

	DCMI_CaptureCmd(ENABLE); // DCMI����ʹ��
	DCMI_Cmd(ENABLE);		 // DCMIʹ��
}
