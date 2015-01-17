#include "config_adc.h"

#define		NO_CHANNEL		((uint8_t)(0xFF))

short g_ADC1_value[8] = {0};	//チャンネル数8個でとりあえず設定

/******************************************************************************
*	タイトル ： 指定したピンのADCチャンネルを選択
*	  関数名 ： Select_ADC_channel
*	  戻り値 ： uint8_t型 
*	   引数1 ： GPIO_TypeDef型 *GPIOx  GPIO（ポインタ）
*	   引数2 ： uint16_t型 pin  ピンの設定
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/13
******************************************************************************/
uint8_t Select_ADC_channel(GPIO_TypeDef *GPIOx, uint16_t pin)
{
	uint8_t ADC_channel = NO_CHANNEL;
	if(GPIOx == GPIOA){
		if(pin == GPIO_Pin_0){
			ADC_channel = ADC_Channel_0;
		}else if(pin == GPIO_Pin_1){
			ADC_channel = ADC_Channel_1;
		}else if(pin == GPIO_Pin_2){
			ADC_channel = ADC_Channel_2;
		}else if(pin == GPIO_Pin_3){
			ADC_channel = ADC_Channel_3;
		}else if(pin == GPIO_Pin_4){
			ADC_channel = ADC_Channel_4;		
		}else if(pin == GPIO_Pin_5){
			ADC_channel = ADC_Channel_5;
		}else if(pin == GPIO_Pin_6){
			ADC_channel = ADC_Channel_6;
		}else if(pin == GPIO_Pin_7){
			ADC_channel = ADC_Channel_7;
		}
	}else if(GPIOx == GPIOB){
		if(pin == GPIO_Pin_0){
			ADC_channel = ADC_Channel_8;
		}else if(pin == GPIO_Pin_1){
			ADC_channel = ADC_Channel_9;
		}
	}else if(GPIOx == GPIOC){
		if(pin == GPIO_Pin_0){
			ADC_channel = ADC_Channel_10; 
		}else if(pin == GPIO_Pin_1){
			ADC_channel = ADC_Channel_11;
		}else if(pin == GPIO_Pin_2){
			ADC_channel = ADC_Channel_12;
		}else if(pin == GPIO_Pin_3){
			ADC_channel = ADC_Channel_13;
		}else if(pin == GPIO_Pin_4){
			ADC_channel = ADC_Channel_14;
		}else if(pin == GPIO_Pin_3){
			ADC_channel = ADC_Channel_15;
		}
	}

	return (ADC_channel);
}

