
#ifndef CONFIG_PORT_H
#define CONFIG_PORT_H

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

//É|Å[ÉgÇÃê›íË
void Init_port(GPIOMode_TypeDef mode,GPIO_TypeDef *port,uint16_t pin,GPIOPuPd_TypeDef pupd,GPIOOType_TypeDef otype);
uint8_t Pin_select_source(uint16_t pin);
void Set_GPIO_output(GPIO_TypeDef *port, uint16_t pin, unsigned short high_or_low);

#endif // !CONFIG_PORT_H
