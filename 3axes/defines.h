#ifndef DEFINES_H
#define DEFINES_H

/*モード切替*/
#define OUTPUT_MODE			AUTO_CONTROL
#define TARGET_SELECT		CAM_DATA
#define CENTER						ON	//ストーンを中心に持っていく
#define SERIAL 						ON
#define DEBUG						OFF

#define ABSOLUTE_D				OFF
#define STORN_COORD				OFF
#define FINISH_ARM					ON
#define MOVE_ARM_CAL			OFF
#define STORN_RANGE_CAM	ON

/* 送るデータ切り替え */
//#define DEBUG_CAM_DATA 						//カメラの素のデーター
#define DEBUG_ROBO_COORD_DATA		//ロボットの自己位置
//#define DEBUG_AD_DATA							//アームの距離
//#define DEBUG_TASK
//#define DEBUG_OUTPUT_DATA					//モーター出力
//#define DEBUG_ENC_DATA						//エンコーダの値
//#define DEBUG_TARGET_DATA					//目標値
//#define DEBUG_TARGET_COORD					//目標座標
//#define DEBUG_VELOCITY_DATA				//速度
//#define CAM_DATA2

#define MAX_VELOCITY			290.0//270.0
#define ROBO_TO_CENTER	1250.0
#define ROBO_TO_ARM			150.0

//#define PC				usb_put_char
#define PC				transmit_usart2_c

#define ON			1
#define OFF		0

#define CALIBRATION			1	//キャリブレ
#define AUTO_CONTROL		2	//自動
#define MANUAL_CONTROL	3	//手動
#define GAIN_ADJUSTMENT	4	//ゲイン調整
#define COORDINATE			5	//目標が指定した座標
#define CAM_DATA				6	//目標がカメラからのデータ
#define SONIC_WAVES			7	//超音波

/* ゲイン調整 */
#define ROCK_P_GAIN				10.0
#define ROCK_D_GAIN				15.0

#define CALIBRA_P_GAIN			100.0
#define CALIBRA_D_GAIN			120.0

#define STRAIGHT_P_GAIN		0.9//0.75
#define STRAIGHT_D_GAIN		0.0

#define ROCK_P_ARMGAIN		2.0
#define ROCK_D_ARMGAIN		3.2

/*最高速度*/
//#define MAX_VELOCITY						500.0
#define MAX_ANGULAR_VELOCITY	170.0	//最高角速度

/* 割り込みタイム */
#define INTERRUPT_TIME			5.0

#define START_X						0.00
#define START_Y						0.00
#define START_DEGREE				0.00

#define START_PORT					GPIOC, GPIO_Pin_13
//#define START_PORT					GPIOA, GPIO_Pin_0//マイコンについているスイッチ
#define START_SW					GPIO_ReadInputDataBit(START_PORT)
#define BUZZER							GPIOE, GPIO_Pin_1
#define ENC_RESET					GPIOA, GPIO_Pin_5
#define LIMIT_PORT					GPIOC, GPIO_Pin_15
#define LIMIT_SW						GPIO_ReadInputDataBit(LIMIT_PORT)
#define POTENTIO						GPIOC, GPIO_Pin_0

/* PWM の定義 */
#define MAX_DUTY				100.0
#define FREE							999

/*ストーン検知してない*/
#define UNDISCOVERED		9999
#define OVER_DISCOVERD	8888

/*エンコーダのカウント*/
#define ENCL()						tim4_count()
#define ENCR()						tim5_count()
#define ENCF()						tim8_count()

/*エンコーダタイヤ直径*/
#define ENC_DIAMETER_F	 		30.0
#define ENC_DIAMETER_R			30.0
#define ENC_DIAMETER_L			30.0

/*中心からエンコーダまでの距離*/
#define CENTER_TO_ENC		87.5

/*超音波*/
#define TRIG 							GPIOC, GPIO_Pin_15
#define ECOH 						GPIOC, GPIO_Pin_14

#define PULSE						400.0
//62n 400
//stm 200
#define M_PI							3.141592653
#define R_TO_D(x) 				( (float)(x) * ( 180.0 / M_PI ) )
#define D_TO_R(x)				( (float)(x) * ( M_PI / 180.0 ) )

#endif
