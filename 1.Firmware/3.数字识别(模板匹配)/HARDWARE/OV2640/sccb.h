#ifndef __SCCB_H
#define __SCCB_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 

//IO方向设置
#define SCCB_SDA_IN()  {GPIOB->MODER&=~(3<<(1*2));GPIOB->MODER|=0<<1*2;}	//PB1 输入
#define SCCB_SDA_OUT() {GPIOB->MODER&=~(3<<(1*2));GPIOB->MODER|=1<<1*2;} 	//PB1 输出


//IO操作函数	 
#define SCCB_SCL    		PBout(0)	 	//SCL
#define SCCB_SDA    		PBout(1) 		//SDA	 

#define SCCB_READ_SDA    	PBin(1)  		//输入SDA    
#define SCCB_ID   			0X60  			//OV2640的ID

///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u8 reg,u8 data);
u8 SCCB_RD_Reg(u8 reg);
#endif













