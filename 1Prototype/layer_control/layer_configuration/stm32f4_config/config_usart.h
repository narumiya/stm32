#ifndef CONFIG_USART_H
#define CONFIG_USART_H

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

/*USARTを設定する関数
USART番号、ボーレーﾄ、ＴＸ側ポート・ピン、ＲＸ側ポート・ピンを引数とする。

使用例)USART1にPA1(RX)PA2(TX)　ボーレート115200を設定したい場合
Init_USART(USART1,115200,GPIOA,GPIO_pin_1,GPIOA,GPIO_pin_2)*/
void Init_USART(USART_TypeDef *USARTx,unsigned int baudrate, GPIO_TypeDef *GPIOx_TX ,uint16_t pin_TX, GPIO_TypeDef *GPIOx_RX, uint16_t pin_RX);


/*USART割込みが起こったとき入る関数。
呼び出す必要はない。*/
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);


#endif
