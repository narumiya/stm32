#include "robo_finction.h"
#include "robo_data.h"
#include "defines.h"

void buzzer(void)
{
	unsigned int i;

	for(i=0; i<1000000; i++){
		GPIO_SetBits(BUZZER);
	}

	GPIO_ResetBits(BUZZER);
}

void buzzer_cycle( float time )
{
	static float count_time	= 0.00;
	static float off_time		= 0.00;
	static int ignore 				= 0;

	count_time += INTERRUPT_TIME;

	if( count_time <= time ){
		GPIO_SetBits(BUZZER);
	}else{
		ignore	= 1;
	}
	if( ignore == 1 ){
		off_time += INTERRUPT_TIME;
		GPIO_ResetBits(BUZZER);
	}
	if( off_time >= time ){
		count_time	= 0.00;
		off_time 		= 0.00;
		ignore			= 0;
	}
}

void buzzer_stop(void)
{
	GPIO_ResetBits(BUZZER);
}

void buzzer_on(void)
{
	GPIO_SetBits(BUZZER);
}

void initialize(robot_information_t *robot, target_t *target )
{
	GPIO_SetBits(ENC_RESET);
	robot->angle.degree = 0.00;
	robot->coord.c_x = 0.00;
	robot->coord.c_y = 0.00;
	robot->old_coord.c_x= 0.00;
	robot->old_coord.c_y= 0.00;
	robot->enc_cnt.f= 0.00;
	robot->enc_cnt.r= 0.00;
	robot->enc_cnt.l= 0.00;
	robot->velocity.velocity = 0.00;
	robot->velocity.angular_velocity = 0.00;
	robot->waves = 0.00;
	robot->sw.start_sw = 0;
	robot->sw.limit_sw = 0;
	target->angle.degree = 0.00;
	target->coord.c_x = 0.00;
	target->coord.c_y = 0.00;
	target->distance.between_two_points = 0.00;
	target->distance.horizontal = 0.00;
	target->distance.vertical = 0.00;
	target->velocity.velocity = 0.00;
	target->velocity.angular_velocity = 0.00;
	deadtime();
}

float Absolute_duty(float max_duty, float target, float now){

	float output_duty = 0.00,
			percentage = 0.00;

	if(target != 0.00) percentage = fabs(now / target);

	if(percentage >= 1.00){
		output_duty = 0.00;
	}else{
		output_duty = max_duty * (1.00 - percentage);
	}

	return (output_duty);
}
