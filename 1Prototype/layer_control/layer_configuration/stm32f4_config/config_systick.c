#include "config_systick.h"

unsigned int 	g_time = 0,
						g_serial_time = 0,
						g_debug_time = 0,
						g_arm_time = 0,
						g_micro_time = 0;

/******************************************************************************
*	�^�C�g�� �F ���荞�݃n���h���@�֐��ꏊ�Œ�
*	  �֐��� �F SysTick_Handler
*	  �߂�l �F void�^ 
*	   ����1 �F void�^  
*	  �쐬�� �F ������		
*	  �쐬�� �F 2014/11/10
******************************************************************************/
void SysTick_Handler(void){
	//�C��ms���Ɋ��荞��ŁA1�J�E���g����@�P��:[ms]
	g_time ++;
	g_debug_time ++;
	g_serial_time ++;
	g_arm_time ++;
}

/******************************************************************************
*	�^�C�g�� �F ���荞�݃^�C�}�ݒ�֐�
*	  �֐��� �F Init_SysTick
*	  �߂�l �F void�^ �Ȃ�
*	   ����1 �F float�^ time  ���荞�ݎ�����ݒ�
*	  �쐬�� �F ������
*	  �쐬�� �F 2014/11/10
******************************************************************************/
void Init_SysTick(float time){
	//systick���荞�݂̐ݒ�	time�̒P��:[s]
	SystemCoreClockUpdate();									//SystemCoreClock�̍X�V
	NVIC_SetPriority(SysTick_IRQn,1);						//���荞�ݗD��x�̐ݒ�		�D��x��1��
	if(SysTick_Config(SystemCoreClock*time)){		//systick�ɂ�銄�荞�ݎ�����ݒ�
						//���s������@�������ݎ��R
	}
}

/******************************************************************************
*	�^�C�g�� �F timer2���荞�ݐݒ�
*	  �֐��� �F TIM2_IRQHandler
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{�z��
*	  �쐬�� �F 2014/11/11
******************************************************************************/
void TIM2_IRQHandler(void)
{
	g_micro_time ++;
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void Init_micro_interrupt(TIM_TypeDef *tim)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;

	RCC_PeriphClock_TIM(tim);//�N���b�N����

	//TIM ����
	TIM_TimeBaseStructure.TIM_Period = 84 - 1;
	//����
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(tim, &TIM_TimeBaseStructure);

	TIM_ITConfig(tim, TIM_IT_Update, ENABLE);
	TIM_Cmd(tim, ENABLE);
	//���荞��
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
