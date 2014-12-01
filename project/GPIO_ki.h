#ifndef GPIO_KI_H
#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

#define GPIO_KI_H

void Init_io_port(GPIOMode_TypeDef mode,GPIO_TypeDef *port,uint16_t pin,GPIOPuPd_TypeDef pupd,GPIOOType_TypeDef otype);

#endif
