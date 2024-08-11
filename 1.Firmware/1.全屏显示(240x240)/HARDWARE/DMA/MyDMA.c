#include "MyDMA.h"

u16 color_buff[1]; // DMA2的memory地址//在lcd.c中有extern

void DMA2_Init(u16 cndtr)
{
	/*初始化结构体*/
	DMA_InitTypeDef DMA_InitStructure;
	// NVIC_InitTypeDef NVIC_InitStructure;

	/*开启rcc时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	/*复位DMA2_Stream3*/
	DMA_DeInit(DMA2_Stream3);

	/*初始化结构体参数复位DMA2_Stream3映射SPI1_TX*/
	DMA_InitStructure.DMA_BufferSize = cndtr;
	DMA_InitStructure.DMA_Channel = DMA_Channel_3;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;

	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;

	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)color_buff;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&SPI1->DR;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;

	DMA_Init(DMA2_Stream3, &DMA_InitStructure);

	// NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream3_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	// NVIC_Init(&NVIC_InitStructure);

	// DMA_ClearFlag(DMA2_Stream3, DMA_FLAG_TCIF3);
	// DMA_ITConfig(DMA2_Stream3, DMA_IT_TC, ENABLE);

	/*关闭DMA2*/
	DMA_Cmd(DMA2_Stream3, DISABLE);
}

// #include "spi.h"
// void DMA2_Stream3_IRQHandler(void)
// {
// 	if (DMA_GetITStatus(DMA2_Stream3, DMA_IT_TCIF3) == SET)
// 	{
// 		DMA_ClearITPendingBit(DMA2_Stream3, DMA_IT_TCIF3);
		
// 		DMA_Cmd(DMA2_Stream3, DISABLE);
// 		LCD_CS_Set();
// 		SPI_DataSizeConfig(SPI1, SPI_DataSize_8b); // 设置SPI1为8bit传输模式
// 		SPI_Cmd(SPI1, ENABLE);
// 	}
// }
