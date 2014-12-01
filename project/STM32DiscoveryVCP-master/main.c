#include "main.h"

int TIM1_over_flow=0;
int TIM1_under_flow=0;



extern volatile uint32_t ticker, downTicker, time;

enum {
  I2C_STATE_START = 0,
  I2C_STATE_ADDRESS_DONE,
  I2C_STATE_DATA_1_DONE,
  I2C_STATE_DATA_2_DONE,
  I2C_STATE_STOP,
} MASTER_SEND_STATE;

#define SLAVE_ADDRESS 0x2A

int aa=0;
int stateI2C1 = I2C_STATE_START;
unsigned char bSendData[2];
/*
 * The USB data must be 4 byte aligned if DMA is enabled. This macro handles
 * the alignment, if necessary (it's actually magic, but don't tell anyone).
 */
__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;


void init();


/*
 * Define prototypes for interrupt handlers here. The conditional "extern"
 * ensures the weak declarations from startup_stm32f4xx.c are overridden.
 */
#ifdef __cplusplus
 extern "C" {
#endif

#ifdef __cplusplus
}
#endif


 void USART_puts(USART_TypeDef* USARTx, volatile char *s){

 	while(*s){
 		// wait until data register is empty
 		while( !(USARTx->SR & 0x00000040) );
 		USART_SendData(USARTx, *s);
 		*s++;
 	}
 }


int main(void)
{
	char str[40] ={0};
	int while_count=0;
	char i2c_data[8];
	FIL myFile;   // Filehandler


	/* Set up the system clocks */
	SystemInit();

	init();

	while(1){

		//GPIOD->BSRRL = GPIO_Pin_12;
	if(UB_Fatfs_CheckMedia(MMC_0)==FATFS_OK)
		{
			GPIOD->BSRRL = GPIO_Pin_12;
			// Media mounten
			if(UB_Fatfs_Mount(MMC_0)==FATFS_OK)
			{
				GPIOD->BSRRL = GPIO_Pin_13;
				//File zum schreiben im root neu anlegen
				if(UB_Fatfs_OpenFile(&myFile, "0:/UB_File.csv", F_WR_CLEAR)==FATFS_OK)
				{
					GPIOD->BSRRL = GPIO_Pin_14;
					time = 0;
				  while(time < 3000)
				  {
					  if(time%10==0){
					  GPIOD->BSRRL = GPIO_Pin_15;
					  while_count++;
					  sprintf(str,"%d",time);
					// ein paar Textzeilen in das File schreiben
					  UB_Fatfs_WriteString(&myFile,str);
					  }

				  }

				}
			}
		}
		GPIOD->BSRRH = GPIO_Pin_12;
		GPIOD->BSRRH = GPIO_Pin_13;
		GPIOD->BSRRH = GPIO_Pin_14;
		GPIOD->BSRRH = GPIO_Pin_15;
		UB_Fatfs_CloseFile(&myFile);
		// Media unmounten
		UB_Fatfs_UnMount(MMC_0);
		while(1){

		}
	}



#if 0
	bSendData[0] = 0x00;
	bSendData[1] = 0x84;
	/* Initialize USB, IO, SysTick, and all those other things you do in the morning */
	init();






	//sprintf(str,"Welcome to STM32F4-Discovery\r\n");
	//VCP_send_str(str);


	//bSendData[0] = 0x29;
	//I2C_GenerateSTART(I2C1,ENABLE);
	GPIOD->BSRRL = GPIO_Pin_12;
	I2C_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0x00);
	I2C_write(I2C1, 0x8B);

	I2C_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);
	GPIOD->BSRRL = GPIO_Pin_13;
	I2C_write(I2C1, 0x00);
	I2C_write(I2C1, 0x0B);
	I2C_stop(I2C1);
	time = 0;
	while(time<2);
	I2C_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0x03);
	I2C_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Receiver);
	GPIOD->BSRRL = GPIO_Pin_14;
	i2c_data[0] = I2C_read_ack(I2C1);
	i2c_data[1] = I2C_read_ack(I2C1);
	i2c_data[2] = I2C_read_ack(I2C1);
	i2c_data[3] = I2C_read_ack(I2C1);
	i2c_data[4] = I2C_read_ack(I2C1);
	i2c_data[5] = I2C_read_ack(I2C1);
	i2c_data[6] = I2C_read_ack(I2C1);
	i2c_data[7] = I2C_read_nack(I2C1);
	I2C_stop(I2C1);


	while(1){

		if(time > 200){

			time =0;
			/*
			if(I2C_STATE_STOP == stateI2C1){
				if(aa == 2){
					I2C_ITConfig(I2C1, I2C_IT_EVT, DISABLE);
					I2C_start(I2C1, SLAVE_ADDRESS, I2C_Direction_Receiver);
					i2c_data = I2C_read_nack(I2C1);
					stateI2C1 = I2C_STATE_START;
					I2C_ITConfig(I2C1, I2C_IT_EVT, ENABLE);
					I2C_GenerateSTART(I2C1,ENABLE);
				}else{
					stateI2C1 = I2C_STATE_START;
					I2C_GenerateSTART(I2C1,ENABLE);
				}
			}
			*/


			I2C_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);
			GPIOD->BSRRL = GPIO_Pin_15;
			I2C_write(I2C1, 0x03);
			I2C_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Receiver);
			i2c_data[0] = I2C_read_ack(I2C1);
			i2c_data[1] = I2C_read_ack(I2C1);
			i2c_data[2] = I2C_read_ack(I2C1);
			i2c_data[3] = I2C_read_ack(I2C1);
			i2c_data[4] = I2C_read_ack(I2C1);
			i2c_data[5] = I2C_read_ack(I2C1);
			i2c_data[6] = I2C_read_ack(I2C1);
			i2c_data[7] = I2C_read_nack(I2C1);
			I2C_stop(I2C1);
		 	sprintf(str,"0:%3d 1:%3d 2:%3d 3:%3d 4:%3d 5:%3d 6:%3d 7:%3d \r\n",i2c_data[0], i2c_data[1], i2c_data[2], i2c_data[3], i2c_data[4], i2c_data[5], i2c_data[6], i2c_data[7]);

			//VCP_send_str(str);
			transmit_uart3_s(str);
		}

	}

