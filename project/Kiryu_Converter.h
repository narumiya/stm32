
#ifndef KIRYU_CONVERTER_H
#define KIRYU_CONVERTER_H

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
//#include "stm32f4xx_adc.h"
#include "stm32f4xx_crc.h"
//#include "stm32f4xx_dma.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_gpio.h"
//#include "stm32f4xx_i2c.h"
//#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
//#include "stm32f4xx_spi.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "misc.h"

int USART_irqn_select(USART_TypeDef *usart);
uint8_t GPIO_af_USART_select(USART_TypeDef *usart);
void RCC_PeriphClock_TIM(TIM_TypeDef *tim);
void RCC_PeriphClock_USART(USART_TypeDef *usart);
void NVIC_Configuration(int irqn);
void NVIC_config_USART(USART_TypeDef *usart);
uint8_t Pin_select_source(uint16_t pin);
uint8_t Tim_select_af(TIM_TypeDef *tim);

#endif // !KIRYU_CONVERTER_H
