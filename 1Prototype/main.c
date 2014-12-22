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

#include "define.h"
#include "motor_define.h"
#include "my_standard_io.h"
#include "transmit.h"
#include "receive.h"

void Init_USART_new(USART_TypeDef *USARTx,unsigned int baudrate, GPIO_TypeDef *GPIOx_TX ,uint16_t pin_TX, GPIO_TypeDef *GPIOx_RX, uint16_t pin_RX);

void all_setup(void)
{
	SystemInit();
	Init_SysTick(0.001);					//1ms���荞��
	//Init_ADC1(POTENTIO);
	//Init_PWM(RIGHT_TIRE_PWMSET, 10000);			//���^�C�����[�^�[
	//Init_PWM(LEFT_TIRE_PWMSET, 10000);			//�E�^�C�����[�^�[
	//Init_PWM(BACK_TIRE_PWMSET, 10000);			//���^�C�����[�^�[
	Init_PWM(ARM_PWMSET, 50);						//�A�[�����[�^�[
	//Init_PWM(ARM_PWMSET, 100);						//�A�[�����[�^�[
	//Init_USART_new(USART2, 115200, GPIOD, GPIO_Pin_5, GPIOD, GPIO_Pin_6);
	//Init_USART(USART2, 115200, GPIOD, GPIO_Pin_5, GPIOD, GPIO_Pin_6);
	//Init_USART(USART3, 115200, GPIOD, GPIO_Pin_8, GPIOD, GPIO_Pin_9);
	 Init_port(GPIO_Mode_OUT, GPIOD, GPIO_Pin_14 | GPIO_Pin_15, GPIO_PuPd_UP, GPIO_OType_PP);//LED
	//Init_usb();
}

int set_position(unsigned char id, int position)
{
	USART_InitTypeDef 	USART_InitStructure;

	unsigned char tx[3];
	unsigned char rx[3];
	int i = 0;
	int data = 0;

	if(0 <= id && id <= 31){
		tx[0] = 0x80 | id;														//CMD=0b100XXXXX
		tx[1] = (unsigned char)(position >> 7 & 0x7F);		//POS_H
		tx[2] = (unsigned char)(position & 0x7F);			//POS_L

		/*USART_InitStructure.USART_BaudRate 				= 115200;							//�{�[���[�g�̐ݒ�
		USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;				//�r�b�g��
		USART_InitStructure.USART_StopBits 				= USART_StopBits_1;					//�X�g�b�v�r�b�g�̒���
		USART_InitStructure.USART_Parity 				= USART_Parity_Even;				//�p���e�B�̗L�� 12/16�T�[�{�g�p�̂��ߋ����ɐݒ�
		USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;	//�n�[�h�E�F�A�t���[����̗L��
		USART_InitStructure.USART_Mode 					= USART_Mode_Tx;	//���M��M�̑I��
		USART_Init(USART3, &USART_InitStructure);											//USART�̐ݒ�
		USART_Cmd(USART3, ENABLE);*/
		USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);

		for(i=0; i<3; i++){
			//transmit_usart2_c(tx[i]);		//�R�}���h1�o�C�g�����M
		}

		transmit_usart2_c(0x80);
		transmit_usart2_c(0x3A);
		transmit_usart2_c(0x4C);

		/*USART_InitStructure.USART_BaudRate 				= 115200;							//�{�[���[�g�̐ݒ�
		USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;				//�r�b�g��
		USART_InitStructure.USART_StopBits 				= USART_StopBits_1;					//�X�g�b�v�r�b�g�̒���
		USART_InitStructure.USART_Parity 				= USART_Parity_Even;				//�p���e�B�̗L�� 12/16�T�[�{�g�p�̂��ߋ����ɐݒ�
		USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;	//�n�[�h�E�F�A�t���[����̗L��
		USART_InitStructure.USART_Mode 					= USART_Mode_Rx;	//���M��M�̑I��
		USART_Init(USART3, &USART_InitStructure);											//USART�̐ݒ�
		USART_Cmd(USART3, ENABLE);*/
		//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

		for(i=0; i<3; i++){
			rx[i] = receive();			//���[�^�[����̕Ԓl���󂯎��Arx�ɑ��
		}

		data = (int)(rx[1] & 0x7F);
		data = (data << 7) + (int)rx[2];
	}

	return data;
}

void wait(float m_sec){
	reset_count_time(0);
	while(1){
		if(count_time(0) >= m_sec){
			reset_count_time(0);
			break;
		}
	}
}

