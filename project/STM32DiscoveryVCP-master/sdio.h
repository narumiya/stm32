
#ifndef SDIO_H
#define SDIO_H
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_sdio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"


//SDIO
void SDIO_IRQHandler(void);

//SDIO‰Šú‰»ŠÖ”
void SDIO_Configuration(void);

#endif
