#include "sdio.h"


/*
void SDIO_Configuration(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	SDIO_InitTypeDef 	SDIO_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SDIO, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	 GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_SDIO);

	 // Configure the SDIO peripheral
	 SDIO_InitTypeDef SDIO_InitStructure;
	 SDIO_InitStructure.SDIO_ClockDiv = 0xB2;
	 SDIO_InitStructure.SDIO_ClockEdge = SDIO_ClockEdge_Rising;
	 SDIO_InitStructure.SDIO_MCLKBypass = SDIO_MCLKBypass_Disable;
	 SDIO_InitStructure.SDIO_ClockPowerSave = SDIO_ClockPowerSave_Enable;
	 SDIO_InitStructure.SDIO_BusWide = SDIO_BusWide_4b;
	 SDIO_InitStructure.SDIO_HardwareFlowControl =
	 SDIO_HardwareFlowControl_Enable;
	 SDIO_Init(&SDIO_InitStructure);

	 // Configure one bit for preemption priority
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	 // Enable the SDIO Interrupt
	 NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStructure);

}


void SDIO_IRQHandler(void)
 {
     // Process All SDIO Interrupt Sources
     SD_ProcessIRQSrc();
 }
*/
