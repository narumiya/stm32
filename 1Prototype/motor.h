
#ifndef MOTOR_H
#define MOTOR_H


#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"

#include "config_pwm.h"
#include "config_port.h"
#include "calculate.h"
#include <math.h>

#define PWM_FREQUENCY	1000	//10kHzÇ…ê›íË

void Move_left_tire(float l_duty);
void Move_right_tire(float r_duty);
void Move_back_tire(float b_duty);
void Move(float l_duty, float r_duty, float b_duty);
void Move_arm(float arm_duty);
void Deadtime_left_tire(void);
void Deadtime_right_tire(void);
void Deadtime_back_tire(void);
void Deadtime_arm(void);
void Deadtime_tire(void);
void Deadtime_all(void);
float get_motor_output_x(float motor_output, float degree);
float get_motor_output_y(float motor_output, float degree);
float get_motor_output_l(float motor_output_x, float motor_output_y, float degree_now);
float get_motor_output_r(float motor_output_x, float motor_output_y, float degree_now);
float get_motor_output_b(float motor_output_x, float motor_output_y, float degree_now);

#endif
