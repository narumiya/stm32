#include "init_system_stm32f4.h"
#include <math.h>
#include "select_port_on_module.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

#include "misc.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_crc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"

//------------------------------------------------------------------------------
//	設定のアシスト関数

//----------------------------------------------------------
//ポートのクロック供給
void RCC_PeriphClock_GPIO(GPIO_TypeDef *port){
	static unsigned char f=0;

	if(port == GPIOA && (f&0x01) == 0){
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		f |= 0x01;
	}else if(port == GPIOB && (f&0x02) == 0){
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		f |= 0x02;
	}else if(port == GPIOC && (f&0x04) == 0){
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		f |= 0x04;
	}else if(port == GPIOD && (f&0x08) == 0){
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		f |= 0x08;
	}else if(port == GPIOE && (f&0x10) == 0){
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		f |= 0x10;
	}
}

//----------------------------------------------------------
//TIMのクロック供給
void RCC_PeriphClock_TIM(TIM_TypeDef *tim){
	static unsigned int f=0;

	if(tim == TIM1 && (f&0x01) == 0){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		f |= 0x01;
	}else if(tim == TIM2 && (f&0x02) == 0){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		f |= 0x02;
	}else if(tim == TIM3 && (f&0x04) == 0){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		f |= 0x04;
	}else if(tim == TIM4 && (f&0x08) == 0){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		f |= 0x08;
	}else if(tim == TIM5 && (f&0x10) == 0){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		f |= 0x10;
	}else if(tim == TIM8 && (f&0x20) == 0){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
		f |= 0x20;
	}else if(tim == TIM9 && (f&0x40) == 0){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
		f |= 0x40;
	}else if(tim == TIM10 && (f&0x80) == 0){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
		f |= 0x80;
	}else if(tim == TIM11 && (f&0x100) == 0){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
		f |= 0x100;
	}
}
//----------------------------------------------------------
//USART/UARTのクロック供給
void RCC_PeriphClock_USART(USART_TypeDef *usart){
	static unsigned int f=0;

	if(usart == USART1 && (f&0x01) == 0){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		f |= 0x01;
	}else if(usart == USART2 && (f&0x02) == 0){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		f |= 0x02;
	}else if(usart == USART3 && (f&0x04) == 0){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		f |= 0x04;
	}else if(usart == UART4 && (f&0x08) == 0){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
		f |= 0x08;
	}else if(usart == UART5 && (f&0x10) == 0){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
		f |= 0x10;
	}else if(usart == USART6 && (f&0x20) == 0){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
		f |= 0x20;
	}
}


