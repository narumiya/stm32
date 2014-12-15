#ifndef ROBO_DATA_H
#define ROBO_DATA_H

#include "motor.h"
#include "config_systick.h"
#include "config_port.h"
#include "receive.h"
#include "defines.h"
#include "config_port.h"
#include "name_converter.h"

typedef struct{
	float f;
	float l;
	float r;
}encoder_cnt_t;

typedef struct{
	float c_x;
	float c_y;
	float arm_x;
	float arm_y;
}coord_t;

typedef struct{
	float c_x;
	float c_y;
}old_coord_t;

typedef struct{
	float c_x;
	float c_y;
}finish_coord_t;

typedef struct{
	float degree;
}angle_t;

typedef struct{
	float velocity;
	float angular_velocity;
}velocity_t;

typedef struct{
	float vertical;
	float horizontal;
	float between_two_points;
}distance_t;

typedef struct{
	short start_sw;
	short limit_sw;
}switch_t;

typedef struct{
	coord_t	coord;
	old_coord_t old_coord;
	angle_t angle;
	velocity_t velocity;
	encoder_cnt_t enc_cnt;
	short ad;
	float waves;
	short waves_on;
	switch_t sw;
	float arm_dis;
}robot_information_t;

typedef struct{
	coord_t coord;
	angle_t angle;
	velocity_t velocity;
	distance_t distance;
}target_t;

float Limit_ul(float upper,float lower,float figure);

float pd_rock( float present , float target , float p_gain, float d_gain );

float pd_straight( float  );

float pd_arm_rock( float present , float target , float p_gain, float d_gain , int box);

float get_motor_output_l(float motor_output_x,float motor_output_y,float degree_now,const float degree);

float get_motor_output_r(float motor_output_x,float motor_output_y,float degree_now,const float degree);

float get_motor_output_b(float motor_output_x,float motor_output_y,float degree_now,const float degree);

float get_twopoints_distance( float deviation_x , float deviation_y );

float get_target_degree( float deviation_x , float deviation_y );

float get_horizontal_distance( float degree , float distance );

float get_vertical_distance(float degree , float distance );

float get_target_velocity( float distance_rest , float vertical_distance , float a_up ,  float a_down , float max_velocity);	//rest—]‚è

float get_target_angular_velocity( float degree , float target_degree , float a_up , float a_down );

float get_motor_output_x( float straight , float target_degree );

float get_motor_output_y( float straight , float target_degree );

float revision_degree( float degree );

//void Calculate_Information_3tire(robot_information_t *robot);

void get_robot_inf( robot_information_t *robot );

void init_robot_inf(robot_information_t *robot);

float get_Average( int number_scope, int box, float add );

void sonic_waves(robot_information_t *robot);

void position_rock(robot_information_t *robot, motor_output_t *motor);

void init_arm(robot_information_t *robot);

void arm_length(robot_information_t *robot);

void search(robot_information_t *robot, target_t *target, motor_output_t *motor);

#endif