int main(void)
{
	  int pos, r_pos; // �Z�b�g����|�W�V�����f�[�^�ƕԂ��Ă����|�W�V�����f�[�^
	  int i, id; // id�ɂ͓K���Ȑ��l�����Ă�������
	  int a=0;
	 int  task = 0;
	 char str = 123;
	 float offset;

	  all_setup();
	  while(1){
		  /*Set_duty(BOX8PWM, 0.01);
		  wait(500);
		  Set_duty(BOX8PWM, 0.02);
	      wait(500);
	      Set_duty(BOX8PWM, 0.03);
		  wait(500);
		  Set_duty(BOX8PWM, 0.02);*/


		  Set_duty(BOX8PWM, 0.035);
		  wait(20000);
		  Set_duty(BOX8PWM, 0.075);
		  wait(20000);

		  /*for(offset = 0.035; offset<0.1115; offset += 0.008) {
	           Set_duty(BOX8PWM, offset); // servo position determined by a pulsewidth between 1-2ms
	            wait(250);
	            if(a==0){

	            	GPIO_SetBits(GPIOD, GPIO_Pin_14);
	            	a=1;
	            }else if(a==1){
	            	GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	            	a=0;
	            }
	        }*/
		 /* wait(1000);
			if(a==0){
				GPIO_SetBits(GPIOD, GPIO_Pin_14);
				//r_pos = set_position(0, 4500);
				Set_duty(BOX8PWM, 0.01);
				a=1;
			}else if(a==1){
				GPIO_ResetBits(GPIOD, GPIO_Pin_14);
				//r_pos = set_position(0, 5000);
				Set_duty(BOX8PWM, 0.02);
				a=0;
			}*/
	  }
	/*  while(1){

		if(count_time(0) >= 1000){
			reset_count_time(0);
			//pos = (pos == 5000 ? 10000 : 5000); // �|�W�V�����f�[�^��؂�ւ���
			//r_pos = set_position(0, 4500);
			//Set_duty(BOX8PWM, 0.2);
			if(a==0){
				GPIO_SetBits(GPIOD, GPIO_Pin_14);
				//r_pos = set_position(0, 4500);
				Set_duty(BOX8PWM, 0.01);
				a=1;
			}else if(a==1){
				GPIO_ResetBits(GPIOD, GPIO_Pin_14);
				//r_pos = set_position(0, 5000);
				Set_duty(BOX8PWM, 0.02);
				a=2;
			}else if(a==2){
				GPIO_SetBits(GPIOD, GPIO_Pin_14);
				//r_pos = set_position(0, 5000);
				Set_duty(BOX8PWM, 0.03);
				a=3;
			}else if(a==3){
				GPIO_ResetBits(GPIOD, GPIO_Pin_14);
				//r_pos = set_position(0, 5000);
				Set_duty(BOX8PWM, 0.04);
				a=4;
			}else if(a==4){
				GPIO_SetBits(GPIOD, GPIO_Pin_14);
				//r_pos = set_position(0, 5000);
				Set_duty(BOX8PWM, 0.05);
				a=5;
			}else if(a==5){
				GPIO_ResetBits(GPIOD, GPIO_Pin_14);
				//r_pos = set_position(0, 5000);
				Set_duty(BOX8PWM, 0.06);
				a=6;
			}else if(a==6){
				GPIO_SetBits(GPIOD, GPIO_Pin_14);
				//r_pos = set_position(0, 5000);
				Set_duty(BOX8PWM, 0.07);
				a=7;
			}else if(a==7){
				GPIO_ResetBits(GPIOD, GPIO_Pin_14);
				//r_pos = set_position(0, 5000);
				Set_duty(BOX8PWM, 0.08);
				a=8;
			}else if(a==8){
				GPIO_SetBits(GPIOD, GPIO_Pin_14);
				//r_pos = set_position(0, 5000);
				Set_duty(BOX8PWM, 0.09);
				a=9;
			}else if(a==9){
				GPIO_ResetBits(GPIOD, GPIO_Pin_14);
				//r_pos = set_position(0, 5000);
				Set_duty(BOX8PWM, 0.1);
				a=10;
			}else if(a==10){
				GPIO_SetBits(GPIOD, GPIO_Pin_14);
				//r_pos = set_position(0, 5000);
				Set_duty(BOX8PWM, 0.12);
				a=0;
			}
		}
		*/  //Set_duty(BOX8PWM, 1);
		//Set_duty(BOX8PWM, 0.1);
		//r_pos = set_position(0, 4500);
			//transmit_usart3_s("123");
		 // f_print(PC, "pos", r_pos);
		  //put_enter(PC);
		  //Set_duty(BOX8PWM, 0.5);
		 /* if(task ==0){
			  Set_duty(BOX8PWM, 0.5);
			  if(count_time(0) >= 150){
				  reset_count_time(0);
				  task = 1;
			  }
		  }else if(task == 1){

		  }*/

		  //transmit_usart2_c(str);
/*
  }*/
	  return 0;
}

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
