
#include "motor.h"
#include "define.h"
#include "motor_define.h"

#define	MIN_MOTOR_DUTY_PERCENT		5
#define MAX_MOTOR_DUTY_PERCENT		99



void Move_left_tire(float l_duty)
{
	static short i = 0;

	if(fabs(l_duty) > MIN_MOTOR_DUTY_PERCENT){
		if(l_duty < 0){
			if(i != 0){
				Deadtime_left_tire();
				i = 0;
			}else{
				l_duty *= (-1);
				Set_GPIO_output(LEFT_TIRE_CW, LOW);
				Set_GPIO_output(LEFT_TIRE_CCW, HIGH);
				i = 0;
			}
		}else if(l_duty == BRAKE){
			if(i != 1){
				Deadtime_left_tire();
				i = 1;
			}else{
				l_duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(LEFT_TIRE_CW, HIGH);
				Set_GPIO_output(LEFT_TIRE_CCW, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_left_tire();
				i = 2;
			}else{
				Set_GPIO_output(GPIOD, GPIO_Pin_15, HIGH);
				Set_GPIO_output(LEFT_TIRE_CW, HIGH);
				Set_GPIO_output(LEFT_TIRE_CCW, LOW);
				i = 2;
			}
		}

		l_duty = Limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, l_duty);

		Set_duty(LEFT_TIRE_PWM, l_duty / 100);

	}else{
		Deadtime_left_tire();
	}
}

void Move_right_tire(float r_duty)
{
	static short i = 0;

	if(fabs(r_duty) > MIN_MOTOR_DUTY_PERCENT){
		if(r_duty < 0){
			if(i != 0){
				Deadtime_right_tire();
				i = 0;
			}else{
				r_duty *= (-1);
				Set_GPIO_output(RIGHT_TIRE_CW, LOW);
				Set_GPIO_output(RIGHT_TIRE_CCW, HIGH);
				i = 0;
			}
		}else if(r_duty == BRAKE){
			if(i != 1){
				Deadtime_right_tire();
				i = 1;
			}else{
				r_duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(RIGHT_TIRE_CW, HIGH);
				Set_GPIO_output(RIGHT_TIRE_CCW, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_right_tire();
				i = 2;
			}else{
				Set_GPIO_output(RIGHT_TIRE_CW, HIGH);
				Set_GPIO_output(RIGHT_TIRE_CCW, LOW);
				i = 2;
			}
		}

		r_duty = Limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, r_duty);
		Set_duty(RIGHT_TIRE_PWM, (r_duty / 100.0));
	}else{
		Deadtime_right_tire();
	}
}

void Move_back_tire(float b_duty)
{
	static short i = 0;

	if(fabs(b_duty) > MIN_MOTOR_DUTY_PERCENT){
		if(b_duty < 0){
			if(i != 0){
				Deadtime_back_tire();
				i = 0;
			}else{
				b_duty *= (-1);
				Set_GPIO_output(BACK_TIRE_CW, LOW);
				Set_GPIO_output(BACK_TIRE_CCW, HIGH);
				i = 0;
			}
		}else if(b_duty == BRAKE){
			if(i != 1){
				Deadtime_back_tire();
				i = 1;
			}else{
				b_duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(BACK_TIRE_CW, HIGH);
				Set_GPIO_output(BACK_TIRE_CCW, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_back_tire();
				i = 2;
			}else{
				Set_GPIO_output(BACK_TIRE_CW, HIGH);
				Set_GPIO_output(BACK_TIRE_CCW, LOW);
				i = 2;
			}
		}

		b_duty = Limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, b_duty);
		Set_duty(BACK_TIRE_PWM, (b_duty / 100.0));

	}else{
		Deadtime_back_tire();
	}
}

void Move_arm(float arm_duty)
{

	static short i = 0;

	if(fabs(arm_duty) > MIN_MOTOR_DUTY_PERCENT){
		if(arm_duty < 0){
			if(i != 0){
				Deadtime_arm();
				i = 0;
			}else{
				arm_duty *= (-1);
				Set_GPIO_output(ARM_PUSH, LOW);
				Set_GPIO_output(ARM_PULL, HIGH);
				i = 0;
			}
		}else if(arm_duty == BRAKE){
			if(i != 1){
				Deadtime_arm();
				i = 1;
			}else{
				arm_duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(ARM_PUSH, HIGH);
				Set_GPIO_output(ARM_PULL, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_arm();
				i = 2;
			}else{
				Set_GPIO_output(ARM_PUSH, HIGH);
				Set_GPIO_output(ARM_PULL, LOW);
				i = 2;
			}
		}

		arm_duty = Limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, arm_duty);
		Set_duty(ARM_PWM, (arm_duty / 100.0));
	}else{
		Deadtime_arm();
	}
}

