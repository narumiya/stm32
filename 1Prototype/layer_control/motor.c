
#include "motor.h"

#define	MIN_MOTOR_DUTY_PERCENT		5
#define MAX_MOTOR_DUTY_PERCENT		95
#define DEADTIME_TIMER_MAX_MS		10

void Move_motor_0(float duty)
{
	static short i = 0;
	static int deadtime_timer = 0;


	if(duty == BRAKE){
		duty = 0.0;
	}

	if(fabs(duty) > MIN_MOTOR_DUTY_PERCENT){
		if(duty < 0){
			if(i != 0){
				Deadtime_motor_0();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 0;
				}
			}else{
				deadtime_timer = 0;
				duty *= (-1);
				Set_GPIO_output(MOTOR_0_PIN0, LOW);
				Set_GPIO_output(MOTOR_0_PIN1, HIGH);
				i = 0;
			}
		}else if(duty == BRAKE){
			if(i != 1){
				Deadtime_motor_0();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 1;
				}
			}else{
				deadtime_timer = 0;
				duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(MOTOR_0_PIN0, HIGH);
				Set_GPIO_output(MOTOR_0_PIN1, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_motor_0();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 2;
				}
			}else{
				deadtime_timer = 0;
				Set_GPIO_output(MOTOR_0_PIN0, HIGH);
				Set_GPIO_output(MOTOR_0_PIN1, LOW);
				i = 2;
			}
		}

		duty = limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, duty);
		//duty = 100 - duty;

		Set_duty(MOTOR_0_TIM_CH, duty / 100);

	}else{
		Deadtime_motor_0();
	}
}

void Move_motor_1(float duty)
{
	static short i = 0;
	static int deadtime_timer = 0;


	if(duty == BRAKE){
		duty = 0.0;
	}

	if(fabs(duty) > MIN_MOTOR_DUTY_PERCENT){
		if(duty < 0){
			if(i != 0){
				Deadtime_motor_1();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 0;
				}
			}else{
				deadtime_timer = 0;
				duty *= (-1);
				Set_GPIO_output(MOTOR_1_PIN0, LOW);
				Set_GPIO_output(MOTOR_1_PIN1, HIGH);
				i = 0;
			}
		}else if(duty == BRAKE){
			if(i != 1){
				Deadtime_motor_1();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 1;
				}
			}else{
				deadtime_timer = 1;
				duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(MOTOR_1_PIN0, HIGH);
				Set_GPIO_output(MOTOR_1_PIN1, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_motor_1();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 2;
				}
			}else{
				deadtime_timer = 0;
				Set_GPIO_output(MOTOR_1_PIN0, HIGH);
				Set_GPIO_output(MOTOR_1_PIN1, LOW);
				i = 2;
			}
		}

		duty = limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, duty);
		//duty = 100 - duty;

		Set_duty(MOTOR_1_TIM_CH, duty / 100);

	}else{
		Deadtime_motor_1();
	}
}

