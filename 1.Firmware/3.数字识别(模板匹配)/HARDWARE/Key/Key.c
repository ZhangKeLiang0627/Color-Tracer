#include "Delay.h"
#include "stm32f4xx.h" // Device header
#include "BEEPER.h"
#include "key.h"

/*Only For 1 Key//只能适配一个按键//不适用多按键*/

uint8_t Key_KeyNumber; // 在定时器中得到的键码值（不受主程序中的delay影响）

Key_Tag Key_A0; // 定义一个A0引脚口的按键结构体

/**
 * @brief 返回键码值（放在主程序中循环）
 * @param  无
 * @retval 键码值
 */
uint8_t Key_GetNum(void)
{
	uint8_t Temp;
	Temp = Key_KeyNumber;
	if (Key_KeyNumber == SHORT_PRESS)
		Beeper_Perform(BEEPER_TRITONE);
	if (Key_KeyNumber == LONG_PRESS)
		Beeper_Perform(BEEPER_WARNING);
	Key_KeyNumber = 0;
	return Temp;
}

/**
 * @brief 独立按键初始化
 * @param  无
 * @retval 无
 */
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	Key_A0.DoublePressOpen_Flag = 0;
	Key_A0.LongPressOpen_Flag = 1;
}

/**
 * @brief 初步获得按键的电平
 * @param  无
 * @retval 返回键码值
 */
uint8_t Key_GetState(void)
{
	uint8_t KeyNumber = 0;

	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
	{
		KeyNumber = 1;
	}

	return KeyNumber;
}

/**
 * @brief 判断单击&长按&双击&软件消抖
 * @param  无
 * @retval 无
 */
void Key_Loop(void)
{

	static uint8_t NowState, LastState; // 定义现在时刻的按键电平状态和前一时刻的按键电平状态
	LastState = NowState;				// 更新前一时刻状态
	NowState = Key_GetState();			// 更新现在的状态

	if (LastState == 0 && NowState == 1 && Key_A0.LongPressOpen_Flag) // 按键按下，长按计时开始
	{
		Key_A0.Time_1 = 0; // 长按判断时长清零
	}

	if (LastState == 1 && NowState == 1 && Key_A0.Time_1 <= 800 && Key_A0.LongPressOpen_Flag) // 按键持续下压，长按时间累加（0.8s）
	{
		Key_A0.Time_1 += 20; // 加20是因为TIM2定时20ms
	}

	if (LastState == 1 && Key_A0.Time_1 > 800 && Key_A0.LongPressOpen_Flag) // 长按0.8s
	{
		Key_KeyNumber = LONG_PRESS; // 返回长按键码值2
		Key_A0.Time_1 = 201;		// 优雅地避开长按后头触发短按的尴尬
	}

	if (LastState == 1 && NowState == 0 && Key_A0.Time_1 <= 200) // 短按&&双击
	{

		if (Key_A0.DoublePressOpen_Flag == 0) // 双击开关标志为零//双击没有打开
		{
			Key_KeyNumber = SHORT_PRESS; // 返回单击键码值1
		}

		else if (Key_A0.DoublePressOpen_Flag == 1) // 双击打开
		{
			if (Key_A0.FirstPress_Flag == 0) // 第一次按下判断
			{
				Key_A0.FirstPress_Flag = 1;
				Key_A0.Time_2 = 0; // 双击判断时长清零
			}
			else if (Key_A0.FirstPress_Flag == 1) // 如果已经按下第一次
			{
				if (Key_A0.Time_2 <= 200) // 如果前后两次按下时间间隔小于0.3s//这里改成0.2s了 实测问题不大
				{
					Key_KeyNumber = DOUBLE_PRESS; // 返回双击键码值3
					Key_A0.FirstPress_Flag = 0;	  // 清零第一次按下标志位
				}
			}
		}
	}

	if (Key_A0.FirstPress_Flag) // 如果第一次已经按下
	{
		Key_A0.Time_2 += 20;	 // 双击判断时长开始累加//这里加20是因为TIM2计时20ms
		if (Key_A0.Time_2 > 200) // 如果双击判断时长大于0.3s//则判断为单击//这里改成0.2s了//0.2s大概是极限了
		{
			Key_KeyNumber = SHORT_PRESS; // 返回单击键码值1
			Key_A0.FirstPress_Flag = 0;	 // 清零第一次按下标志位
		}
	}
}
