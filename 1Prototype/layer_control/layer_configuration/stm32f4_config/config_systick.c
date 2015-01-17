#include "config_systick.h"

unsigned int 	g_time = 0,
						g_serial_time = 0,
						g_debug_time = 0,
						g_arm_time = 0,
						g_micro_time = 0;

/******************************************************************************
*	タイトル ： 割り込みハンドラ　関数場所固定
*	  関数名 ： SysTick_Handler
*	  戻り値 ： void型 
*	   引数1 ： void型  
*	  作成者 ： いいの		
*	  作成日 ： 2014/11/10
******************************************************************************/
void SysTick_Handler(void){
	//任意ms毎に割り込んで、1カウントする　単位:[ms]
	g_time ++;
	g_debug_time ++;
	g_serial_time ++;
	g_arm_time ++;
}

/******************************************************************************
*	タイトル ： 割り込みタイマ設定関数
*	  関数名 ： Init_SysTick
*	  戻り値 ： void型 なし
*	   引数1 ： float型 time  割り込み周期を設定
*	  作成者 ： いいの
*	  作成日 ： 2014/11/10
******************************************************************************/
void Init_SysTick(float time){
	//systick割り込みの設定	timeの単位:[s]
	SystemCoreClockUpdate();									//SystemCoreClockの更新
	NVIC_SetPriority(SysTick_IRQn,1);						//割り込み優先度の設定		優先度を1に
	if(SysTick_Config(SystemCoreClock*time)){		//systickによる割り込み周期を設定
						//失敗時動作　書き込み自由
	}
}

/******************************************************************************
*	タイトル ： timer2割り込み設定
*	  関数名 ： TIM2_IRQHandler
*	  戻り値 ： void型
*	    引数 ： なし
*	  作成者 ： 成宮陽生
*	  作成日 ： 2014/11/11
******************************************************************************/
void TIM2_IRQHandler(void)
{
	g_micro_time ++;
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void Init_micro_interrupt(TIM_TypeDef *tim)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;

	RCC_PeriphClock_TIM(tim);//クロック供給

	//TIM 周期
	TIM_TimeBaseStructure.TIM_Period = 84 - 1;
	//分周
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(tim, &TIM_TimeBaseStructure);

	TIM_ITConfig(tim, TIM_IT_Update, ENABLE);
	TIM_Cmd(tim, ENABLE);
	//割り込み
	NVIC_Configuration(Tim_irqn_select(tim));
}

unsigned int count_time(int i)
{
	if(i == 0){
		return (g_time);
	}else if(i == 1){
		return (g_serial_time);
	}else if(i == 2){
		return (g_micro_time);
	}else if(i==3){
		return (g_debug_time);
	}else if(i==4){
		return (g_arm_time);
	}

	return 0;
}

void reset_count_time(int i)
{
	if(i == 0){
		g_time = 0;
	}else if(i == 1){
		g_serial_time = 0;
	}else if(i == 2){
		g_micro_time = 0;
	}else if(i==3){
		g_debug_time = 0;
	}else if(i==4){
		g_arm_time = 0;
	}
}
