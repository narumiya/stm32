#include "usart.h"

/*
#define USART2_BAUDRATE 115200
#define USART3_BAUDRATE 115200
*/
#define Usart2_TxBufferSize  300//リングバッファの要素数
#define Usart2_RxBufferSize  100//リングバッファの要素数
#define Usart3_TxBufferSize  300//リングバッファの要素数
#define Usart3_RxBufferSize  100//リングバッファの要素数

char Usart2_TxBuffer[Usart2_TxBufferSize];

int  Usart2_TxPtrNow=0,
     Usart2_TxPtrEnd=1;

char Usart2_RxBuffer[Usart2_RxBufferSize];

int  Usart2_RxPtrNow=0,
     Usart2_RxPtrEnd=1;

char Usart3_TxBuffer[Usart3_TxBufferSize];

int  Usart3_TxPtrNow=0,
     Usart3_TxPtrEnd=1;

char Usart3_RxBuffer[Usart3_RxBufferSize];

int  Usart3_RxPtrNow=0,
     Usart3_RxPtrEnd=1;




void USART3_Configuration(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* Connect PXx to USARTx_Tx*/
	 GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);//USART3 TX/PD8
	 /* Connect PXx to USARTx_Rx*/
	 GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);//USART3 RX/PD9


	//USART2を9600bps,8bit,ストップビット1,パリティなし,フロー制御なし,送受信有効に設定
	USART_InitStructure.USART_BaudRate = 119200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE);

	/* Configure one bit for preemption priority */
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	 /* Enable the USART Interrupt */
	 NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStructure);

	 LED();
}


/*
//一文字送信
void transmit_uart2_c(char c)
{

  USART_ITConfig(USART2, USART_IT_TXE, DISABLE);  //送信し終わった割り込みを一時的に禁止

  Usart2_TxBuffer[Usart2_TxPtrEnd]=c;    //リングバッファに１文字追加

  Usart2_TxPtrEnd++;                    //書き込みポインタを＋１

  if(Usart2_TxPtrEnd>(Usart2_TxBufferSize-1)) Usart2_TxPtrNow=0; Usart2_TxPtrEnd=1;    //書き込みポインタがオーバーフローしたら０に戻す

  USART_ITConfig(USART2, USART_IT_TXE, ENABLE);  // 送信し終わった割り込みを許可

}
//文字列送信
void transmit_uart2_s(char *s)
{

  USART_ITConfig(USART2, USART_IT_TXE, DISABLE); 

  while(*s!=0) // until end of string   文字列の末尾までループ

  {

    Usart2_TxBuffer[Usart2_TxPtrEnd]=*(s++); 

    Usart2_TxPtrEnd++; //  ポインタ＋１

    if(Usart2_TxPtrEnd>(Usart2_TxBufferSize-1)) Usart2_TxPtrEnd=0;

  }

  USART_ITConfig(USART2, USART_IT_TXE, ENABLE);   //送信し終わった割り込みを許可

}
*/
//一文字送信
void transmit_uart3_c(char c)
{

  USART_ITConfig(USART3, USART_IT_TXE, DISABLE);  //送信し終わった割り込みを一時的に禁止

  Usart3_TxBuffer[Usart3_TxPtrEnd]=c;    //リングバッファに１文字追加

  Usart3_TxPtrEnd++;    //書き込みポインタを＋１

  if(Usart3_TxPtrEnd>(Usart3_TxBufferSize-1)) Usart3_TxPtrNow=0; Usart3_TxPtrEnd=1;    //書き込みポインタがオーバーフローしたら０に戻す

  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);  // 送信し終わった割り込みを許可

}
//文字列送信
void transmit_uart3_s(char *s)
{

  USART_ITConfig(USART3, USART_IT_TXE, DISABLE); 

  while(*s!=0) // until end of string   文字列の末尾までループ
  {

    Usart3_TxBuffer[Usart3_TxPtrEnd]=*(s++); 

    Usart3_TxPtrEnd++; //  ポインタ＋１

    if(Usart3_TxPtrEnd>(Usart3_TxBufferSize-1)) Usart3_TxPtrEnd=0;

  }

  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);   //送信し終わった割り込みを許可

}
/*

void USART2_IRQHandler(void)
{
  
  char c;
  
   //受信割り込み
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  { 
     c = (char)USART_ReceiveData(USART2);
      #ifdef DEBUG_1
       transmit_uart2_c(c);
      #else
         transmit_uart2_c(c);
      #endif

  }
  
  
   if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)  // UART送信フラグチェック

  {

    USART_SendData(USART2, Usart2_TxBuffer[Usart2_TxPtrNow++]); // １文字送信

    if(Usart2_TxPtrNow>(Usart2_TxBufferSize-1)) Usart2_TxPtrNow=0;;//   ポインタオーバーフローならゼロに戻す

    if(Usart2_TxPtrNow==Usart2_TxPtrEnd)     //リングバッファが空か？

    {

      USART_ITConfig(USART2, USART_IT_TXE, DISABLE); //送信割り込みをオフ


    }

  }
  

}
*/

void LED(void)
{
	GPIO_InitTypeDef LED_Config;
	// Always remember to turn on the peripheral clock...  If not, you may be up till 3am debugging...
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	LED_Config.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	LED_Config.GPIO_Mode = GPIO_Mode_OUT;
	LED_Config.GPIO_OType = GPIO_OType_PP;
	LED_Config.GPIO_Speed = GPIO_Speed_25MHz;
	LED_Config.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &LED_Config);
}

void USART3_IRQHandler(void)
{
  
  char c;
  
   //受信割り込み
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  { 
     c = (char)USART_ReceiveData(USART3);
     transmit_uart3_c(c);
  }
  
  GPIOD->BSRRL = GPIO_Pin_13;
   if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)  // UART送信フラグチェック

  {GPIOD->BSRRL = GPIO_Pin_14;

    USART_SendData(USART3, Usart3_TxBuffer[Usart3_TxPtrNow++]); // １文字送信

    if(Usart3_TxPtrNow>(Usart3_TxBufferSize-1)) Usart3_TxPtrNow=0;;//   ポインタオーバーフローならゼロに戻す

    if(Usart3_TxPtrNow==Usart3_TxPtrEnd)     //リングバッファが空か？
    {
      USART_ITConfig(USART3, USART_IT_TXE, DISABLE); //送信割り込みをオフ
    }

  }
  
}
