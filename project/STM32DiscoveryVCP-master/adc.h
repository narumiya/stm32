
#ifndef ADC_H
#define ADC_H
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_rcc.h"

//ADC初期化関数
void ADC_Configuration(void);
//値取得関数自作
uint16_t GetAdc1Value_xch(uint8_t ch);


#endif