void Move_motor_2(float duty)
{
	static short i = 0;
	static int deadtime_timer = 0;


	if(duty == BRAKE){
		duty = 0.0;
	}

	if(fabs(duty) > MIN_MOTOR_DUTY_PERCENT){
		if(duty < 0){
			if(i != 0){
				Deadtime_motor_2();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 0;
				}
			}else{
				deadtime_timer = 0;
				duty *= (-1);
				Set_GPIO_output(MOTOR_2_PIN0, LOW);
				Set_GPIO_output(MOTOR_2_PIN1, HIGH);
				i = 0;
			}
		}else if(duty == BRAKE){
			if(i != 1){
				Deadtime_motor_2();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 1;
				}
			}else{
				deadtime_timer = 0;
				duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(MOTOR_2_PIN0, HIGH);
				Set_GPIO_output(MOTOR_2_PIN1, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_motor_2();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 2;
				}
			}else{
				deadtime_timer = 0;
				Set_GPIO_output(MOTOR_2_PIN0, HIGH);
				Set_GPIO_output(MOTOR_2_PIN1, LOW);
				i = 2;
			}
		}

		duty = limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, duty);
		//duty = 100 - duty;

		Set_duty(MOTOR_2_TIM_CH, duty / 100);

	}else{
		Deadtime_motor_2();
	}
}
void Move_motor_3(float duty)
{
	static short i = 0;
	static int deadtime_timer = 0;


	if(duty == BRAKE){
		duty = 0.0;
	}

	if(fabs(duty) > MIN_MOTOR_DUTY_PERCENT){
		if(duty < 0){
			if(i != 0){
				Deadtime_motor_3();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 0;
				}
			}else{
				deadtime_timer = 0;
				duty *= (-1);
				Set_GPIO_output(MOTOR_3_PIN0, LOW);
				Set_GPIO_output(MOTOR_3_PIN1, HIGH);
				i = 0;
			}
		}else if(duty == BRAKE){
			if(i != 1){
				Deadtime_motor_3();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 1;
				}
			}else{
				deadtime_timer = 0;
				duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(MOTOR_3_PIN0, HIGH);
				Set_GPIO_output(MOTOR_3_PIN1, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_motor_3();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 2;
				}
			}else{
				deadtime_timer = 0;
				Set_GPIO_output(MOTOR_3_PIN0, HIGH);
				Set_GPIO_output(MOTOR_3_PIN1, LOW);
				i = 2;
			}
		}

		duty = limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, duty);
		//duty = 100 - duty;

		Set_duty(MOTOR_3_TIM_CH, duty / 100);

	}else{
		Deadtime_motor_3();
	}
}
void Move_motor_4(float duty)
{
	static short i = 0;
	static int deadtime_timer = 0;


	if(duty == BRAKE){
		duty = 0.0;
	}

	if(fabs(duty) > MIN_MOTOR_DUTY_PERCENT){
		if(duty < 0){
			if(i != 0){
				Deadtime_motor_4();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 0;
				}
			}else{
				deadtime_timer = 0;
				duty *= (-1);
				Set_GPIO_output(MOTOR_4_PIN0, LOW);
				Set_GPIO_output(MOTOR_4_PIN1, HIGH);
				i = 0;
			}
		}else if(duty == BRAKE){
			if(i != 1){
				Deadtime_motor_4();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 1;
				}
			}else{
				deadtime_timer = 0;
				duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(MOTOR_4_PIN0, HIGH);
				Set_GPIO_output(MOTOR_4_PIN1, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_motor_4();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 2;
				}
			}else{
				deadtime_timer = 0;
				Set_GPIO_output(MOTOR_4_PIN0, HIGH);
				Set_GPIO_output(MOTOR_4_PIN1, LOW);
				i = 2;
			}
		}

		duty = limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, duty);
		//duty = 100 - duty;

		Set_duty(MOTOR_4_TIM_CH, duty / 100);

	}else{
		Deadtime_motor_4();
	}
}
void Move_motor_5(float duty)
{
	static short i = 0;
	static int deadtime_timer = 0;


	if(duty == BRAKE){
		duty = 0.0;
	}

	if(fabs(duty) > MIN_MOTOR_DUTY_PERCENT){
		if(duty < 0){
			if(i != 0){
				Deadtime_motor_5();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 0;
				}
			}else{
				deadtime_timer = 0;
				duty *= (-1);
				Set_GPIO_output(MOTOR_5_PIN0, LOW);
				Set_GPIO_output(MOTOR_5_PIN1, HIGH);
				i = 0;
			}
		}else if(duty == BRAKE){
			if(i != 1){
				Deadtime_motor_5();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 1;
				}
			}else{
				deadtime_timer = 0;
				duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(MOTOR_5_PIN0, HIGH);
				Set_GPIO_output(MOTOR_5_PIN1, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_motor_5();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 2;
				}
			}else{
				deadtime_timer = 0;
				Set_GPIO_output(MOTOR_5_PIN0, HIGH);
				Set_GPIO_output(MOTOR_5_PIN1, LOW);
				i = 2;
			}
		}

		duty = limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, duty);
		//duty = 100 - duty;

		Set_duty(MOTOR_5_TIM_CH, duty / 100);

	}else{
		Deadtime_motor_5();
	}
}
void Move_motor_6(float duty)
{
	static short i = 0;
	static int deadtime_timer = 0;


	if(duty == BRAKE){
		duty = 0.0;
	}

	if(fabs(duty) > MIN_MOTOR_DUTY_PERCENT){
		if(duty < 0){
			if(i != 0){
				Deadtime_motor_6();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 0;
				}
			}else{
				deadtime_timer = 0;
				duty *= (-1);
				Set_GPIO_output(MOTOR_6_PIN0, LOW);
				Set_GPIO_output(MOTOR_6_PIN1, HIGH);
				i = 0;
			}
		}else if(duty == BRAKE){
			if(i != 1){
				Deadtime_motor_6();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 1;
				}
			}else{
				deadtime_timer = 0;
				duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(MOTOR_6_PIN0, HIGH);
				Set_GPIO_output(MOTOR_6_PIN1, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_motor_6();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 2;
				}
			}else{
				deadtime_timer = 0;
				Set_GPIO_output(MOTOR_6_PIN0, HIGH);
				Set_GPIO_output(MOTOR_6_PIN1, LOW);
				i = 2;
			}
		}

		duty = limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, duty);
		//duty = 100 - duty;

		Set_duty(MOTOR_6_TIM_CH, duty / 100);

	}else{
		Deadtime_motor_6();
	}
}
void Move_motor_7(float duty)
{
	static short i = 0;
	static int deadtime_timer = 0;


	if(duty == BRAKE){
		duty = 0.0;
	}

	if(fabs(duty) > MIN_MOTOR_DUTY_PERCENT){
		if(duty < 0){
			if(i != 0){
				Deadtime_motor_7();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 0;
				}
			}else{
				deadtime_timer = 0;
				duty *= (-1);
				Set_GPIO_output(MOTOR_7_PIN0, LOW);
				Set_GPIO_output(MOTOR_7_PIN1, HIGH);
				i = 0;
			}
		}else if(duty == BRAKE){
			if(i != 1){
				Deadtime_motor_7();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 1;
				}
			}else{
				deadtime_timer = 0;
				duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(MOTOR_7_PIN0, HIGH);
				Set_GPIO_output(MOTOR_7_PIN1, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_motor_7();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 2;
				}
			}else{
				deadtime_timer = 0;
				Set_GPIO_output(MOTOR_7_PIN0, HIGH);
				Set_GPIO_output(MOTOR_7_PIN1, LOW);
				i = 2;
			}
		}

		duty = limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, duty);
		//duty = 100 - duty;

		Set_duty(MOTOR_7_TIM_CH, duty / 100);

	}else{
		Deadtime_motor_7();
	}
}
void Move_motor_8(float duty)
{
	static short i = 0;
	static int deadtime_timer = 0;


	if(duty == BRAKE){
		duty = 0.0;
	}

	if(fabs(duty) > MIN_MOTOR_DUTY_PERCENT){
		if(duty < 0){
			if(i != 0){
				Deadtime_motor_8();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 0;
				}
			}else{
				deadtime_timer = 0;
				duty *= (-1);
				Set_GPIO_output(MOTOR_8_PIN0, LOW);
				Set_GPIO_output(MOTOR_8_PIN1, HIGH);
				i = 0;
			}
		}else if(duty == BRAKE){
			if(i != 1){
				Deadtime_motor_8();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 1;
				}
			}else{
				deadtime_timer = 0;
				duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(MOTOR_8_PIN0, HIGH);
				Set_GPIO_output(MOTOR_8_PIN1, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_motor_8();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 2;
				}
			}else{
				deadtime_timer = 0;
				Set_GPIO_output(MOTOR_8_PIN0, HIGH);
				Set_GPIO_output(MOTOR_8_PIN1, LOW);
				i = 2;
			}
		}

		duty = limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, duty);
		//duty = 100 - duty;

		Set_duty(MOTOR_8_TIM_CH, duty / 100);

	}else{
		Deadtime_motor_8();
	}
}
void Move_motor_9(float duty)
{
	static short i = 0;
	static int deadtime_timer = 0;


	if(duty == BRAKE){
		duty = 0.0;
	}

	if(fabs(duty) > MIN_MOTOR_DUTY_PERCENT){
		if(duty < 0){
			if(i != 0){
				Deadtime_motor_9();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 0;
				}
			}else{
				deadtime_timer = 0;
				duty *= (-1);
				Set_GPIO_output(MOTOR_9_PIN0, LOW);
				Set_GPIO_output(MOTOR_9_PIN1, HIGH);
				i = 0;
			}
		}else if(duty == BRAKE){
			if(i != 1){
				Deadtime_motor_9();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 1;
				}
			}else{
				deadtime_timer = 0;
				duty = MAX_MOTOR_DUTY_PERCENT;
				Set_GPIO_output(MOTOR_9_PIN0, HIGH);
				Set_GPIO_output(MOTOR_9_PIN1, HIGH);
				i = 1;
			}
		}else{
			if(i != 2){
				Deadtime_motor_9();
				deadtime_timer += INTERRUPT_TIME_MS;
				if(deadtime_timer >= DEADTIME_TIMER_MAX_MS){
					deadtime_timer = 0;
					i = 2;
				}
			}else{
				deadtime_timer = 0;
				Set_GPIO_output(MOTOR_9_PIN0, HIGH);
				Set_GPIO_output(MOTOR_9_PIN1, LOW);
				i = 2;
			}
		}

		duty = limit_ul(MAX_MOTOR_DUTY_PERCENT , 0, duty);
		//duty = 100 - duty;

		Set_duty(MOTOR_9_TIM_CH, duty / 100);

	}else{
		Deadtime_motor_9();
	}
}

