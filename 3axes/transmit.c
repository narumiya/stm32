#include "trancemit.h"

void transmit_usb(char word[])
{
	int z=0;
	while(word[z] != '\0'){
		usb_put_char(word[z]);
		z ++;
	}
}

void transmit_usart1_s(char word[])
{
	int z=0;

	while(word[z] != '\0'){
		while(USART_GetFlagStatus( USART1, USART_FLAG_TXE) == RESET);
		USART_SendData( USART1, word[z] );
		z ++;
	}
}

void transmit_usart2_s(char word[])
{
	int z=0;

	while(word[z] != '\0'){
		while(USART_GetFlagStatus( USART2, USART_FLAG_TXE) == RESET);
		USART_SendData( USART2, word[z] );
		z ++;
	}
}

void transmit_usart3_s(char word[])
{
	int z=0;

	while(word[z] != '\0'){
		while(USART_GetFlagStatus( USART3, USART_FLAG_TXE) == RESET);
		USART_SendData( USART3, word[z] );
		z ++;
	}
}
