#include "tim_pwm.h"
//初期設定
#define TIM_CNTRCLK     24000000UL // TIM3 Clock Frequency : 24MHz
#define TIM_FREQ        100000         // TIM3 PWM Frequency   : 36KHz
//モーター設定
#define BRAKE   999

/*
//モーター1
#define MOTOR1_OUT_PIN  GPIOB
#define MOTOR1_OUT_CW   GPIO_Pin_7
#define MOTOR1_OUT_CCW  GPIO_Pin_5
//モーター2
#define MOTOR2_OUT_PIN  GPIOB
#define MOTOR2_OUT_CW   GPIO_Pin_6
#define MOTOR2_OUT_CCW  GPIO_Pin_4
//モーター3
#define MOTOR3_OUT_PIN  GPIOA
#define MOTOR3_OUT_CW   GPIO_Pin_13
#define MOTOR3_OUT_CCW  GPIO_Pin_15
//モーター4
#define MOTOR4_OUT_PIN  GPIOA
#define MOTOR4_OUT_CW   GPIO_Pin_12
#define MOTOR4_OUT_CCW  GPIO_Pin_14
//モーター5
#define MOTOR5_OUT_PIN  GPIOC
#define MOTOR5_OUT_CW   GPIO_Pin_9
#define MOTOR5_OUT_CCW  GPIO_Pin_7
//モーター6
#define MOTOR6_OUT_PIN  GPIOC
#define MOTOR6_OUT_CW   GPIO_Pin_8
#define MOTOR6_OUT_CCW  GPIO_Pin_6
*/