void Move(float l_duty, float r_duty, float b_duty)
{
	Move_left_tire(l_duty);
	Move_right_tire(r_duty);
	Move_back_tire(b_duty);
}

void Deadtime_left_tire(void)
{
	Set_GPIO_output(LEFT_TIRE_CW, LOW);
	Set_GPIO_output(LEFT_TIRE_CCW, LOW);
	Set_duty(LEFT_TIRE_PWM, 0.0);
}
void Deadtime_right_tire(void)
{
	Set_GPIO_output(RIGHT_TIRE_CW, LOW);
	Set_GPIO_output(RIGHT_TIRE_CCW, LOW);
	Set_duty(RIGHT_TIRE_PWM, 0.0);
}
void Deadtime_back_tire(void)
{
	Set_GPIO_output(BACK_TIRE_CW, LOW);
	Set_GPIO_output(BACK_TIRE_CCW, LOW);
	Set_duty(BACK_TIRE_PWM, 0.0);
}
void Deadtime_arm(void)
{
	Set_GPIO_output(ARM_PUSH, LOW);
	Set_GPIO_output(ARM_PULL, LOW);
	Set_duty(ARM_PWM, 0.0);
}
void Deadtime_tire(void)
{
	Deadtime_left_tire();
	Deadtime_right_tire();
	Deadtime_back_tire();
}
void Deadtime_all(void)
{
	Deadtime_tire();
	Deadtime_arm();
}

float Convert_duty(float duty)
{
	float convert_duty = 0.0;
	convert_duty = 100.0 - duty;
	return (convert_duty);
}

float get_motor_output_x(float motor_output, float degree)
{
	float motor_output_x = 0.0,
		 degree_reverse = 0.0;

	if(motor_output < 0.0){
		degree_reverse = 180.0;
	}
	motor_output_x = fabs(motor_output) * cos(Convert_to_radian(degree + degree_reverse));

	return (motor_output_x);
}

float get_motor_output_y(float motor_output, float degree)
{
	float motor_output_y = 0.0,
		 degree_reverse = 0.0;

	if(motor_output < 0.0){
		degree_reverse = 180.0;
	}
	motor_output_y = fabs(motor_output) * sin(Convert_to_radian(degree + degree_reverse));

	return (motor_output_y);
}

float get_motor_output_l(float motor_output_x, float motor_output_y, float degree_now)
{
	float 	motor_output_l = 0.0,
			degree_reverse_x = 0.0,
			degree_reverse_y = 0.0;

	if(motor_output_x < 0.0){
		degree_reverse_x = 180.0;
	}else{
		degree_reverse_x = 0.0;
		}
	if(motor_output_y < 0.0){
		degree_reverse_y = 180.0;
	}else{
		degree_reverse_y = 0.0;
	}

	motor_output_l = fabs(motor_output_x) * cos(Convert_to_radian(degree_now + 150.0 + degree_reverse_x));
	motor_output_l += fabs(motor_output_y) * sin(Convert_to_radian(degree_now + 150.0 + degree_reverse_y));
	return(motor_output_l);
}
float get_motor_output_r(float motor_output_x, float motor_output_y, float degree_now)
{
	float 	motor_output_r = 0.0,
			degree_reverse_x = 0.0,
			degree_reverse_y = 0.0;

	if(motor_output_x < 0.0){
		degree_reverse_x = 180.0;
	}else{
		degree_reverse_x = 0.0;
		}
	if(motor_output_y < 0.0){
		degree_reverse_y = 180.0;
	}else{
		degree_reverse_y = 0.0;
	}

	motor_output_r = fabs(motor_output_x) * cos(Convert_to_radian(degree_now + 30.0 + degree_reverse_x));
	motor_output_r += fabs(motor_output_y) * sin(Convert_to_radian(degree_now + 30.0 + degree_reverse_y));
	return(motor_output_r);
}
float get_motor_output_b(float motor_output_x, float motor_output_y, float degree_now)
{
	float 	motor_output_b = 0.0,
			degree_reverse_x = 0.0,
			degree_reverse_y = 0.0;

	if(motor_output_x < 0.0){
		degree_reverse_x = 180.0;
	}else{
		degree_reverse_x = 0.0;
		}
	if(motor_output_y < 0.0){
		degree_reverse_y = 180.0;
	}else{
		degree_reverse_y = 0.0;
	}

	motor_output_b = fabs(motor_output_x) * cos(Convert_to_radian(degree_now - 90.0 + degree_reverse_x));
	motor_output_b += fabs(motor_output_y) * sin(Convert_to_radian(degree_now - 90.0 + degree_reverse_y));
	return(motor_output_b);
}
