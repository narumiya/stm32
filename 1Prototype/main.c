#include <math.h>

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

#include "define.h"
#include "motor_define.h"
#include "my_standard_io.h"
#include "transmit.h"
#include "receive.h"

void all_setup(void)
{
	SystemInit();
	Init_SysTick(0.001);					//1ms割り込み
	//Init_ADC1(POTENTIO);
	Init_PWM(RIGHT_TIRE_PWMSET, 10000);			//左タイヤモーター
	Init_PWM(LEFT_TIRE_PWMSET, 10000);			//右タイヤモーター
	Init_PWM(BACK_TIRE_PWMSET, 10000);			//後ろタイヤモーター
	Init_PWM(ARM_PWMSET, 10000);						//アームモーター
	Init_USART(USART2, 115200, GPIOD, GPIO_Pin_5, GPIOD, GPIO_Pin_6);
	Init_USART(USART3, 115200, GPIOD, GPIO_Pin_8, GPIOD, GPIO_Pin_9);
}

int set_position(unsigned char id, int position)
{
	unsigned char tx[3];
	unsigned char rx[3];
	int i = 0;
	int data = 0;

	if(0 < id && id < 31){
		tx[0] = 0x80 | id;														//CMD=0b100XXXXX
		tx[1] = (unsigned char)(position >> 7 & 0x7F);		//POS_H
		tx[2] = (unsigned char)(position & 0x7F);				//POS_L

		for(i=0; i<3; i++){
			transmit_usart2_c(tx[i]);		//コマンド1バイトずつ送信
		}

		for(i=0; i<3; i++){
			rx[i] = receive_usart2_c();			//モーターからの返値を受け取り、rxに代入
		}

		data = (int)(rx[1] & 0x7F);
		data = (data << 7) + (int)rx[2];
	}

	return data;
}

int main(void)
{
	while(1){
		if(count_time(0) >= INTERRUPT_TIME){
			reset_count_time(0);

		}
	}
}