/*

 while(1){
		//motor1
		TIM9->CCR1 = 400;//PE5
		TIM9->CCR2 = 400;//PE6
		//motor2
		TIM2->CCR2 = 839;//PB3
		TIM3->CCR3 = 839;//PB0
		//motor3
		TIM1->CCR1 = 400;//PE9
		TIM1->CCR2 = 400;//PE11
		//motor4
		TIM1->CCR4 = 400;//PE14
		TIM2->CCR3 = 839;//PB10
		//motor5
		TIM12->CCR1 = 839;//PB14
		TIM12->CCR2 = 839;//PB15

}
*/
	while(1){

	}



/*
	while (0)
	{

			if(time > 5){
				time =0;

				//TIM4->CCR1 = 839*GetAdc1Value_xch(0)/4095;
				//TIM4->CCR2 = TIM4->CCR1;
				//TIM4->CCR3 = TIM4->CCR1;
				//TIM4->CCR4 = TIM4->CCR1;

				#if defined DEBUG_1
				//sprintf(str,"ADC3 CH11:%d CH12:%d\r\n", GetAdc1Value_xch(0), TIM4->CCR1);
				sprintf(str,"over:%d under:%d ENC:%6d \r\n",TIM1_over_flow, TIM1_under_flow, TIM_GetCounter(TIM1));
				//sprintf(str,"ABCDEFG%dBUG\n\r",GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_9));
				VCP_send_str(str);
				#endif
				//USART_puts(USART3,"ABCD\n\r");
				//transmit_uart3_s(str);
			}



	}
*/
#endif
	return 0;
}


void init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStructure);


/*
	GPIOD->BSRRH = GPIO_Pin_12;
	GPIOD->BSRRH = GPIO_Pin_13;
	GPIOD->BSRRH = GPIO_Pin_14;
	GPIOD->BSRRH = GPIO_Pin_15;
*/
	/* Setup SysTick or CROD! */
	if (SysTick_Config(SystemCoreClock / 1000)){ColorfulRingOfDeath();}

	/* Setup USB */
	/*
	USBD_Init(&USB_OTG_dev,
	            USB_OTG_FS_CORE_ID,
	            &USR_desc,
	            &USBD_CDC_cb,
	            &USR_cb);
*/

	UB_Fatfs_Init();

//	ADC_Configuration();
//	Init_TIM_pwm();
	//Init_Motor();
	//USART3_Configuration();
	//Init_TIM_encoder();
	//I2C_Configuration();

}

void TIM1_UP_TIM10_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET){
     if((TIM1->CR1>>4) == 1){
         TIM1_over_flow++;
     }else{
         TIM1_under_flow++;
     }
    TIM_ClearFlag(TIM1, TIM_IT_Update);
  }
}

void I2C1_EV_IRQHandler(void)
{

/*
	if(I2C_GetITStatus(I2C1, I2C_IT_ARLO)){
		GPIOD->BSRRL = GPIO_Pin_12;
	}

	if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)){
		//GPIOD->BSRRL = GPIO_Pin_12;
		I2C_Send7bitAddress(I2C1, 0x31, I2C_Direction_Transmitter);
	}

	if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){
		GPIOD->BSRRL = GPIO_Pin_13;
	}
	if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)){
		GPIOD->BSRRL = GPIO_Pin_14;
	}
	if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)){
		GPIOD->BSRRL = GPIO_Pin_15;
	}
	if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)){

	}
	*/
	if(I2C_STATE_START == stateI2C1){
		if(I2C_GetITStatus(I2C1, I2C_IT_SB) == SET){
			if(aa == 0){GPIOD->BSRRL = GPIO_Pin_12;}
			// I2C master send address
			I2C_Send7bitAddress(I2C1, SLAVE_ADDRESS, I2C_Direction_Transmitter);
			// next
			stateI2C1 = I2C_STATE_ADDRESS_DONE;
		}
	}else if(I2C_STATE_ADDRESS_DONE == stateI2C1){
		GPIOD->BSRRL = GPIO_Pin_13;
		if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == SUCCESS) {
			GPIOD->BSRRL = GPIO_Pin_13;
			// send rs
			I2C_SendData(I2C1, bSendData[0]);
			bSendData[0] = 0x00;
			bSendData[1] = 0x04;
			// next
			if(aa == 0 || aa == 1){
				stateI2C1 = I2C_STATE_DATA_1_DONE;
				if(aa == 1){
					bSendData[0] = 0x04;
				}
				aa++;
			}else{
				stateI2C1 = I2C_STATE_DATA_2_DONE;
			}
		}
	}else if(I2C_STATE_DATA_1_DONE == stateI2C1){
		if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == SUCCESS) {
			GPIOD->BSRRL = GPIO_Pin_14;
			//send rs
			I2C_SendData(I2C1, bSendData[1]);

			// next
			stateI2C1 = I2C_STATE_DATA_2_DONE;
		}
	}else if(I2C_STATE_DATA_2_DONE == stateI2C1){
		if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == SUCCESS) {
			GPIOD->BSRRL = GPIO_Pin_15;
			// stop condition
			I2C_GenerateSTOP(I2C1, ENABLE);
			stateI2C1 = I2C_STATE_STOP;
		}
	}

}
