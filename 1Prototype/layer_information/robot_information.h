#ifndef ROBOT_INFORMATION_H
#define ROBOT_INFORMATION_H

#include <math.h>
#include "config_encoder.h"
#include "calculate.h"
#include "config_adc.h"
#include "define.h"
#include "my_standard_io.h"


#define START_X			0
#define START_Y			0
#define START_DEGREE	0






//すべてのラケット情報構造体
typedef struct{
	Racket_each_information_t top;
	Racket_each_information_t right;
}Racket_all_information_t;


//自己位置情報構造体
typedef struct{
	Encoder_t enc_tire[ENCODER_TIRE_SUM];
	Coordinate_t coord;
	Angle_t angle;
	Angle_t omega;
	Velocity_t velocity;
}Robot_center_information_t;

typedef struct{
	short LjoyX;
	short LjoyY;
	short RjoyX;
	short RjoyY;

	short robot_LjoyX;
	short robot_LjoyY;
	short robot_RjoyX;
	short robot_RjoyY;

	unsigned short Up;
	unsigned short Right;
	unsigned short Down;
	unsigned short Left;
	unsigned short Triangle;
	unsigned short Circle;
	unsigned short Cross;
	unsigned short Square;
	unsigned short Start;
	unsigned short Select;
	unsigned short PS;
	unsigned short AccX;
	unsigned short AccY;
	unsigned short L1;
	unsigned short L2;
	unsigned short R1;
	unsigned short R2;

	unsigned short connect;
	unsigned short error;
}PS3_Controller_t;

//ロボット情報構造体
typedef struct{
	Robot_center_information_t center;
	Racket_all_information_t racket;
	PS3_Controller_t ps3;
}Robot_all_information_t;


typedef struct{
	float kp;
	float ki;
	float kd;
}Gain_t;



void Init_Robot_center_infomation(Robot_center_information_t *robot);
void Init_button_information(Button_information_t *button);
void Init_potentio(Potentio_t *potentio);

void calculate_information_center(Robot_center_information_t *robot, unsigned char *flag_safety);

void get_button_information(int chattaring_timer, GPIO_TypeDef *GPIOx, uint16_t pin,Button_information_t *button);


#endif
