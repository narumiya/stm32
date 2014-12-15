#ifndef DEFINES_H
#define DEFINES_H

/*���[�h�ؑ�*/
#define OUTPUT_MODE			AUTO_CONTROL
#define TARGET_SELECT		CAM_DATA
#define CENTER						ON	//�X�g�[���𒆐S�Ɏ����Ă���
#define SERIAL 						ON
#define DEBUG						OFF

#define ABSOLUTE_D				OFF
#define STORN_COORD				OFF
#define FINISH_ARM					ON
#define MOVE_ARM_CAL			OFF
#define STORN_RANGE_CAM	ON

/* ����f�[�^�؂�ւ� */
//#define DEBUG_CAM_DATA 						//�J�����̑f�̃f�[�^�[
#define DEBUG_ROBO_COORD_DATA		//���{�b�g�̎��Ȉʒu
//#define DEBUG_AD_DATA							//�A�[���̋���
//#define DEBUG_TASK
//#define DEBUG_OUTPUT_DATA					//���[�^�[�o��
//#define DEBUG_ENC_DATA						//�G���R�[�_�̒l
//#define DEBUG_TARGET_DATA					//�ڕW�l
//#define DEBUG_TARGET_COORD					//�ڕW���W
//#define DEBUG_VELOCITY_DATA				//���x
//#define CAM_DATA2

#define MAX_VELOCITY			290.0//270.0
#define ROBO_TO_CENTER	1250.0
#define ROBO_TO_ARM			150.0

//#define PC				usb_put_char
#define PC				transmit_usart2_c

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
#define ROCK_P_GAIN				10.0
#define ROCK_D_GAIN				15.0

#define CALIBRA_P_GAIN			100.0
#define CALIBRA_D_GAIN			120.0

#define STRAIGHT_P_GAIN		0.9//0.75
#define STRAIGHT_D_GAIN		0.0

#define ROCK_P_ARMGAIN		2.0
#define ROCK_D_ARMGAIN		3.2

/*�ō����x*/
//#define MAX_VELOCITY						500.0
#define MAX_ANGULAR_VELOCITY	170.0	//�ō��p���x

/* ���荞�݃^�C�� */
#define INTERRUPT_TIME			5.0

#define START_X						0.00
#define START_Y						0.00
#define START_DEGREE				0.00

#define START_PORT					GPIOC, GPIO_Pin_13
//#define START_PORT					GPIOA, GPIO_Pin_0//�}�C�R���ɂ��Ă���X�C�b�`
#define START_SW					GPIO_ReadInputDataBit(START_PORT)
#define BUZZER							GPIOE, GPIO_Pin_1
#define ENC_RESET					GPIOA, GPIO_Pin_5
#define LIMIT_PORT					GPIOC, GPIO_Pin_15
#define LIMIT_SW						GPIO_ReadInputDataBit(LIMIT_PORT)
#define POTENTIO						GPIOC, GPIO_Pin_0

/* PWM �̒�` */
#define MAX_DUTY				100.0
#define FREE							999

/*�X�g�[�����m���ĂȂ�*/
#define UNDISCOVERED		9999
#define OVER_DISCOVERD	8888

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
