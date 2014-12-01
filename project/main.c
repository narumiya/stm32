

#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"
#include "my_standard_io_ver_2.h"
#include "usb_communication.h"
#include "Config_port.h"
//#include "config_encoder.h"

#define PC			Usb_put_char

#define ON			1
#define OFF		0

#define TRUU		1
#define FALSE	0

//別名定義
#define OUTPUT	0
#define INPUT	1

#define PORT_PP					0x01
#define PORT_OD					0x02
#define PORT_PULL_UP			0x10
#define PORT_PULL_DOWN	0x20
#define PORT_PULL_NO		0x30

#define PWM_FREQUENCY		1000000
#define PWM_PERIOD				(84000000 / PWM_FREQUENCY) - 1
#define BITRATE						115200

#define ADC3_DR_ADDRESS     ((uint32_t)0x4001224C)	//ADC3の変換結果レジスタのアドレス

uint16_t ADC3ConvertedValue[2];	//変換結果がDMA転送される配列
float ADvoltage[2];

/*弧度法、度数法　変換*/
//#define M_PI							3.141592653
#define R_TO_D(x) 				( x * ( 180 / M_PI ) )
#define D_TO_R(x)				( x * ( M_PI / 180 ) )

int g_time = 0,
		g_sonic_timer = 0,
	g_time_count = 0;

void init_LED(void)
{
	//LED GPIOD pin12~15;
	Init_port(GPIO_Mode_OUT, GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15, GPIO_PuPd_UP, GPIO_OType_PP);
}

void init_user_switch(void)
{
	Init_port(GPIO_Mode_IN, GPIOA, GPIO_Pin_0, GPIO_PuPd_NOPULL, GPIO_OType_PP);
}
/*
void init_led_pwm(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef				TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//クロック供給

	GPIO_InitPin(RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15, GPIO_Mode_AF);//pin設定

	TIM_TimeBaseStructure.TIM_Period = PWM_PERIOD-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 21-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	//ch1 PD12
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Disable);
	//ch2 PD13
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Disable);
	//ch3 PD14
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Disable);
	//ch4 PD15
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Disable);

	//TIM4を指定したポートで使用
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

	//TIM4を使用許可
	TIM_Cmd(TIM4, ENABLE);

	//プリロードコンフィグ使用許可
	TIM_ARRPreloadConfig(TIM4, ENABLE);
}*/
/*
void init_USERT2(void)
{
	USART_InitTypeDef				USART_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//クロック供給

	GPIO_InitPin(RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_2 | GPIO_Pin_3 , GPIO_Mode_AF);//pin設定

	//USART2を指定したポートで使用
	GPIO_PinAFConfig(GPIOA , GPIO_PinSource2 , GPIO_AF_USART2);

	//USART2を9600bps,8bit,ストップビット1,パリティなし,フロー制御なし,送受信有効に設定
	USART_InitStructure.USART_BaudRate = BITRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	//設定完了
	USART_Init(USART2, &USART_InitStructure);
	//USART2を有効化
	USART_Cmd(USART2, ENABLE);
}

//TIM3 ch1,2 PB4 PB5
void init_Encoder(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	NVIC_InitTypeDef				NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//クロック供給

	GPIO_InitPin(RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_4 | GPIO_Pin_5, GPIO_Mode_AF);//pin設定

	TIM_PrescalerConfig(TIM3, 0, TIM_PSCReloadMode_Update);
	//TIM 周期
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
	//分周
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//_tim.c 3038

	//Encoderを指定したポートで使用
	GPIO_PinAFConfig(GPIOB , GPIO_PinSource4 , GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB , GPIO_PinSource5 , GPIO_AF_TIM3);

	//TIM3有効
	TIM_Cmd(TIM3, ENABLE);

	//割り込み
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	//優先度MAX
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;
	//サブの優先度MAX
	NVIC_InitStructure.NVIC_IRQChannelSubPriority				= 0;
	//割り込み許可
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

	  //必要なペリフェラルにクロック供給開始
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

	  GPIO_InitPin(RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_1 | GPIO_Pin_2, GPIO_Mode_AN);//pin設定

	  DMA_InitStructure.DMA_Channel = DMA_Channel_2;
	  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC3_DR_ADDRESS;
	  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue;
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	  DMA_InitStructure.DMA_BufferSize = 2;	//２チャンネルの変換結果を送るからデータ数は２（チャネルを増やしたらここを変える）
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//送り先アドレスをインクリメント
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

	  //ADC3の基本設定
	  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	  ADC_CommonInit(&ADC_CommonInitStructure);

	  //ADC3の変換モード設定。入力2本をスキャン変換モードで逐次変換
	  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	  ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//スキャン変換モードに
	  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_NbrOfConversion = 2;	//入力を２本（チャネルを増やしたらここを変える）
	  ADC_Init(ADC3, &ADC_InitStructure);

	  //ADC3のアナログ入力を定義する
	  //ADC_Channel_11がPA1,ADC_Channel_12がPA2。マニュアル(UM1472)のピン配表を見るとわかる
	  //"ADC123_IN11"という表記は、ADC1,ADC2,ADC3で使える入力でchannel_11に割り当てられる、ということ
	  //使うチャネルを増やすには、ここに追記する。チャネル指定の次のパラメータは変換シーケンスの順序
	  ADC_RegularChannelConfig(ADC3, ADC_Channel_11, 1, ADC_SampleTime_3Cycles);
	  ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 2, ADC_SampleTime_3Cycles);

	  //変換結果がDMA転送されるごとに、ADCは次の変換を開始するように設定
	  ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);

	  //ADC3のDMAを使えるようにする
	  ADC_DMACmd(ADC3, ENABLE);

	  //ADC3を使えるようにする
	  ADC_Cmd(ADC3, ENABLE);
}*/

