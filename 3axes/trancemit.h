#ifndef TRANCEMIT_H
#define TRANCEMIT_H

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#include "config_usb.h"

void transmit_usb(char word[]);

void transmit_usart1_s(char word[]);

void transmit_usart2_s(char word[]);

void transmit_usart3_s(char word[]);

#endif
