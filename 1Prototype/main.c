#include <math.h>
#include <stdio.h>

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

/*�}�C�R���̐ݒ�*/
#include "config_adc.h"
#include "config_encoder.h"
#include "config_port.h"
#include "config_pwm.h"
#include "config_systick.h"
#include "config_usart.h"
#include "name_converter.h"
#include "config_usb.h"
#include "can.h"

#include "define.h"
#include "motor_define.h"
#include "my_standard_io.h"
#include "transmit.h"
#include "receive.h"

//void Init_USART_new(USART_TypeDef *USARTx,unsigned int baudrate, GPIO_TypeDef *GPIOx_TX ,uint16_t pin_TX, GPIO_TypeDef *GPIOx_RX, uint16_t pin_RX);

void all_setup(void)
{
	SystemInit();
	Init_SysTick(0.001);					//1ms���荞��
	CAN_Configuration();
	//Init_ADC1(POTENTIO);
	//Init_PWM(RIGHT_TIRE_PWMSET, 10000);			//���^�C�����[�^�[
	//Init_PWM(LEFT_TIRE_PWMSET, 10000);			//�E�^�C�����[�^�[
	//Init_PWM(BACK_TIRE_PWMSET, 10000);			//���^�C�����[�^�[
	Init_PWM(ARM_PWMSET, 50);								//�A�[�����[�^�[
	//Init_PWM(ARM_PWMSET, 100);							//�A�[�����[�^�[
	//Init_USART_new(USART2, 115200, GPIOD, GPIO_Pin_5, GPIOD, GPIO_Pin_6);
	//Init_USART(USART2, 115200, GPIOD, GPIO_Pin_5, GPIOD, GPIO_Pin_6);
	//Init_USART(USART3, 115200, GPIOD, GPIO_Pin_8, GPIOD, GPIO_Pin_9);
	//Init_usb();

	 Init_port(GPIO_Mode_OUT, GPIOD, GPIO_Pin_14 | GPIO_Pin_15, GPIO_PuPd_UP, GPIO_OType_PP);//LED
}

int main(void)
{
	CanRxMsg	can_rx_flame;
	CanTxMsg	can_tx_flame;

	all_setup();

	while(1){
		if(count_time(0) >= INTERRUPT_TIME_MS){
			reset_count_time(0);

			can_tx_flame.StdId 	= 0x00F;			//ID 11bit 0�`0x7FF
			can_tx_flame.ExtId		= 0x0;				//�g���t���[��ID 28bit 0�`0x1FFFFFFF
			can_tx_flame.IDE 		= 0;					//�g���t���[��ID���g���ꍇ1
			can_tx_flame.RTR		= 0;					//�f�[�^�t���[��:0 �����[�g�t���[��:1
			can_tx_flame.DLC		= 1;					//���M����f�[�^�t�B�[���h�̃o�C�g��
			can_tx_flame.Data[0]	= 0xAA;			//���M����f�[�^�t�B�[���h
			CAN_Transmit(CAN1, &can_tx_flame);

		  }
	  }

	  return 0;
}

/*
void Init_USART_new(USART_TypeDef *USARTx,unsigned int baudrate, GPIO_TypeDef *GPIOx_TX ,uint16_t pin_TX, GPIO_TypeDef *GPIOx_RX, uint16_t pin_RX){
	//�\���̕ϐ���錾
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;

	//���W���[���X�g�b�v��Ԃ̉���
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_PeriphClock_USART(USARTx);
	//GPIO�̐ݒ�
	Init_port(GPIO_Mode_AF,GPIOx_TX,pin_TX,GPIO_PuPd_NOPULL,GPIO_OType_PP);
	Init_port(GPIO_Mode_AF,GPIOx_RX,pin_RX,GPIO_PuPd_NOPULL,GPIO_OType_PP);

	//PIN���I���^�l�B�e�u�t�@���N�V�����Ɋ��蓖��

	GPIO_PinAFConfig(GPIOx_TX, Pin_select_source(pin_TX), GPIO_af_USART_select(USARTx));//USART1 TX/PB6
	GPIO_PinAFConfig(GPIOx_RX, Pin_select_source(pin_RX), GPIO_af_USART_select(USARTx));//USART1 RX/PB7


	//USART1�̐ݒ�
	USART_InitStructure.USART_BaudRate 				= baudrate;							//�{�[���[�g�̐ݒ�
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;				//�r�b�g��
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;					//�X�g�b�v�r�b�g�̒���
	USART_InitStructure.USART_Parity 				= USART_Parity_Even;				//�p���e�B�̗L�� 12/16�T�[�{�g�p�̂��ߋ����ɐݒ�
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;	//�n�[�h�E�F�A�t���[����̗L��
	USART_InitStructure.USART_Mode 					=USART_Mode_Tx ;	//���M��M�̑I��
	USART_Init(USARTx, &USART_InitStructure);											//USART�̐ݒ�
	USART_Cmd(USARTx, ENABLE);															//USART���Ӊ�H�̗L����
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);										//USART���Ӊ�H�̊����ݗL����

	//���荞�ݐݒ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);							//�D��x�̃r�b�g�ݒ�
	NVIC_InitStructure.NVIC_IRQChannel 						= USART_irqn_select(USARTx);	//�L��������IRQ�`�����l���̎w��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 2;			//���荞�݂̗D�揇�ʁi�O���[�v�j�̎w��B0���ŗD��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;			//���荞�݂̗D�揇��(�T�u)�̎w��B0���ŗD��
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;		//���荞�݂̗L����
	NVIC_Init(&NVIC_InitStructure);											//���荞�ݐݒ�
}
*/
