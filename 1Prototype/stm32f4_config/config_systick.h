
#ifndef CONFIG_SYSTICK_H
#define CONFIG_SYSTICK_H
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#include "name_converter.h"

void SysTick_Handler(void);	//割り込みハンドラ
void Init_SysTick(float time);	//割り込みタイマーの初期設定
void Init_micro_interrupt(TIM_TypeDef *tim);
void TIM2_IRQHandler(void);

unsigned int count_time(int);
void reset_count_time(int);

#endif // !CONFIG_SYSTICK_H


/***********************仕様説明************************

void SysTick_Handler(void);	//割り込みハンドラ
	任意[ms]毎に割り込みによって呼び出されるルーチン
	この関数下に任意の割り込み処理をさせよう
	任意[ms]毎なので処理落ちさせないように注意


void Init_SysTick(unsigned float time);	//割り込みタイマーの初期設定　
	割り込み周期の設定関数
	割り込みに使用したい周期を引数に指定し使おう


******************************************************/