void init_timer(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	NVIC_InitTypeDef				NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//クロック供給

	//TIM_PrescalerConfig(TIM3, 0, TIM_PSCReloadMode_Update);
	//TIM 周期
	TIM_TimeBaseStructure.TIM_Period = 84 - 1;
	//分周
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	//割り込み
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	//優先度MAX
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 1;
	//サブの優先度MAX
	NVIC_InitStructure.NVIC_IRQChannelSubPriority				= 1;
	//割り込み許可
	NVIC_InitStructure.NVIC_IRQChannelCmd						= ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//systic割り込み設定			//ここの数字を変更すると割り込み周期が変わる　単位（秒）
void init_systic(float time )
{
	//SystemCoreの更新
	SystemCoreClockUpdate();

	if(SysTick_Config( SystemCoreClock * time ) ){	//割り込みが起こらなかったらif文のなかに入る

	}
}

void TIM3_IRQHandler(void)
{
	//g_time_count ++;
	g_sonic_timer ++;
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

//1msごとに割り込む
void SysTick_Handler(void)
{
	g_time ++; 			//1msで、１カウントする
}

//1us割り込み
/*void TIM2_IRQHandler(void)
{
	g_time_count += 0.000001;
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}*/


void transmit_c( char str )
{
	while(USART_GetFlagStatus( USART2, USART_FLAG_TXE) == RESET);
		USART_SendData( USART2, str );
}

void ColorfulRingOfDeath(void)
{
	uint16_t ring = 1;
	while (1)
	{
		uint32_t count = 0;
		while (count++ < 500000);

		GPIOD->BSRRH = (ring << 12);
		ring = ring << 1;
		if (ring >= 1<<4)
		{
			ring = 1;
		}
		GPIOD->BSRRL = (ring << 12);
	}
}

float get_Average( int number_scope, int box, float add ){
    static float average[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    static float number[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    if(number[box] >= number_scope){
        number[box] = (number_scope - 1);
    }

    average[box] *= number[box];
    average[box] += add;
    number[box] ++;
    average[box] = average[box] / number[box];

    return (average[box]);
}

#define TRIG 		GPIOB, GPIO_Pin_8
#define ECOH 	GPIOB, GPIO_Pin_9
void sonic_waves(void)
{
	float distance = 0;
	static int phase_count = 0;

	Init_port(GPIO_Mode_OUT,TRIG, GPIO_PuPd_UP, GPIO_OType_PP);
	Init_port(GPIO_Mode_IN, ECOH, GPIO_PuPd_NOPULL, GPIO_OType_PP);

	if(phase_count == 0){
		GPIO_SetBits(TRIG);

		if(g_sonic_timer >= 10){
			GPIO_ResetBits(TRIG);
			phase_count = 1;
			g_sonic_timer = 0;
		}
	}else if(phase_count == 1){
		if(GPIO_ReadInputDataBit(ECOH) == SET){
			g_sonic_timer = 0;
			phase_count = 2;
		}
	}else if(phase_count == 2){

		if(GPIO_ReadInputDataBit(ECOH) == RESET){
			distance =get_Average( 20 ,0 , g_sonic_timer * 0.17 );

			F_print(PC, "cnt", g_sonic_timer);
			F_print(PC, "wave", distance);
			Put_enter(PC);

			g_sonic_timer = 0;
			phase_count = 0;
		}
	}
}

int main(void)
{
	int i =0;
	int j = 0;
	float dis = 0.00;

	SystemInit();
	init_LED();
	//init_user_switch();
	init_timer();
	init_systic(0.001);
	//init_led_pwm();
	//init_USERT2();
	//Init_encoder(TIM1, GPIOE, GPIO_Pin_9 | GPIO_Pin_11);//PE9 11 動いた
	/*Init_encoder(TIM2, GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
	Init_encoder(TIM3, GPIOA, GPIO_Pin_6 | GPIO_Pin_7);
	Init_encoder(TIM4, GPIOB, GPIO_Pin_6 | GPIO_Pin_7);
	Init_encoder(TIM5, GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
	Init_encoder(TIM8, GPIOC, GPIO_Pin_6 | GPIO_Pin_7);*/
	//Init_encoder();

	Init_usb();
	//init_ad_converter();

	//エンコーダ初期化
	//TIM_SetCounter(TIM1 , 0);
	/*TIM_SetCounter(TIM2 , 0);
	TIM_SetCounter(TIM3 , 0);
	TIM_SetCounter(TIM4 , 0);
	TIM_SetCounter(TIM5 , 0);
	TIM_SetCounter(TIM8 , 0);*/

	//g_over_tim3 = 0,
	//g_under_tim3 = 0;
	//AD変換開始
	//ADC_SoftwareStartConv(ADC3);

	//ColorfulRingOfDeath();

	while(1){

    	if(g_time_count >= 1000000){
    		g_time_count = 0;
    		GPIO_SetBits(GPIOD,GPIO_Pin_13);
    		i++;
    	}
    	if(g_time >= 1000){
    		g_time = 0;
    		j++;
    	}
    	sonic_waves();

		//GPIO_SetBits(GPIOD,GPIO_Pin_12);
		//ADvoltage[0] = ADC3ConvertedValue[0] *3.3 / 0xFFF;
		//ADvoltage[1] = ADC3ConvertedValue[1] *3.3 / 0xFFF;

		//スイッチの状体
		/*if( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) != RESET ){
			//pwm_output_TIM4_ch1(100);
			//pwm_output_TIM4_ch2(100);
			//pwm_output_TIM4_ch3(100);
			//pwm_output_TIM4_ch4(100);
			//TIM_SetCompare1(TIM4, ( PWM_PERIOD * 100 ) /100);
			GPIO_SetBits(GPIOD,GPIO_Pin_15);
			GPIO_SetBits(GPIOD,GPIO_Pin_14);
			GPIO_SetBits(GPIOD,GPIO_Pin_13);
			GPIO_SetBits(GPIOD,GPIO_Pin_12);
		}else{
			GPIO_ResetBits(GPIOD,GPIO_Pin_12);
			GPIO_ResetBits(GPIOD,GPIO_Pin_13);
			GPIO_ResetBits(GPIOD,GPIO_Pin_14);
			GPIO_ResetBits(GPIOD,GPIO_Pin_15);
			pwm_output_TIM4_ch1(10);
			pwm_output_TIM4_ch2(10);
			pwm_output_TIM4_ch3(10);
			pwm_output_TIM4_ch4(10);
			//TIM_SetCompare1(TIM4, ( PWM_PERIOD * 10 ) /100);
		}*/

		/*if(g_time_count >= 1.0 ){
			GPIO_SetBits(GPIOD,GPIO_Pin_12);
		}*/

		 //count =  tim4_count();

		//F_print(PC,"tim1",TIM_GetCounter(TIM1));
		 //F_print(PC,"tim1",tim1_count());
		//F_print(PC,"tim2",tim2_count());ok
		 //F_print(PC,"tim3",tim3_count());ok
		 //F_print(PC,"tim4",tim4_count());ok
		 //F_print(PC,"tim5",tim5_count());ok
		 //F_print(PC,"tim8",tim8_count());ok

		// F_print(PC,"ad1",ADvoltage[1]);
		 //F_print(PC,"time",g_time_count);
		 //Put_enter(PC);

		/* if( g_time >= 0.01 ){
			 g_time = 0;
			 I_print(PC,"count",count);
			 I_print(PC,"g_tim3_under",g_under_tim3);
			 I_print(PC,"g_tim3_over",g_over_tim3);
			 Put_enter(PC);
		 }*/
	}

	return 0;
}
