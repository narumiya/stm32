#include "init_STM32F4.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"
#include "GPIO_KI.h"

#define BITRATE			115200
//�ʖ���`
#define OUTPUT	0
#define INPUT	1

#define PORT_PP					0x01
#define PORT_OD					0x02
#define PORT_PULL_UP			0x10
#define PORT_PULL_DOWN	0x20
#define PORT_PULL_NO		0x30

#define ADC3_DR_ADDRESS     ((uint32_t)0x4001224C)	//ADC3�̕ϊ����ʃ��W�X�^�̃A�h���X

uint16_t ADC3ConvertedValue[2];	//�ϊ����ʂ�DMA�]�������z��

void init_USERT2(void)
{
	USART_InitTypeDef				USART_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//�N���b�N����

	//GPIO_InitPin(RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_2 | GPIO_Pin_3 , GPIO_Mode_AF);//pin�ݒ�
	Init_io_port(GPIO_Mode_AF, GPIOA,  GPIO_Pin_2 | GPIO_Pin_3, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	//USART2���w�肵���|�[�g�Ŏg�p
	GPIO_PinAFConfig(GPIOA , GPIO_PinSource2 , GPIO_AF_USART2);

	//USART2��9600bps,8bit,�X�g�b�v�r�b�g1,�p���e�B�Ȃ�,�t���[����Ȃ�,����M�L���ɐݒ�
	USART_InitStructure.USART_BaudRate = BITRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	//�ݒ芮��
	USART_Init(USART2, &USART_InitStructure);
	//USART2��L����
	USART_Cmd(USART2, ENABLE);
}

/*void init_Encoder(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	NVIC_InitTypeDef				NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//�N���b�N����

	GPIO_InitPin(RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_4 | GPIO_Pin_5, GPIO_Mode_AF);//pin�ݒ�

	TIM_PrescalerConfig(TIM3, 0, TIM_PSCReloadMode_Update);
	//TIM ����
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
	//����
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//_tim.c 3038

	//Encoder���w�肵���|�[�g�Ŏg�p
	GPIO_PinAFConfig(GPIOB , GPIO_PinSource4 , GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB , GPIO_PinSource5 , GPIO_AF_TIM3);

	//TIM3�L��
	TIM_Cmd(TIM3, ENABLE);

	//���荞��
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	//�D��xMAX
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;
	//�T�u�̗D��xMAX
	NVIC_InitStructure.NVIC_IRQChannelSubPriority				= 0;
	//���荞�݋���
	NVIC_InitStructure.NVIC_IRQChannelCmd						= ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

void init_ad_converter(void)
{
	  ADC_InitTypeDef       			ADC_InitStructure;
	  ADC_CommonInitTypeDef 	ADC_CommonInitStructure;
	  DMA_InitTypeDef       			DMA_InitStructure;

	  ADC_DeInit();

	  //�K�v�ȃy���t�F�����ɃN���b�N�����J�n
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

	  //GPIO_InitPin(RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_1 | GPIO_Pin_2, GPIO_Mode_AN);//pin�ݒ�
	  Init_an_port(GPIOC,GPIO_Pin_1 | GPIO_Pin_2, GPIO_Mode_AN);

	  DMA_InitStructure.DMA_Channel = DMA_Channel_2;
	  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC3_DR_ADDRESS;
	  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue;
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	  DMA_InitStructure.DMA_BufferSize = 2;	//�Q�`�����l���̕ϊ����ʂ𑗂邩��f�[�^���͂Q�i�`���l���𑝂₵���炱����ς���j
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//�����A�h���X���C���N�������g
	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	  DMA_Cmd(DMA2_Stream0, ENABLE);

	  //ADC3�̊�{�ݒ�
	  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	  ADC_CommonInit(&ADC_CommonInitStructure);

	  //ADC3�̕ϊ����[�h�ݒ�B����2�{���X�L�����ϊ����[�h�Œ����ϊ�
	  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	  ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//�X�L�����ϊ����[�h��
	  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_NbrOfConversion = 2;	//���͂��Q�{�i�`���l���𑝂₵���炱����ς���j
	  ADC_Init(ADC3, &ADC_InitStructure);

	  //ADC3�̃A�i���O���͂��`����
	  //ADC_Channel_11��PA1,ADC_Channel_12��PA2�B�}�j���A��(UM1472)�̃s���z�\������Ƃ킩��
	  //"ADC123_IN11"�Ƃ����\�L�́AADC1,ADC2,ADC3�Ŏg������͂�channel_11�Ɋ��蓖�Ă���A�Ƃ�������
	  //�g���`���l���𑝂₷�ɂ́A�����ɒǋL����B�`���l���w��̎��̃p�����[�^�͕ϊ��V�[�P���X�̏���
	  ADC_RegularChannelConfig(ADC3, ADC_Channel_11, 1, ADC_SampleTime_3Cycles);
	  ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 2, ADC_SampleTime_3Cycles);

	  //�ϊ����ʂ�DMA�]������邲�ƂɁAADC�͎��̕ϊ����J�n����悤�ɐݒ�
	  ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);

	  //ADC3��DMA���g����悤�ɂ���
	  ADC_DMACmd(ADC3, ENABLE);

	  //ADC3���g����悤�ɂ���
	  ADC_Cmd(ADC3, ENABLE);
}
*/
