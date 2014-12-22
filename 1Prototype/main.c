#include <math.h>
#include <stdio.h>

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

/*マイコンの設定*/
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
	Init_SysTick(0.001);					//1ms割り込み
	//Init_ADC1(POTENTIO);
	//Init_PWM(RIGHT_TIRE_PWMSET, 10000);			//左タイヤモーター
	//Init_PWM(LEFT_TIRE_PWMSET, 10000);			//右タイヤモーター
	//Init_PWM(BACK_TIRE_PWMSET, 10000);			//後ろタイヤモーター
	Init_PWM(ARM_PWMSET, 50);						//アームモーター
	//Init_PWM(ARM_PWMSET, 100);						//アームモーター
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

		/*USART_InitStructure.USART_BaudRate 				= 115200;							//ボーレートの設定
		USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;				//ビット長
		USART_InitStructure.USART_StopBits 				= USART_StopBits_1;					//ストップビットの長さ
		USART_InitStructure.USART_Parity 				= USART_Parity_Even;				//パリティの有無 12/16サーボ使用のため偶数に設定
		USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;	//ハードウェアフロー制御の有無
		USART_InitStructure.USART_Mode 					= USART_Mode_Tx;	//送信受信の選択
		USART_Init(USART3, &USART_InitStructure);											//USARTの設定
		USART_Cmd(USART3, ENABLE);*/
		USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);

		for(i=0; i<3; i++){
			//transmit_usart2_c(tx[i]);		//コマンド1バイトずつ送信
		}

		transmit_usart2_c(0x80);
		transmit_usart2_c(0x3A);
		transmit_usart2_c(0x4C);

		/*USART_InitStructure.USART_BaudRate 				= 115200;							//ボーレートの設定
		USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;				//ビット長
		USART_InitStructure.USART_StopBits 				= USART_StopBits_1;					//ストップビットの長さ
		USART_InitStructure.USART_Parity 				= USART_Parity_Even;				//パリティの有無 12/16サーボ使用のため偶数に設定
		USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;	//ハードウェアフロー制御の有無
		USART_InitStructure.USART_Mode 					= USART_Mode_Rx;	//送信受信の選択
		USART_Init(USART3, &USART_InitStructure);											//USARTの設定
		USART_Cmd(USART3, ENABLE);*/
		//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

		for(i=0; i<3; i++){
			rx[i] = receive();			//モーターからの返値を受け取り、rxに代入
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
	  int pos, r_pos; // セットするポジションデータと返ってきたポジションデータ
	  int i, id; // idには適当な数値を入れておくこと
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
			//pos = (pos == 5000 ? 10000 : 5000); // ポジションデータを切り替える
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
	//構造体変数を宣言
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;

	//モジュールストップ状態の解除
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_PeriphClock_USART(USARTx);
	//GPIOの設定
	Init_port(GPIO_Mode_AF,GPIOx_TX,pin_TX,GPIO_PuPd_NOPULL,GPIO_OType_PP);
	Init_port(GPIO_Mode_AF,GPIOx_RX,pin_RX,GPIO_PuPd_NOPULL,GPIO_OType_PP);

	//PINをオルタネィテブファンクションに割り当て

	GPIO_PinAFConfig(GPIOx_TX, Pin_select_source(pin_TX), GPIO_af_USART_select(USARTx));//USART1 TX/PB6
	GPIO_PinAFConfig(GPIOx_RX, Pin_select_source(pin_RX), GPIO_af_USART_select(USARTx));//USART1 RX/PB7


	//USART1の設定
	USART_InitStructure.USART_BaudRate 				= baudrate;							//ボーレートの設定
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;				//ビット長
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;					//ストップビットの長さ
	USART_InitStructure.USART_Parity 				= USART_Parity_Even;				//パリティの有無 12/16サーボ使用のため偶数に設定
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;	//ハードウェアフロー制御の有無
	USART_InitStructure.USART_Mode 					=USART_Mode_Tx ;	//送信受信の選択
	USART_Init(USARTx, &USART_InitStructure);											//USARTの設定
	USART_Cmd(USARTx, ENABLE);															//USART周辺回路の有効化
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);										//USART周辺回路の割込み有効化

	//割り込み設定
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);							//優先度のビット設定
	NVIC_InitStructure.NVIC_IRQChannel 						= USART_irqn_select(USARTx);	//有効化するIRQチャンネルの指定
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 2;			//割り込みの優先順位（グループ）の指定。0が最優先
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;			//割り込みの優先順位(サブ)の指定。0が最優先
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;		//割り込みの有効化
	NVIC_Init(&NVIC_InitStructure);											//割り込み設定
}
