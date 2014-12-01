#ifndef DEFINES_H
#define DEFINES_H
/*
//#include <stdio.h>
#include <math.h>

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
*/
/* �}�C�R���̐ݒ� */
/*#include "config_adc.h"
#include "config_encoder.h"
#include "config_port.h"
#include "config_pwm.h"
#include "config_systick.h"
#include "config_usart.h"
#include "name_converter.h"
#include "config_usb.h"

#include "my_standard_io.h"
#include "robo_data.h"
#include "robo_finction.h"
#include "debug.h"
#include "motor_define.h"
#include "motor.h"
#include "cam_cal.h"
#include "chata.h"
#include "trancemit.h"
#include "receive.h"
*/

/*���[�h�ؑ�*/
#define OUTPUT_MODE			AUTO_CONTROL
#define TARGET_SELECT		CAM_DATA
#define CENTER						ON	//�X�g�[���𒆐S�Ɏ����Ă���
#define SERIAL 						OFF
#define DEBUG						OFF
#define ABSOLUTE_D			OFF

/* ����f�[�^�؂�ւ� */
//#define DEBUG_CAM_DATA 						//�J�����̑f�̃f�[�^�[
//#define DEBUG_ROBO_COORD_DATA		//���{�b�g�̎��Ȉʒu
//#define DEBUG_AD_DATA							//�A�[���̋���
//#define DEBUG_TASK
//#define DEBUG_OUTPUT_DATA					//���[�^�[�o��
//#define DEBUG_ENC_DATA						//�G���R�[�_�̒l
//#define DEBUG_TARGET_DATA					//�ڕW�l
//#define DEBUG_TARGET_COORD					//�ڕW���W
//#define DEBUG_VELOCITY_DATA				//���x

#define PC1			transmit_usart2_s
#define PC				usb_put_char

#define ON			1
#define OFF		0

#define CALIBRATION			1	//�L�����u��
#define AUTO_CONTROL		2	//����
#define MANUAL_CONTROL	3	//�蓮
#define GAIN_ADJUSTMENT	4	//�Q�C������
#define COORDINATE			5	//�ڕW���w�肵�����W
#define CAM_DATA				6	//�ڕW���J��������̃f�[�^
#define SONIC_WAVES			7	//�����g

/* �Q�C������ */
#define ROCK_P_GAIN				50.0
#define ROCK_D_GAIN				60.0

#define CALIBRA_P_GAIN			100.0
#define CALIBRA_D_GAIN			120.0

#define STRAIGHT_P_GAIN		2.6
#define STRAIGHT_D_GAIN		2.9

#define ROCK_P_ARMGAIN		1000.0
#define ROCK_D_ARMGAIN		1500.0

/*�ō����x*/
#define MAX_VELOCITY						500.0
#define MAX_ANGULAR_VELOCITY	170.0	//�ō��p���x

/* ���荞�݃^�C�� */
#define INTERRUPT_TIME			5

#define START_X						0.00
#define START_Y						0.00
#define START_DEGREE				0.00

#define START_PORT					GPIOC, GPIO_Pin_13
//#define START_PORT					GPIOA, GPIO_Pin_0//�}�C�R���ɂ��Ă���X�C�b�`
#define START_SW					GPIO_ReadInputDataBit(START_PORT)
#define BUZZER							GPIOE, GPIO_Pin_1
#define ENC_RESET					GPIOA, GPIO_Pin_15
#define LIMIT_PORT					GPIOC, GPIO_Pin_1
#define LIMIT_SW						GPIO_ReadInputDataBit(LIMIT_PORT)
#define POTENTIO						GPIOC, GPIO_Pin_0

/* PWM �̒�` */
#define MAX_DUTY				100.0
#define FREE							999

#define UNDISCOVERED		9999

/*�G���R�[�_�̃J�E���g*/
#define ENCL()						tim4_count()
#define ENCR()						tim5_count()
#define ENCF()						tim8_count()

/*�G���R�[�_�^�C�����a*/
#define ENC_DIAMETER_F	 		30.0
#define ENC_DIAMETER_R			30.0
#define ENC_DIAMETER_L			30.0

/*���S����G���R�[�_�܂ł̋���*/
#define CENTER_TO_ENC		87.5

/*�����g*/
#define TRIG 							GPIOC, GPIO_Pin_15
#define ECOH 						GPIOC, GPIO_Pin_14

#define PULSE						400.0
//62n 400
//stm 200
#define M_PI							3.141592653
#define R_TO_D(x) 				( (float)(x) * ( 180.0 / M_PI ) )
#define D_TO_R(x)				( (float)(x) * ( M_PI / 180.0 ) )

#endif
