#include "Kiryu_Converter.h"




//------------------------------------------------------------------------------
//	設定のアシスト関数

uint8_t GPIO_af_USART_select(USART_TypeDef *usart){
	static unsigned int f=0;
	uint8_t af_usart=0;

	if(usart == USART1 && (f&0x01) == 0){
		af_usart = GPIO_AF_USART1;
		f |= 0x01;
	}else if(usart == USART2 && (f&0x02) == 0){
		af_usart = GPIO_AF_USART2;
		f |= 0x02;
	}else if(usart == USART3 && (f&0x04) == 0){
		af_usart = GPIO_AF_USART3;
		f |= 0x04;
	}else if(usart == UART4 && (f&0x08) == 0){
		af_usart = GPIO_AF_UART4;
		f |= 0x08;
	}else if(usart == UART5 && (f&0x10) == 0){
        af_usart = GPIO_AF_UART5;
		f |= 0x10;
	}else if(usart == USART6 && (f&0x20) == 0){
		af_usart = GPIO_AF_USART6;
		f |= 0x20;
	}
	return af_usart;
}

int USART_irqn_select(USART_TypeDef *usart){
	static unsigned int f=0;
	int irqn=0;

	if(usart == USART1 && (f&0x01) == 0){
		irqn = USART1_IRQn;
		f |= 0x01;
	}else if(usart == USART2 && (f&0x02) == 0){
		irqn = USART2_IRQn;
		f |= 0x02;
	}else if(usart == USART3 && (f&0x04) == 0){
		irqn = USART3_IRQn;
		f |= 0x04;
	}else if(usart == UART4 && (f&0x08) == 0){
		irqn = UART4_IRQn;
		f |= 0x08;
	}else if(usart == UART5 && (f&0x10) == 0){
        irqn = UART5_IRQn;
		f |= 0x10;
	}else if(usart == USART6 && (f&0x20) == 0){
		irqn = USART6_IRQn;
		f |= 0x20;
	}
	return irqn;
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
