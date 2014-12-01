#ifndef MOTOR_H
#define MOTOR_H

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#include "config_pwm.h"
#include "motor_define.h"
#include "defines.h"
#include "robo_data.h"

typedef struct{
	float l;
	float r;
	float b;
	float turn;
	float x;
	float y;
}motor_output_t;

void move_left_tire( float );

void move_right_tire( float );

void move_back_tire( float );

void move_arm(float arm_duty);

void move( float, float, float );

void deadtime(void);

#endif
