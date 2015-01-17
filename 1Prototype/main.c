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
#include "can.h"

#include "define.h"
//#include "motor_define.h"
#include "motor.h"
#include "my_standard_io.h"
#include "transmit.h"
#include "receive.h"
#include "arm_operate.h"

#define SERVO_PWM			MOTOR_7_PWM
#define SERVO_TIM_CH	MOTOR_7_TIM_CH
#define SERVO_PWM_SET		MOTOR_7_PWM_SET

//void Init_USART_new(USART_TypeDef *USARTx,unsigned int baudrate, GPIO_TypeDef *GPIOx_TX ,uint16_t pin_TX, GPIO_TypeDef *GPIOx_RX, uint16_t pin_RX);

CanRxMsg	can_rx_flame;
CanTxMsg	can_tx_flame;

PS3_Controller_t	PS3;

void CAN1_RX0_IRQHandler(void)
{
	if(CAN_GetITStatus(CAN1, CAN_IT_FMP0)){//新しいメッセージを受信ししたときに呼び出される
		CAN_Receive(CAN1, CAN_FIFO0, &can_rx_flame);//受信
		//receive_can_att();
		receive_data(can_rx_flame.Data, &PS3);
		Set_GPIO_output(GPIOD, GPIO_Pin_14, HIGH);
	}
}


void servo_move(float degree)
{
	static float old_duty = 0;
	float duty = 0.00;

	if(0 <= degree && degree <= 270){
		duty = ( 0.04 / 135.0 ) * degree + 0.035;
	}else{
		duty = old_duty;
	}

	old_duty = duty;

	Set_duty(SERVO_TIM_CH, duty);
}


void all_setup(void)
{
	SystemInit();
	Init_SysTick(0.001);					//1ms割り込み
	//CAN_Configuration();
	//Init_ADC1(POTENTIO);
	//Init_PWM(RIGHT_TIRE_PWMSET, 10000);			//左タイヤモーター
	//Init_PWM(LEFT_TIRE_PWMSET, 10000);			//右タイヤモーター
	//Init_PWM(BACK_TIRE_PWMSET, 10000);			//後ろタイヤモーター
	//Init_PWM(ARM_PWMSET, 50);								//アームモーター
	//Init_PWM(ARM_PWMSET, 100);							//アームモーター
	//Init_PWM(RIGHT_ARM1_PWM_SET, 10000);								//アームモーター
	//Init_PWM(RIGHT_ARM2_PWM_SET, 10000);							//アームモーター
	Init_PWM(SERVO_PWM_SET, 50);							//サーボ
	//Init_USART_new(USART2, 115200, GPIOD, GPIO_Pin_5, GPIOD, GPIO_Pin_6);
	Init_USART(USART2, 115200, GPIOD, GPIO_Pin_5, GPIOD, GPIO_Pin_6);
	//Init_USART(USART3, 115200, GPIOD, GPIO_Pin_8, GPIOD, GPIO_Pin_9);
	//Init_usb();

	Init_port(GPIO_Mode_OUT, GPIOD, GPIO_Pin_14 | GPIO_Pin_15, GPIO_PuPd_UP, GPIO_OType_PP);//LED
	Init_port(GPIO_Mode_IN, GPIOA, GPIO_Pin_0, GPIO_PuPd_NOPULL, GPIO_OType_PP);//switch
	Init_port(GPIO_Mode_OUT, AIR1, GPIO_PuPd_NOPULL, GPIO_OType_PP);

	Init_port(GPIO_Mode_OUT, RIGHT_ARM1_PUSH, GPIO_PuPd_NOPULL,GPIO_OType_PP);
	Init_port(GPIO_Mode_OUT, RIGHT_ARM1_PULL, GPIO_PuPd_NOPULL,GPIO_OType_PP);
	Init_port(GPIO_Mode_OUT, RIGHT_ARM2_PUSH, GPIO_PuPd_NOPULL,GPIO_OType_PP);
	Init_port(GPIO_Mode_OUT, RIGHT_ARM2_PULL, GPIO_PuPd_NOPULL,GPIO_OType_PP);
}