void Move_motor_number(float duty, unsigned char number)
{
	switch (number) {
		case 0:
			Move_motor_0(duty);
			break;
		case 1:
			Move_motor_1(duty);
			break;
		case 2:
			Move_motor_2(duty);
			break;
		case 3:
			Move_motor_3(duty);
			break;
		case 4:
			Move_motor_4(duty);
			break;
		case 5:
			Move_motor_5(duty);
			break;
		case 6:
			Move_motor_6(duty);
			break;
		case 7:
			Move_motor_7(duty);
			break;
		case 8:
			Move_motor_8(duty);
			break;
		case 9:
			Move_motor_9(duty);
			break;
		default:
			Deadtime_all();
			break;
	}
}


void Move_left_f_tire(float duty)
{
	Move_motor_number(duty, LEFT_F_TIRE);
}
void Move_left_b_tire(float duty)
{
	Move_motor_number(duty, LEFT_B_TIRE);
}
void Move_right_f_tire(float duty)
{
	Move_motor_number(duty, RIGHT_F_TIRE);
}
void Move_right_b_tire(float duty)
{
	Move_motor_number(duty, RIGHT_B_TIRE);
}
void Move_top_racket_reload_motor(float duty)
{
	Move_motor_number(duty, TOP_RACKET_RELOAD_MOTOR);
}
void Move_top_racket_release_motor(float duty)
{
	Move_motor_number(duty, TOP_RACKET_RELEASE_MOTOR);
}
/*
void Move_result(Underbody_tire_t result)
{
	Move(result.l_f, result.l_b, result.r_f, result.r_b);
}

void Move(float l_f_duty, float l_b_duty, float r_f_duty, float r_b_duty)
{
	Move_left_f_tire(l_f_duty);
	Move_left_b_tire(l_b_duty);
	Move_right_f_tire(r_f_duty);
	Move_right_b_tire(r_b_duty);
}*/