/******************************************************************************
*	タイトル ： ADC1初期設定
*	  関数名 ： Init_ADC1
*	  戻り値 ： void型 
*	   引数1 ： GPIO_TypeDef型 *GPIOx  GPIO（ポインタ）
*	   引数2 ： uint16_t型 pin  ピンの設定
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/13
******************************************************************************/
void Init_ADC1(GPIO_TypeDef *GPIOx, uint16_t pin)
{
	unsigned short i = 0;
	unsigned short ch = 0;
	uint8_t ADC_channel[16] = {NO_CHANNEL};

	//構造体変数を宣言
	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	DMA_InitTypeDef       DMA_InitStructure;
	Pin_t	pin_state;

	//構造体変数を初期化
	ADC_StructInit(&ADC_InitStructure);
	ADC_CommonStructInit(&ADC_CommonInitStructure);
	DMA_StructInit(&DMA_InitStructure);

	//モジュールストップ状態の解除
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	//GPIOの設定
	Init_port(GPIO_Mode_AN, GPIOx, pin, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	//Init_port(GPIO_Mode_AN,GPIOA,GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5,GPIO_PuPd_NOPULL,GPIO_OType_PP);
	//Init_port(GPIO_Mode_AN,GPIOC,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3,GPIO_PuPd_NOPULL,GPIO_OType_PP);
	
	//GPIOのピン分析
	Analysis_GPIO_Pin(pin, &pin_state);

	//DMA設定
	DMA_DeInit(DMA2_Stream0);														//DMA周辺回路レジスタを初期値にする
	DMA_InitStructure.DMA_Channel 				= DMA_Channel_0;					//チャンネルの指定
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= (uint32_t)&ADC1->DR;				//DMAy Channelx用周辺回路のベースアドレスを定義する
	DMA_InitStructure.DMA_Memory0BaseAddr 		= (uint32_t)&(g_ADC1_value);		//DMAy Channelxのメモリ側ベースアドレスを定義する
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_PeripheralToMemory;		//データ転送方向
	DMA_InitStructure.DMA_BufferSize 			= pin_state.user_pin_sum;								//バッファサイズ
	DMA_InitStructure.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;		//ペリフェラル側のアドレスを転送毎にインクリメントするかどうか
	DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;				//メモリ側のアドレスを転送毎にインクリメントするかどうか
	DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_HalfWord;	//ペリフェラル側のデータサイズ
	DMA_InitStructure.DMA_MemoryDataSize 		= DMA_MemoryDataSize_HalfWord;		//メモリ側のデータサイズ
	DMA_InitStructure.DMA_Mode 					= DMA_Mode_Circular;				//DMAの動作モードを指定
	DMA_InitStructure.DMA_Priority 				= DMA_Priority_High;				//DMA転送のソフトウェア優先度
	DMA_InitStructure.DMA_FIFOMode 				= DMA_FIFOMode_Disable;				//FIFOモードまたはダイレクトモードが指定されたストリームのために使用されるかどうかを指定します。
	DMA_InitStructure.DMA_FIFOThreshold 		= DMA_FIFOThreshold_HalfFull;		//FIFOしきい値レベルを指定します。
	DMA_InitStructure.DMA_MemoryBurst 			= DMA_MemoryBurst_Single;			//メモリ転送のためのバースト転送の設定を指定します。
	DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_Single;		//周辺転送のバースト転送の設定を指定します。
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);										//DMAの設定
	DMA_Cmd(DMA2_Stream0, ENABLE);													//DMAの有効化

	//ADC設定
	ADC_DeInit();																	//
	ADC_CommonInitStructure.ADC_Mode 			= ADC_Mode_Independent;				//独立した、またはマルチモードで動作するようにADCを設定します。
	ADC_CommonInitStructure.ADC_Prescaler 		= ADC_Prescaler_Div2;				//ADCへのクロックの周波数を選択します。
	ADC_CommonInitStructure.ADC_DMAAccessMode 	= ADC_DMAAccessMode_Disabled;		//マルチADCモード用のダイレクトメモリアクセスモードを設定します。
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;	//2サンプリング位相間の遅延を設定します。
	ADC_CommonInit(&ADC_CommonInitStructure);										//

	ADC_InitStructure.ADC_Resolution 			= ADC_Resolution_12b;				//ADC分解能のデュアルモードを設定
	ADC_InitStructure.ADC_ScanConvMode 			= ENABLE;							//スキャン（マルチチャンネル）またはシングル（1チャネル）モードで実行するかどうかを指定
	ADC_InitStructure.ADC_ContinuousConvMode 	= ENABLE;							//連続またはシングルモードで実行するかどうかを指定
	ADC_InitStructure.ADC_ExternalTrigConvEdge 	= ADC_ExternalTrigConvEdge_None;	//外部トリガエッジを選択し、定期的なグループのトリガを可能にする
	ADC_InitStructure.ADC_ExternalTrigConv 		= 0;								//定期的な基の変換の開始をトリガするために使用される外部イベントを選択
	ADC_InitStructure.ADC_DataAlign 			= ADC_DataAlign_Right;				//ADCデータ・アラインメントを左右どちらにするかを指定
	ADC_InitStructure.ADC_NbrOfConversion 		= pin_state.user_pin_sum;								//定期的なチャネルグループのシーケンサーを使用して実行されますADC変換の数を指定します。
	ADC_Init(ADC1, &ADC_InitStructure);												//

	//ADC1のDMAを使えるようにする
	ADC_DMACmd(ADC1, ENABLE);

	//ADC1のアナログ入力を定義する
	//ADC_Channel_11がPA1,ADC_Channel_12がPA2。マニュアル(UM1472)のピン配表を見るとわかる
	//"ADC123_IN11"という表記は、ADC1,ADC2,ADC3で使える入力でchannel_11に割り当てられる、ということ
	//使うチャネルを増やすには、ここに追記する。チャネル指定の次のパラメータは変換シーケンスの順序
	/*ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 3, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 4, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 5, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 6, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 7, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 8, ADC_SampleTime_480Cycles);*/

	//ADC_Channelの選択
	for(i = 0; i <16; i ++){
		if(pin_state.user_pin[i] == 1){
			ADC_channel[i] =  Select_ADC_channel(GPIOx, pin_state.pin_address[i]);
		}
	}

	//ADC1のアナログ入力を定義する
	for(i = 0; i < 16; i ++){
		if(ADC_channel[i] != NO_CHANNEL){
			ch ++;
			if(ch > pin_state.user_pin_sum){
				break;
			}else{
				ADC_RegularChannelConfig(ADC1, ADC_channel[i], ch, ADC_SampleTime_480Cycles);
			}
		}
	}

	//ADC_VBATCmd(ENABLE);//?多分いらない
	//変換結果がDMA転送されるごとに、ADCは次の変換を開始するように設定
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	//ADC1を使えるようにする
	ADC_Cmd(ADC1, ENABLE);
	//変換スタート
	ADC_SoftwareStartConv(ADC1);
}

/******************************************************************************
*	タイトル ： 指定したチャンネルのADC1の値を得る
*	  関数名 ： get_ADC1_value
*	  戻り値 ： short型 
*	   引数1 ： unsigned short型 ch  チャンネル(0~7)
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/14
******************************************************************************/
short get_ADC1_value(unsigned short ch)
{
	return (g_ADC1_value[ch]);
}