//----------------------------------------------------------
//割り込み関数の許可
void NVIC_Configuration(int irqn){
	NVIC_InitTypeDef	NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = irqn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//----------------------------------------------------------
//割り込み関数の許可TIM専用
void NVIC_config_TIM(TIM_TypeDef *tim){
	NVIC_InitTypeDef	NVIC_InitStructure;
	if(tim == TIM1){
//		NVIC_Configuration(TIM1_IRQn);
	}else if(tim == TIM2){
//		NVIC_Configuration(TIM2_IRQn);
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}else if(tim == TIM3){
//		NVIC_Configuration(TIM3_IRQn);
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}else if(tim == TIM4){
//		NVIC_Configuration(TIM4_IRQn);
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}else if(tim == TIM5){
//		NVIC_Configuration(TIM5_IRQn);
		NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}else if(tim == TIM8){
		NVIC_Configuration(TIM8_UP_TIM13_IRQn);
	}else if(tim == TIM9){
//		NVIC_Configuration(TIM9_IRQn);
	}else if(tim == TIM10){
//		NVIC_Configuration(TIM10_IRQn);
	}else if(tim == TIM11){
//		NVIC_Configuration(TIM11_IRQn);
	}
}
//----------------------------------------------------------
//割り込み関数の許可USART専用
void NVIC_config_USART(USART_TypeDef *usart){
	if(usart == USART1){
		NVIC_Configuration(USART1_IRQn);
	}else if(usart == USART2){
		NVIC_Configuration(USART2_IRQn);
	}else if(usart == USART3){
		NVIC_Configuration(USART3_IRQn);
	}else if(usart == UART4){
		NVIC_Configuration(UART4_IRQn);
	}else if(usart == UART5){
		NVIC_Configuration(UART5_IRQn);
	}else if(usart == USART6){
		NVIC_Configuration(USART6_IRQn);
	}
}

//ポートをAFで使用する場合の設定
void Init_af_port(GPIO_TypeDef *port,uint16_t pin,uint8_t af,uint16_t mode){
	GPIO_InitTypeDef GPIO_InitStructure;					//GPIO初期化のための構造体
//	uint8_t pin;

	RCC_PeriphClock_GPIO(port);
	GPIO_StructInit(&GPIO_InitStructure);					//初期化用構造体にパラメータをセットしていくため、いったん初期値に戻す

	if((mode&0x0f) == PORT_PP){
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//出力ポートのタイプをプッシュプルに指定する
	}else if((mode&0x0f )== PORT_OD){
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;		//出力ポートのタイプをプッシュプルに指定する
	}

	if((mode&0xf0) == PORT_PULL_UP){
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	}else if((mode&0xf0) == PORT_PULL_DOWN){
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	}else if((mode&0xf0) == PORT_PULL_NO){
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	}

	GPIO_InitStructure.GPIO_Pin = pin;						//設定するピンを指定する（スイッチのピン・アクティブハイ）
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		//指定したピンを出力に指定する
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//GPIOのスピードを100MHz（最高速）にセットする
	GPIO_Init(port, &GPIO_InitStructure);					//PORT設定入力

	GPIO_PinAFConfig(port,Pin_select_source(pin),af);
}

//ポートをANで使用する場合の設定
void Init_an_port(GPIO_TypeDef *port,uint16_t pin,uint16_t mode){
	GPIO_InitTypeDef GPIO_InitStructure;					//GPIO初期化のための構造体
//	uint8_t pin;

	RCC_PeriphClock_GPIO(port);
	GPIO_StructInit(&GPIO_InitStructure);					//初期化用構造体にパラメータをセットしていくため、いったん初期値に戻す

	if((mode&0xf0) == PORT_PULL_UP){
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	}else if((mode&0xf0) == PORT_PULL_DOWN){
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	}else if((mode&0xf0) == PORT_PULL_NO){
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	}

	GPIO_InitStructure.GPIO_Pin = pin;						//設定するピンを指定する（スイッチのピン・アクティブハイ）
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;		//指定したピンを出力に指定する
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//GPIOのスピードを100MHz（最高速）にセットする
	GPIO_Init(port, &GPIO_InitStructure);					//PORT設定入力
}
//----------------------------------------------------------
//ポートのソース選択
uint8_t Pin_select_source(uint16_t pin){
	uint8_t source=0;

	switch(pin){
		case GPIO_Pin_0:	source = GPIO_PinSource0;
		break;
		case GPIO_Pin_1:	source = GPIO_PinSource1;
		break;
		case GPIO_Pin_2:	source = GPIO_PinSource2;
		break;
		case GPIO_Pin_3:	source = GPIO_PinSource3;
		break;
		case GPIO_Pin_4:	source = GPIO_PinSource4;
		break;
		case GPIO_Pin_5:	source = GPIO_PinSource5;
		break;
		case GPIO_Pin_6:	source = GPIO_PinSource6;
		break;
		case GPIO_Pin_7:	source = GPIO_PinSource7;
		break;
		case GPIO_Pin_8:	source = GPIO_PinSource8;
		break;
		case GPIO_Pin_9:	source = GPIO_PinSource9;
		break;
		case GPIO_Pin_10:	source = GPIO_PinSource10;
		break;
		case GPIO_Pin_11:	source = GPIO_PinSource11;
		break;
		case GPIO_Pin_12:	source = GPIO_PinSource12;
		break;
		case GPIO_Pin_13:	source = GPIO_PinSource13;
		break;
		case GPIO_Pin_14:	source = GPIO_PinSource14;
		break;
		case GPIO_Pin_15:	source = GPIO_PinSource15;
		break;
		default:break;
	}

	return source;
}
//----------------------------------------------------------
//TIMのチャンネル設定(port)
GPIO_TypeDef* Tim_select_port(TIM_TypeDef *tim,uint8_t ch){
	GPIO_TypeDef *port;
	if(tim == TIM1){
		if(ch == TIM_CH1)	port = TIM1_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM1_CH2_PORT;
		if(ch == TIM_CH3)	port = TIM1_CH3_PORT;
		if(ch == TIM_CH4)	port = TIM1_CH4_PORT;
	}else if(tim == TIM2){
		if(ch == TIM_CH1)	port = TIM2_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM2_CH2_PORT;
		if(ch == TIM_CH3)	port = TIM2_CH3_PORT;
		if(ch == TIM_CH4)	port = TIM2_CH4_PORT;
	}else if(tim == TIM3){
		if(ch == TIM_CH1)	port = TIM3_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM3_CH2_PORT;
		if(ch == TIM_CH3)	port = TIM3_CH3_PORT;
		if(ch == TIM_CH4)	port = TIM3_CH4_PORT;
	}else if(tim == TIM4){
		if(ch == TIM_CH1)	port = TIM4_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM4_CH2_PORT;
		if(ch == TIM_CH3)	port = TIM4_CH3_PORT;
		if(ch == TIM_CH4)	port = TIM4_CH4_PORT;
	}else if(tim == TIM5){
		if(ch == TIM_CH1)	port = TIM5_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM5_CH2_PORT;
		if(ch == TIM_CH3)	port = TIM5_CH3_PORT;
		if(ch == TIM_CH4)	port = TIM5_CH4_PORT;
	}else if(tim == TIM8){
		if(ch == TIM_CH1)	port = TIM8_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM8_CH2_PORT;
		if(ch == TIM_CH3)	port = TIM8_CH3_PORT;
		if(ch == TIM_CH4)	port = TIM8_CH4_PORT;
	}else if(tim == TIM9){
		if(ch == TIM_CH1)	port = TIM9_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM9_CH2_PORT;
	}else if(tim == TIM10){
		if(ch == TIM_CH1)	port = TIM10_CH1_PORT;
	}else if(tim == TIM11){
		if(ch == TIM_CH1)	port = TIM11_CH1_PORT;
	}

	return port;
}

//----------------------------------------------------------
//TIMのチャンネル設定(pin)
uint8_t Tim_select_pin(TIM_TypeDef *tim,uint8_t ch){
	uint16_t	pin;
	if(tim == TIM1){
		if(ch == TIM_CH1)	pin = TIM1_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM1_CH2_PIN;
		if(ch == TIM_CH3)	pin = TIM1_CH3_PIN;
		if(ch == TIM_CH4)	pin = TIM1_CH4_PIN;
	}else if(tim == TIM2){
		if(ch == TIM_CH1)	pin = TIM2_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM2_CH2_PIN;
		if(ch == TIM_CH3)	pin = TIM2_CH3_PIN;
		if(ch == TIM_CH4)	pin = TIM2_CH4_PIN;
	}else if(tim == TIM3){
		if(ch == TIM_CH1)	pin = TIM3_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM3_CH2_PIN;
		if(ch == TIM_CH3)	pin = TIM3_CH3_PIN;
		if(ch == TIM_CH4)	pin = TIM3_CH4_PIN;
	}else if(tim == TIM4){
		if(ch == TIM_CH1)	pin = TIM4_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM4_CH2_PIN;
		if(ch == TIM_CH3)	pin = TIM4_CH3_PIN;
		if(ch == TIM_CH4)	pin = TIM4_CH4_PIN;
	}else if(tim == TIM5){
		if(ch == TIM_CH1)	pin = TIM5_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM5_CH2_PIN;
		if(ch == TIM_CH3)	pin = TIM5_CH3_PIN;
		if(ch == TIM_CH4)	pin = TIM5_CH4_PIN;
	}else if(tim == TIM8){
		if(ch == TIM_CH1)	pin = TIM8_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM8_CH2_PIN;
		if(ch == TIM_CH3)	pin = TIM8_CH3_PIN;
		if(ch == TIM_CH4)	pin = TIM8_CH4_PIN;
	}else if(tim == TIM9){
		if(ch == TIM_CH1)	pin = TIM9_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM9_CH2_PIN;
	}else if(tim == TIM10){
		if(ch == TIM_CH1)	pin = TIM10_CH1_PIN;
	}else if(tim == TIM11){
		if(ch == TIM_CH1)	pin = TIM11_CH1_PIN;
	}

	return pin;
}

//----------------------------------------------------------
//TIMのAF選択
uint8_t Tim_select_af(TIM_TypeDef *tim){
	uint8_t select_af=0;

	if(tim == TIM1){
		select_af = GPIO_AF_TIM1;
	}else if(tim == TIM2){
		select_af = GPIO_AF_TIM2;
	}else if(tim == TIM3){
		select_af = GPIO_AF_TIM3;
	}else if(tim == TIM4){
		select_af = GPIO_AF_TIM4;
	}else if(tim == TIM5){
		select_af = GPIO_AF_TIM5;
	}else if(tim == TIM8){
		select_af = GPIO_AF_TIM8;
	}else if(tim == TIM9){
		select_af = GPIO_AF_TIM9;
	}else if(tim == TIM10){
		select_af = GPIO_AF_TIM10;
	}else if(tim == TIM11){
		select_af = GPIO_AF_TIM11;
	}

	return select_af;
}
//---------------------------------------------------------------------------------
//設定関数

//systick割り込みの設定
void Init_systick(float time){
	//systick割り込みの設定
	SystemCoreClockUpdate();								//SystemCoreClockの更新

	if(SysTick_Config(SystemCoreClock*time)){				//systickによる割り込み周期を設定
															//失敗時動作
	}
}

//----------------------------------------------------------
//I/Oの設定
/*void Init_io_port(uint16_t mode,GPIO_TypeDef *port,uint16_t pin){
	GPIO_InitTypeDef GPIO_InitStructure;					//GPIO初期化のための構造体

	RCC_PeriphClock_GPIO(port);

	GPIO_StructInit(&GPIO_InitStructure);					//初期化用構造体にパラメータをセットしていくため、いったん初期値に戻す
	GPIO_InitStructure.GPIO_Pin = pin;						//設定するピンを指定する（スイッチのピン・アクティブハイ）

	if(mode == OUTPUT){
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//指定したピンを出力に指定する
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//出力ポートのタイプをプッシュプルに指定する
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//プルアップを使用しない
	}else if(mode == INPUT){
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		//指定したピンを入力に指定する
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;		//プルアップを使用しない
	}
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//GPIOのスピードを100MHz（最高速）にセットする
	GPIO_Init(port, &GPIO_InitStructure);					//PORT設定入力

	if(mode == OUTPUT)	GPIO_ResetBits(port,pin);			//ポートのリセット
}*/
//----------------------------------------------------------
//	I2Cnの設定
void Init_i2c(I2C_TypeDef *use_i2c){
	I2C_InitTypeDef	I2C_InitStructure;

	if(use_i2c == I2C1){
		Init_af_port(I2C1_PORT,I2C1_SCL_PIN,GPIO_AF_I2C1,PORT_OD|PORT_PULL_UP);
		Init_af_port(I2C1_PORT,I2C1_SDA_PIN,GPIO_AF_I2C1,PORT_OD|PORT_PULL_UP);

	}else if(use_i2c == I2C2){
		Init_af_port(I2C2_PORT,I2C2_SCL_PIN,GPIO_AF_I2C2,PORT_OD|PORT_PULL_UP);
		Init_af_port(I2C2_PORT,I2C2_SDA_PIN,GPIO_AF_I2C2,PORT_OD|PORT_PULL_UP);

	}else if(use_i2c == I2C3){
		Init_af_port(I2C3_SCL_PORT,I2C3_SCL_PIN,GPIO_AF_I2C3,PORT_OD|PORT_PULL_UP);
		Init_af_port(I2C3_SDA_PORT,I2C3_SDA_PIN,GPIO_AF_I2C3,PORT_OD|PORT_PULL_UP);
	}

	I2C_StructInit(&I2C_InitStructure);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_ClockSpeed = 50000;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(use_i2c,&I2C_InitStructure);

	I2C_Cmd(use_i2c,ENABLE);
}
//----------------------------------------------------------
//	USART/UARTの設定
void Init_usart(USART_TypeDef *usart){
	USART_InitTypeDef USART_InitStructure;
	RCC_PeriphClock_USART(usart);

	//グローバル割り込み初期化の構造体を作る
	NVIC_InitTypeDef NVIC_InitStructure;

	if(usart == USART1){
		Init_af_port(USART1_TX_PORT,USART1_TX_PIN,GPIO_AF_USART1,PORT_OD|PORT_PULL_NO);
		Init_af_port(USART1_RX_PORT,USART1_RX_PIN,GPIO_AF_USART1,PORT_OD|PORT_PULL_NO);
	}else if(usart == USART2){
		Init_af_port(USART2_TX_PORT,USART2_TX_PIN,GPIO_AF_USART2,PORT_OD|PORT_PULL_NO);
		Init_af_port(USART2_RX_PORT,USART2_RX_PIN,GPIO_AF_USART2,PORT_OD|PORT_PULL_NO);
	}else if(usart == USART3){
		Init_af_port(USART3_TX_PORT,USART3_TX_PIN,GPIO_AF_USART3,PORT_OD|PORT_PULL_NO);
		Init_af_port(USART3_RX_PORT,USART3_RX_PIN,GPIO_AF_USART3,PORT_OD|PORT_PULL_NO);
	}else if(usart == UART4){
		Init_af_port(UART4_TX_PORT,UART4_TX_PIN,GPIO_AF_UART4,PORT_OD|PORT_PULL_NO);
		Init_af_port(UART4_RX_PORT,UART4_RX_PIN,GPIO_AF_UART4,PORT_OD|PORT_PULL_NO);
	}else if(usart == UART5){
		Init_af_port(UART5_TX_PORT,UART5_TX_PIN,GPIO_AF_UART5,PORT_OD|PORT_PULL_NO);
		Init_af_port(UART5_RX_PORT,UART5_RX_PIN,GPIO_AF_UART5,PORT_OD|PORT_PULL_NO);
	}else if(usart == USART6){
		Init_af_port(USART6_TX_PORT,USART6_TX_PIN,GPIO_AF_USART6,PORT_OD|PORT_PULL_NO);
		Init_af_port(USART6_RX_PORT,USART6_RX_PIN,GPIO_AF_USART6,PORT_OD|PORT_PULL_NO);
	}

	USART_InitStructure.USART_BaudRate = 38400;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(usart, &USART_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(usart,USART_IT_RXNE,ENABLE);
	USART_Cmd(usart, ENABLE);

}

//----------------------------------------------------------
//エンコーダーの設定
/*void Init_encoder(TIM_TypeDef *tim){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;			//TIMを設定するための構造体

	RCC_PeriphClock_TIM(tim);

	Init_af_port(Tim_select_port(tim,TIM_CH1),Tim_select_pin(tim,TIM_CH1),Tim_select_af(tim),PORT_PP|PORT_PULL_UP);
	Init_af_port(Tim_select_port(tim,TIM_CH2),Tim_select_pin(tim,TIM_CH2),Tim_select_af(tim),PORT_PP|PORT_PULL_UP);

	TIM_Prescaleg(tim,0,TIM_PSCReloadMode_Update);

	TIM_TimeBaseStructrConfiInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 0xffff;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(tim,&TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(tim,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

	TIM_Cmd(tim,ENABLE);

	NVIC_config_TIM(tim);
	TIM_ITConfig(tim,TIM_IT_Update,ENABLE);

}*/
//----------------------------------------------------------
//TIM PWMモードの設定
void Init_pwm(TIM_TypeDef *tim,uint8_t ch){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;			//TIMを設定するための構造体

	RCC_PeriphClock_TIM(tim);
	if((ch&TIM_CH1) != 0)	Init_af_port(Tim_select_port(tim,TIM_CH1),Tim_select_pin(tim,TIM_CH1),Tim_select_af(tim),PORT_PP|PORT_PULL_NO);
	if((ch&TIM_CH2) != 0)	Init_af_port(Tim_select_port(tim,TIM_CH2),Tim_select_pin(tim,TIM_CH2),Tim_select_af(tim),PORT_PP|PORT_PULL_NO);
	if((ch&TIM_CH3) != 0)	Init_af_port(Tim_select_port(tim,TIM_CH3),Tim_select_pin(tim,TIM_CH3),Tim_select_af(tim),PORT_PP|PORT_PULL_NO);
	if((ch&TIM_CH4) != 0)	Init_af_port(Tim_select_port(tim,TIM_CH4),Tim_select_pin(tim,TIM_CH4),Tim_select_af(tim),PORT_PP|PORT_PULL_NO);

	TIM_TimeBaseStructure.TIM_Period = 100;
	TIM_TimeBaseStructure.TIM_Prescaler = 4200;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(tim,&TIM_TimeBaseStructure);

	Tim_pulse_set(tim,ch,1);

	TIM_Cmd(tim,ENABLE);
	TIM_ARRPreloadConfig(tim,ENABLE);
}

//----------------------------------------------------------
//TIM PWMモード時のパルス幅変更
void Tim_pulse_set(TIM_TypeDef *tim,int ch,unsigned int pulse){
	TIM_OCInitTypeDef TIM_OCInitStructure;					//TIMを設定するための構造体

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

	if((ch&TIM_CH1) != 0){
		TIM_OCInitStructure.TIM_Pulse = pulse;
		TIM_OC1Init(tim,&TIM_OCInitStructure);
		TIM_OC1PreloadConfig(tim,TIM_OCPreload_Disable);
	}
	if((ch&TIM_CH2) != 0){
		TIM_OCInitStructure.TIM_Pulse = pulse;
		TIM_OC2Init(tim,&TIM_OCInitStructure);
		TIM_OC2PreloadConfig(tim,TIM_OCPreload_Disable);
	}
	if((ch&TIM_CH3) != 0){
		TIM_OCInitStructure.TIM_Pulse = pulse;
		TIM_OC3Init(tim,&TIM_OCInitStructure);
		TIM_OC3PreloadConfig(tim,TIM_OCPreload_Disable);
	}
	if((ch&TIM_CH4) != 0){
		TIM_OCInitStructure.TIM_Pulse = pulse;
		TIM_OC4Init(tim,&TIM_OCInitStructure);
		TIM_OC4PreloadConfig(tim,TIM_OCPreload_Disable);
	}
	TIM_Cmd(tim,ENABLE);
	TIM_ARRPreloadConfig(tim,ENABLE);
}

//-------------------------------------------------------------
//SPIの初期化
void Init_spi(void){
	SPI_InitTypeDef SPI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);

	Init_af_port(GPIOA,GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7,GPIO_AF_SPI1,PORT_PP | PORT_PULL_NO);
	Init_io_port(OUTPUT,GPIOE,GPIO_Pin_3);

	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStructure.SPI_CPHA		= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL		= SPI_CPOL_High;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_DataSize	= SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_RxOnly;
	SPI_InitStructure.SPI_FirstBit	= SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode		= SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS		= SPI_NSS_Soft;
	SPI_Init(SPI1,&SPI_InitStructure);

	SPI_Cmd(SPI1,ENABLE);
}