void Deadtime_motor_0(void)
{
	Set_GPIO_output(MOTOR_0_PIN0, LOW);
	Set_GPIO_output(MOTOR_0_PIN1, LOW);
	Set_duty(MOTOR_0_TIM_CH, 0.0);
}
void Deadtime_motor_1(void)
{
	Set_GPIO_output(MOTOR_1_PIN0, LOW);
	Set_GPIO_output(MOTOR_1_PIN1, LOW);
	Set_duty(MOTOR_1_TIM_CH, 0.0);
}
void Deadtime_motor_2(void)
{
	Set_GPIO_output(MOTOR_2_PIN0, LOW);
	Set_GPIO_output(MOTOR_2_PIN1, LOW);
	Set_duty(MOTOR_2_TIM_CH, 0.0);
}
void Deadtime_motor_3(void)
{
	Set_GPIO_output(MOTOR_3_PIN0, LOW);
	Set_GPIO_output(MOTOR_3_PIN1, LOW);
	Set_duty(MOTOR_3_TIM_CH, 0.0);
}
void Deadtime_motor_4(void)
{
	Set_GPIO_output(MOTOR_4_PIN0, LOW);
	Set_GPIO_output(MOTOR_4_PIN1, LOW);
	Set_duty(MOTOR_4_TIM_CH, 0.0);
}
void Deadtime_motor_5(void)
{
	Set_GPIO_output(MOTOR_5_PIN0, LOW);
	Set_GPIO_output(MOTOR_5_PIN1, LOW);
	Set_duty(MOTOR_5_TIM_CH, 0.0);
}
void Deadtime_motor_6(void)
{
	Set_GPIO_output(MOTOR_6_PIN0, LOW);
	Set_GPIO_output(MOTOR_6_PIN1, LOW);
	Set_duty(MOTOR_6_TIM_CH, 0.0);
}
void Deadtime_motor_7(void)
{
	Set_GPIO_output(MOTOR_7_PIN0, LOW);
	Set_GPIO_output(MOTOR_7_PIN1, LOW);
	Set_duty(MOTOR_7_TIM_CH, 0.0);
}
void Deadtime_motor_8(void)
{
	Set_GPIO_output(MOTOR_8_PIN0, LOW);
	Set_GPIO_output(MOTOR_8_PIN1, LOW);
	Set_duty(MOTOR_8_TIM_CH, 0.0);
}
void Deadtime_motor_9(void)
{
	Set_GPIO_output(MOTOR_9_PIN0, LOW);
	Set_GPIO_output(MOTOR_9_PIN1, LOW);
	Set_duty(MOTOR_9_TIM_CH, 0.0);
}