void Init_TIM_pwm(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	 TIM_OCInitTypeDef TIM_OCInitStructure;


	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	 //GPIO pin configuration
	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_Init(GPIOD,&GPIO_InitStructure);

	 //Time base configuration
	 TIM_TimeBaseStructure.TIM_Period = (84*1000*1000)/100000-1;
	 TIM_TimeBaseStructure.TIM_Prescaler = 0;
	 TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	 TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	 TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);

	 //Output Compare Toggle Mode configuration
	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

	 //TIM_OCInitStructure.TIM_Pulse = 5000;
	 TIM_OC1Init(TIM4,&TIM_OCInitStructure);
	 TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Disable);
	 TIM_OC2Init(TIM4,&TIM_OCInitStructure);
	 TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Disable);
	 TIM_OC3Init(TIM4,&TIM_OCInitStructure);
	 TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Disable);
	 TIM_OC4Init(TIM4,&TIM_OCInitStructure);
	 TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Disable);

	 GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	 GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	 GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
	 GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);

	 TIM_Cmd(TIM4,ENABLE);
	 TIM_ARRPreloadConfig(TIM4,ENABLE);
 
}
/*
void Init_Motor(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;

  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;

  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);


}

void Motor1_Out(int duty)
{
  if(duty == 999){
      GPIO_SetBits(MOTOR1_OUT_PIN, MOTOR1_OUT_CW | MOTOR1_OUT_CCW);
  }else if(duty>0){
      GPIO_SetBits(MOTOR1_OUT_PIN, MOTOR1_OUT_CW);
      GPIO_ResetBits(MOTOR1_OUT_PIN, MOTOR1_OUT_CCW);
  }else if(duty<0){
      GPIO_SetBits(MOTOR1_OUT_PIN, MOTOR1_OUT_CCW);
      GPIO_ResetBits(MOTOR1_OUT_PIN, MOTOR1_OUT_CW);
  }else if(duty==0){
      GPIO_ResetBits(MOTOR1_OUT_PIN, MOTOR1_OUT_CW | MOTOR1_OUT_CCW);
  }
  if(duty < 0){
      duty *= -1;
  }
  if(duty > 100){
      duty = 100;
  }

  TIM4->CCR4 = (int)(duty*665/100);
}
void Motor2_Out(int duty)
{
  if(duty == 999){
      GPIO_SetBits(MOTOR2_OUT_PIN, MOTOR2_OUT_CW | MOTOR2_OUT_CCW);
  }else if(duty>0){
      GPIO_SetBits(MOTOR2_OUT_PIN, MOTOR2_OUT_CW);
      GPIO_ResetBits(MOTOR2_OUT_PIN, MOTOR2_OUT_CCW);
  }else if(duty<0){
      GPIO_SetBits(MOTOR2_OUT_PIN, MOTOR2_OUT_CCW);
      GPIO_ResetBits(MOTOR2_OUT_PIN, MOTOR2_OUT_CW);
  }else if(duty==0){
      GPIO_ResetBits(MOTOR2_OUT_PIN, MOTOR2_OUT_CW | MOTOR2_OUT_CCW);
  }
  if(duty < 0){
      duty *= -1;
  }
  if(duty > 100){
      duty = 100;
  }

  TIM4->CCR3 = (int)(duty*665/100);
}
void Motor3_Out(int duty)
{
  if(duty == 999){
      GPIO_SetBits(MOTOR3_OUT_PIN, MOTOR3_OUT_CW | MOTOR3_OUT_CCW);
  }else if(duty>0){
      GPIO_SetBits(MOTOR3_OUT_PIN, MOTOR3_OUT_CW);
      GPIO_ResetBits(MOTOR3_OUT_PIN, MOTOR3_OUT_CCW);
  }else if(duty<0){
      GPIO_SetBits(MOTOR3_OUT_PIN, MOTOR3_OUT_CCW);
      GPIO_ResetBits(MOTOR3_OUT_PIN, MOTOR3_OUT_CW);
  }else if(duty==0){
      GPIO_ResetBits(MOTOR3_OUT_PIN, MOTOR3_OUT_CW | MOTOR3_OUT_CCW);
  }
  if(duty < 0){
      duty *= -1;
  }
  if(duty > 100){
      duty = 100;
  }

  TIM1->CCR4 = (int)(duty*239/100);
}
void Motor4_Out(int duty)
{
  if(duty == 999){
      GPIO_SetBits(MOTOR4_OUT_PIN, MOTOR4_OUT_CW | MOTOR4_OUT_CCW);
  }else if(duty>0){
      GPIO_SetBits(MOTOR4_OUT_PIN, MOTOR4_OUT_CW);
      GPIO_ResetBits(MOTOR4_OUT_PIN, MOTOR4_OUT_CCW);
  }else if(duty<0){
      GPIO_SetBits(MOTOR4_OUT_PIN, MOTOR4_OUT_CCW);
      GPIO_ResetBits(MOTOR4_OUT_PIN, MOTOR4_OUT_CW);
  }else if(duty==0){
      GPIO_ResetBits(MOTOR4_OUT_PIN, MOTOR4_OUT_CW | MOTOR4_OUT_CCW);
  }
  if(duty < 0){
      duty *= -1;
  }
  if(duty > 100){
      duty = 100;
  }

  TIM1->CCR3 = (int)(duty*239/100);
}
void Motor5_Out(int duty)
{
  if(duty == 999){
      GPIO_SetBits(MOTOR5_OUT_PIN, MOTOR5_OUT_CW | MOTOR5_OUT_CCW);
  }else if(duty>0){
      GPIO_SetBits(MOTOR5_OUT_PIN, MOTOR5_OUT_CW);
      GPIO_ResetBits(MOTOR5_OUT_PIN, MOTOR5_OUT_CCW);
  }else if(duty<0){
      GPIO_SetBits(MOTOR5_OUT_PIN, MOTOR5_OUT_CCW);
      GPIO_ResetBits(MOTOR5_OUT_PIN, MOTOR5_OUT_CW);
  }else if(duty==0){
      GPIO_ResetBits(MOTOR5_OUT_PIN, MOTOR5_OUT_CW | MOTOR5_OUT_CCW);
  }
  if(duty < 0){
      duty *= -1;
  }
  if(duty > 100){
      duty = 100;
  }

  TIM1->CCR2 = (int)(duty*239/100);
}
void Motor6_Out(int duty)
{
  if(duty == 999){
      GPIO_SetBits(MOTOR6_OUT_PIN, MOTOR6_OUT_CW | MOTOR6_OUT_CCW);
  }else if(duty>0){
      GPIO_SetBits(MOTOR6_OUT_PIN, MOTOR6_OUT_CW);
      GPIO_ResetBits(MOTOR6_OUT_PIN, MOTOR6_OUT_CCW);
  }else if(duty<0){
      GPIO_SetBits(MOTOR6_OUT_PIN, MOTOR6_OUT_CCW);
      GPIO_ResetBits(MOTOR6_OUT_PIN, MOTOR6_OUT_CW);
  }else if(duty==0){
      GPIO_ResetBits(MOTOR6_OUT_PIN, MOTOR6_OUT_CW | MOTOR6_OUT_CCW);
  }
  if(duty < 0){
      duty *= -1;
  }
  if(duty > 100){
      duty = 100;
  }

  TIM1->CCR1 = (int)(duty*239/100);
}


void Motor_Left_Right(int duty_L, int duty_R)
{
  static int    direct_shift_L = 0,
                direct_shift_R = 0,
                duty_L_old = 0,
                duty_R_old = 0;
  if(duty_L_old)

  Motor1_Out(duty_L);
  Motor2_Out(duty_R);



  if(duty_L > 0){
      duty_L_old = 1;
  }else if(duty_L < 0){
      duty_L_old = -1;
  }else if(duty_L == 0){
      duty_L_old = 0;
  }else if(duty_L == 999){
      duty_L_old = 999;
  }

}
*/