int main(void)
{
	short start = 0;
	short a=0;
	float duty=0;

	all_setup();

	servo_move(INIT_ANGLE);
	reset_count_time(0);

	while(1){
		if(count_time(0) >= 800){//INTERRUPT_TIME_MS){
			reset_count_time(0);
			if(a >= 270){
				a=0;
			}
			servo_move(a);
			a+= 10;

			/*if(a == 0){
				duty=servo_move(0);
				//Set_duty(SERVO_TIM_CH, 0.035);
				a=1;
				Set_GPIO_output(GPIOD,GPIO_Pin_14, HIGH);
			}else if(a==1){
				duty=servo_move(270);
				//Set_duty(SERVO_TIM_CH, 0.115);
				a=0;
				Set_GPIO_output(GPIOD,GPIO_Pin_14, LOW);
			}else if(a==2){
				//servo_move(90);
				a=3;
				Set_duty(SERVO_TIM_CH, 0.115);
				Set_GPIO_output(GPIOD,GPIO_Pin_14, HIGH);
			}else if(a==3){
				//servo_move(45);
				a=0;
				Set_duty(SERVO_TIM_CH, 0.075);
				Set_GPIO_output(GPIOD,GPIO_Pin_14, LOW);
			}*/

			/*if(PS3.Start == ON){
				start = ON;
			}
			if(start == ON){
				serve_short(SERVE_START_BOTTUN);

			}//start*/
		}//INTERRUPT_TIME_MS
		f_print(PC, "task",a);
		f_print(PC, "duty",duty);
		f_print(PC,"time",count_time(0));
		put_enter(PC);
	}//while
	return 0;
}

/*
int main(void)
{
	char str[8];
	int i = 0;
	int size =0;
	int send_int = 12;
	short send_short = 30;
	float send_float = 23.67;
	double send_double = 12.34;

	all_setup();

	while(1){
		sprintf(str,"A%f#", send_float);
		can_tx_flame.StdId 	= 0x00F;			//ID 11bit 0～0x7FF
		can_tx_flame.ExtId		= 0x0;				//拡張フレームID 28bit 0～0x1FFFFFFF
		can_tx_flame.IDE 		= 0;					//拡張フレームIDを使う場合1
		can_tx_flame.RTR		= 0;					//データフレーム:0 リモートフレーム:1
		size=0;
		for(i=0; str[i]!='\0'; i++){
			size ++;
		}
		can_tx_flame.DLC		= 8;					//送信するデータフィールドのバイト数
		for(i=0;i<=7; i++){
			can_tx_flame.Data[i]	= str[i];			//送信するデータフィールド
		}
		CAN_Transmit(CAN1, &can_tx_flame);


    	//while(0 == CAN_MessagePending(CAN1, CAN_FIFO0));
		//CAN_Receive(CAN1, CAN_FIFO0, &can_rx_flame);//受信
		if(count_time(0) >= INTERRUPT_TIME_MS ){
			reset_count_time(0);

			f_print(PC, "tx", can_tx_flame.Data[0]);
			f_print(PC, "tx", can_tx_flame.Data[1]);
			f_print(PC, "tx", can_tx_flame.Data[2]);
			f_print(PC, "tx", can_tx_flame.Data[3]);
			f_print(PC, "tx", can_tx_flame.Data[4]);
			f_print(PC, "tx", can_tx_flame.Data[5]);
			f_print(PC, "tx", can_tx_flame.Data[6]);
			f_print(PC, "tx", can_tx_flame.Data[7]);
			f_print(PC, "rx", can_rx_flame.Data[0]);
			f_print(PC, "rx", can_rx_flame.Data[1]);
			f_print(PC, "rx", can_rx_flame.Data[2]);
			f_print(PC, "rx", can_rx_flame.Data[3]);
			f_print(PC, "rx", can_rx_flame.Data[4]);
			f_print(PC, "rx", can_rx_flame.Data[5]);
			f_print(PC, "rx", can_rx_flame.Data[6]);
			f_print(PC, "rx", can_rx_flame.Data[7]);
			f_print(PC, "rx", get_AtoZ_value(0));
			put_enter(PC);
		  }
	  }
	  return 0;
}
*/
/*
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
*/