void Deadtime_motor_number(unsigned char number)
{
	switch (number) {
		case 0:
			Deadtime_motor_0();
			break;
		case 1:
			Deadtime_motor_1();
			break;
		case 2:
			Deadtime_motor_2();
			break;
		case 3:
			Deadtime_motor_3();
			break;
		case 4:
			Deadtime_motor_4();
			break;
		case 5:
			Deadtime_motor_5();
			break;
		case 6:
			Deadtime_motor_6();
			break;
		case 7:
			Deadtime_motor_7();
			break;
		case 8:
			Deadtime_motor_8();
			break;
		case 9:
			Deadtime_motor_9();
			break;
		default:
			Deadtime_all();
			break;
	}
}

void Deadtime_left_f_tire(void)
{
	Deadtime_motor_number(LEFT_F_TIRE);
}
void Deadtime_left_b_tire(void)
{
	Deadtime_motor_number(LEFT_B_TIRE);
}
void Deadtime_right_f_tire(void)
{
	Deadtime_motor_number(RIGHT_F_TIRE);
}
void Deadtime_right_b_tire(void)
{
	Deadtime_motor_number(RIGHT_B_TIRE);
}
void Deadtime_top_racket_reload_motor(void)
{
	Deadtime_motor_number(TOP_RACKET_RELEASE_MOTOR);
}

void Deadtime_top_racket_release_motor(void)
{
	Deadtime_motor_number(TOP_RACKET_RELEASE_MOTOR);
}

void Deadtime_tire(void)
{
	Deadtime_left_f_tire();
	Deadtime_left_b_tire();
	Deadtime_right_f_tire();
	Deadtime_right_b_tire();
}

void Deadtime_racket_motor(void)
{
	Deadtime_top_racket_release_motor();
	Deadtime_top_racket_reload_motor();
}

void Deadtime_all(void)
{
	unsigned char i = 0;
	for(i = 0; i < 10; i ++){
		Deadtime_motor_number(i);
	}
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
	motor_output_x = fabs(motor_output) * cos(convert_to_radian(degree + degree_reverse));

	return (motor_output_x);
}

float get_motor_output_y(float motor_output, float degree)
{
	float motor_output_y = 0.0,
		 degree_reverse = 0.0;

	if(motor_output < 0.0){
		degree_reverse = 180.0;
	}
	motor_output_y = fabs(motor_output) * sin(convert_to_radian(degree + degree_reverse));

	return (motor_output_y);
}

float get_motor_output_l_f(float motor_output_x, float motor_output_y, float degree_now)
{
	float 	motor_output_l_f = 0.0,
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

	motor_output_l_f = fabs(motor_output_x) * cos(convert_to_radian(degree_now + 135.0 + degree_reverse_x));
	motor_output_l_f += fabs(motor_output_y) * sin(convert_to_radian(degree_now + 135.0 + degree_reverse_y));
	return(motor_output_l_f);
}
float get_motor_output_l_b(float motor_output_x, float motor_output_y, float degree_now)
{
	float 	motor_output_l_b = 0.0,
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

	motor_output_l_b = fabs(motor_output_x) * cos(convert_to_radian(degree_now - 135.0 + degree_reverse_x));
	motor_output_l_b += fabs(motor_output_y) * sin(convert_to_radian(degree_now - 135.0 + degree_reverse_y));
	return(motor_output_l_b);
}
float get_motor_output_r_f(float motor_output_x, float motor_output_y, float degree_now)
{
	float 	motor_output_r_f = 0.0,
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

	motor_output_r_f = fabs(motor_output_x) * cos(convert_to_radian(degree_now + 45.0 + degree_reverse_x));
	motor_output_r_f += fabs(motor_output_y) * sin(convert_to_radian(degree_now + 45.0 + degree_reverse_y));
	return(motor_output_r_f);
}

float get_motor_output_r_b(float motor_output_x, float motor_output_y, float degree_now)
{
	float 	motor_output_r_b = 0.0,
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

	motor_output_r_b = fabs(motor_output_x) * cos(convert_to_radian(degree_now - 45.0 + degree_reverse_x));
	motor_output_r_b += fabs(motor_output_y) * sin(convert_to_radian(degree_now - 45.0 + degree_reverse_y));
	return(motor_output_r_b);
}
