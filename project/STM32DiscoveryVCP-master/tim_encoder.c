#include "tim_encoder.h"

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
GPIO_InitTypeDef GPIO_InitStructure;
   

void Init_TIM_encoder(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

   uint16_t PrescalerValue = 0;
  
  /*クロックの供給*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  
  /*GPIO関連設定(TIM2)*/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_11;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);

  /* プリスケーラの値の設定 */
  PrescalerValue = (uint16_t) ((SystemCoreClock ) / 84000000) - 1;

  /* メンバの値の設定 */
  TIM_TimeBaseStructure.TIM_Period = 0xffff-1;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* プリスケーラの設定 */
  TIM_PrescalerConfig(TIM1, PrescalerValue, TIM_PSCReloadMode_Immediate);
  
  TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  
  /*更新割り込み設定*/
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE );
  
  /* TIM3 enable counter */
  TIM_Cmd(TIM1, ENABLE);

  //TIM1
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;

  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;

  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;

  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);

}

