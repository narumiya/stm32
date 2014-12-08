#include <math.h>

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

/* マイコンの設定 */
#include "config_adc.h"
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
#include "motor_define.h"
#include "motor.h"
#include "cam_cal.h"
#include "chata.h"
#include "debug.h"
#include "defines.h"

typedef struct{
	float target_x;
	float target_y;
}target_coord_t;

void all_config(void)
{
	SystemInit();
	Init_SysTick(0.001);					//1ms割り込み
	//Init_micro_interrupt(TIM2);		//1us割り込み
	Init_ADC1(POTENTIO);
	Init_PWM(RIGHT_TIRE_PWMSET, 10000);				//左タイヤモーター
	Init_PWM(LEFT_TIRE_PWMSET, 10000);		//右タイヤモーター
	Init_PWM(BACK_TIRE_PWMSET, 10000);			//後ろタイヤモーター
	Init_PWM(ARM_PWMSET, 10000);												//アームモーター
	//Init_USART(USART2, 115200, GPIOD, GPIO_Pin_5, GPIOD, GPIO_Pin_6);
	Init_USART(USART3, 115200, GPIOD, GPIO_Pin_8, GPIOD, GPIO_Pin_9);
	//Init_encoder(TIM4, GPIOB, GPIO_Pin_6 | GPIO_Pin_7);	//左エンコ
	//Init_encoder(TIM5, GPIOA, GPIO_Pin_0 | GPIO_Pin_1);	//右エンコ
	//Init_encoder(TIM8, GPIOC, GPIO_Pin_6 | GPIO_Pin_7);	//前エンコ
	Init_usb();
}

void port_config(void)
{
	Init_port(GPIO_Mode_OUT, GPIOD, GPIO_Pin_14 | GPIO_Pin_15, GPIO_PuPd_UP, GPIO_OType_PP);//LED
	Init_port(GPIO_Mode_IN, START_PORT, GPIO_PuPd_DOWN, GPIO_OType_PP);//スタートスイッチ
	Init_port(GPIO_Mode_IN, LIMIT_PORT, GPIO_PuPd_NOPULL, GPIO_OType_PP);//リミットスイッチ
	Init_port(GPIO_Mode_OUT, BUZZER, GPIO_PuPd_UP, GPIO_OType_PP);//buzzer
	Init_port(GPIO_Mode_OUT, ENC_RESET, GPIO_PuPd_UP, GPIO_OType_PP);//エンコーダリセットポート

	Init_port(GPIO_Mode_OUT, RIGHT_TIRE_CWSET);
	Init_port(GPIO_Mode_OUT, RIGHT_TIRE_CCWSET);
	Init_port(GPIO_Mode_OUT, LEFT_TIRE_CWSET);
	Init_port(GPIO_Mode_OUT, LEFT_TIRE_CCWSET);
	Init_port(GPIO_Mode_OUT, BACK_TIRE_CWSET);
	Init_port(GPIO_Mode_OUT, BACK_TIRE_CCWSET);
	Init_port(GPIO_Mode_OUT, ARM_PUSHSET);
	Init_port(GPIO_Mode_OUT, ARM_PULLSET);
	//Init_port(GPIO_Mode_OUT,TRIG, GPIO_PuPd_UP, GPIO_OType_PP);	//超音波
	//Init_port(GPIO_Mode_IN, ECOH, GPIO_PuPd_NOPULL, GPIO_OType_PP);//超音波
}

int main(void)
{
	robot_information_t		robot;
	target_t						target;
	target_cam_t				target_cam={0};
	motor_output_t			motor = {0};

#if  TARGET_SELECT == COORDINATE
	target_coord_t			target_coord[4]=
													{	{200, 0},
														{0, 0},
														{-200, 0},
														{0, 0}
													};
#endif

	float		straight = 0.00,
				add_output = 0.00,
				old_velocity = 0.00;

	unsigned short	start_sw = 0,
								task = 0,
								debug_task = 0,
								action_task = 0,
								task_flag = 0,
								flag = 0,
								finish = 0;

	all_config();
	port_config();
	initialize(&robot, &target);
	init_robot_inf(&robot);
	buzzer();

    while(1){
    	//sonic_waves(&robot);

    	if( count_time(0) >= INTERRUPT_TIME ){
    		reset_count_time(0);

    		get_robot_inf( &robot );
    		arm_length(&robot);
    		start_sw = positive_chattering(START_SW,0);

			if( start_sw == EDGE_DOWN ){
				 robot.sw.start_sw = ON;
			}

			if(robot.sw.start_sw != ON){
				initialize(&robot, &target);
			}

#if TARGET_SELECT == COORDINATE
			target.coord.c_x = target_coord[task].target_x;
			target.coord.c_y = target_coord[task].target_y;

#elif TARGET_SELECT == CAM_DATA
			cam_data(&target_cam, &robot);

			switch(action_task){
			case 0:
				//ストーン検知してない
				if( target_cam.x == UNDISCOVERED && target_cam.y == UNDISCOVERED ){
					switch(task){
						case 0:
							target.coord.c_x = robot.coord.c_x;
							target.coord.c_y = 280.0;
						break;
						case 1:
							target.coord.c_x = robot.coord.c_x;
							target.coord.c_y = 0.0;
						break;
						case 2:
							target.coord.c_x = robot.coord.c_x;
							target.coord.c_y = -280.0;
						break;
					}
					buzzer_stop();
					debug_task = 0;
					//move_arm(pd_arm_rock(robot.arm_dis, 60, ROCK_P_ARMGAIN, ROCK_D_ARMGAIN));
					target.distance.between_two_points = get_twopoints_distance( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
					#if ABSOLUTE_D == ON
						if(target.distance.between_two_points < 10){
							add_output = get_Average(20, 1, Absolute_duty(20.0, 35.0, robot.velocity.velocity));
						}else{
							add_output = 0.00;
						}
						#else
						add_output = 0.00;
					#endif
					target.angle.degree = get_target_degree( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
					target.distance.vertical = get_vertical_distance(target.angle.degree, target.distance.between_two_points);
					target.velocity.velocity = get_target_velocity(target.distance.between_two_points, target.distance.vertical, 500.0, 400.0, 110.0);
					//straight = pd_straight(target.distance.between_two_points);
					straight = pd_straight(target.velocity.velocity - robot.velocity.velocity);
					motor.x = get_motor_output_x(straight + add_output, target.angle.degree);
					motor.y = get_motor_output_y(straight + add_output, target.angle.degree);

					if(target.distance.between_two_points < 2.0){
						task ++;
					}
					if(task >= 3){
						task = 0;
					}

					//ストーン押せる範囲に入った
				}else if( -10.0 <= target_cam.y && target_cam.y <= 10.0){
					task_flag ++;
					debug_task = 2;
					if(task_flag >= 200){
						action_task = 1;
					}
					//ストーン検知したが押せる範囲にはいってない
				}else{
					move_arm(pd_arm_rock(robot.arm_dis, 0, ROCK_P_ARMGAIN, ROCK_D_ARMGAIN));
					task_flag = 0;
					target.coord.c_x = robot.coord.c_x;
					target.coord.c_y = target_cam.y + robot.coord.c_y;

					if(robot.coord.c_y > 0 && target.coord.c_y < 0){
						//debug_task = 4;
					}else if(robot.coord.c_y > 0 && target.coord.c_y < 0){
						//debug_task = 5;
					}

					debug_task = 1;
					target.distance.between_two_points = get_twopoints_distance(target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
					#if ABSOLUTE_D == ON
						if(target.distance.between_two_points > 10){
							add_output = get_Average(20, 2, Absolute_duty(20.0, 35.0, robot.velocity.velocity));
						}else{
							add_output = 0.00;
						}
						#else
						add_output = 0.00;
					#endif
					target.angle.degree = get_target_degree( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
					target.distance.vertical = get_vertical_distance( target.angle.degree, target.distance.between_two_points );
					target.velocity.velocity = get_target_velocity( target.distance.between_two_points, target.distance.vertical, 500.0, 400.0, 110.0);
					//straight = pd_straight(target.distance.between_two_points);
					straight = pd_straight( target.velocity.velocity - robot.velocity.velocity);
					motor.x = get_motor_output_x(straight + add_output, target.angle.degree);
					motor.y = get_motor_output_y(straight + add_output, target.angle.degree);
					buzzer_cycle(1500.0);
				}
			break;
			case 1:
				if(flag == 0){
					target.angle.degree = (-1) * get_target_degree(1250 - robot.coord.c_x, robot.coord.c_y);
					target.coord.c_x = target_cam.x + robot.coord.c_x + 5.0 * cos(D_TO_R(target.angle.degree));
					target.coord.c_y = target_cam.y + robot.coord.c_y + 5.0 * sin(D_TO_R(target.angle.degree));
					flag = 1;
				}
				move_arm(pd_arm_rock(robot.arm_dis, 150, ROCK_P_ARMGAIN, ROCK_D_ARMGAIN));
				debug_task = 3;
				target.distance.between_two_points = get_twopoints_distance( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				target.angle.degree = get_target_degree( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				#if ABSOLUTE_D == ON
					if(target.distance.between_two_points > 10){
						add_output = get_Average(20, 3, Absolute_duty(20.0, 35.0, robot.velocity.velocity));
					}else{
						add_output = 0.00;
					}
					#else
					add_output = 0.00;
				#endif
				target.distance.vertical = get_vertical_distance( target.angle.degree, target.distance.between_two_points );
				target.velocity.velocity = get_target_velocity( target.distance.between_two_points, target.distance.vertical, 500.0, 400.0, 110.0);
				//straight = pd_straight(target.distance.between_two_points);
				straight = pd_straight(target.velocity.velocity - robot.velocity.velocity);
				motor.x = get_motor_output_x(straight + add_output, target.angle.degree);
				motor.y = get_motor_output_y(straight + add_output, target.angle.degree);
				buzzer_cycle(800.0);

				if(target.distance.between_two_points < 5.0){
					action_task = 2;
					robot.old_coord.c_x = robot.coord.c_x;
					robot.old_coord.c_y = robot.coord.c_y;
				}
			break;
			case 2:
				if(flag == 1){
					target.coord.c_x = robot.old_coord.c_x - 200.0;
					target.coord.c_y = robot.old_coord.c_y;
					flag = 2;
				}
				debug_task = 4;
				buzzer_cycle(400.0);
				//add_output = get_Average(20 , 4, Absolute_duty(100.0, 150.0, robot.velocity.velocity));
				target.distance.between_two_points = get_twopoints_distance( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				target.angle.degree = get_target_degree(target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				target.distance.vertical = get_vertical_distance(target.angle.degree, target.distance.between_two_points );
				target.velocity.velocity = get_target_velocity(target.distance.between_two_points, target.distance.vertical, 1000.0, 1000.0, 500.0);
				//straight = pd_straight(target.distance.between_two_points);
				straight = pd_straight(target.velocity.velocity - robot.velocity.velocity);
				motor.x = get_motor_output_x(straight /*+ add_output*/, target.angle.degree);
				motor.y = get_motor_output_y(straight /*+ add_output*/, target.angle.degree);
				if(target.distance.between_two_points < 10.0){
					action_task = 0;
					flag = 0;
				}
			break;
			case 3:
				target.coord.c_x = 0;
				target.coord.c_y = 0;
				//add_output = get_Average(20, 5, Absolute_duty(100.0, 10000.0, robot.velocity.velocity));
				target.distance.between_two_points = get_twopoints_distance(target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y);
				target.angle.degree = get_target_degree( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				target.distance.vertical = get_vertical_distance( target.angle.degree, target.distance.between_two_points);
				target.velocity.velocity = get_target_velocity( target.distance.between_two_points, target.distance.vertical, 10000.0, 100000.0, 1000.0);
				//straight = pd_straight(target.distance.between_two_points);
				straight = pd_straight( target.velocity.velocity - robot.velocity.velocity);
				motor.x = get_motor_output_x(straight/* + add_output*/, target.angle.degree);
				motor.y = get_motor_output_y(straight/* + add_output*/, target.angle.degree);
				if(target.distance.between_two_points < 10.0){
					action_task = 6;
					//flag = 0;
					finish = ON;
					robot.old_coord.c_x = robot.coord.c_x;
					robot.old_coord.c_y = robot.coord.c_y;
				}
			break;
			case 4:
				target.coord.c_x = robot.coord.c_x;
				target.coord.c_y = 280;
				//add_output = get_Average(20, 5, Absolute_duty(100.0, 10000.0, robot.velocity.velocity));
				target.distance.between_two_points = get_twopoints_distance(target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y);
				target.angle.degree = get_target_degree( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				target.distance.vertical = get_vertical_distance( target.angle.degree, target.distance.between_two_points);
				target.velocity.velocity = get_target_velocity( target.distance.between_two_points, target.distance.vertical, 50.0, 20.0, 45.0);
				//straight = pd_straight(target.distance.between_two_points);
				straight = pd_straight( target.velocity.velocity - robot.velocity.velocity);
				motor.x = get_motor_output_x(straight/* + add_output*/, target.angle.degree);
				motor.y = get_motor_output_y(straight/* + add_output*/, target.angle.degree);
				if(target.distance.between_two_points < 10.0){
					action_task = 0;
					flag = 0;
				}
			break;
			case 5:
				target.coord.c_x = robot.coord.c_x;
				target.coord.c_y = - 280;
				//add_output = get_Average(20, 5, Absolute_duty(100.0, 10000.0, robot.velocity.velocity));
				target.distance.between_two_points = get_twopoints_distance(target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y);
				target.angle.degree = get_target_degree( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				target.distance.vertical = get_vertical_distance( target.angle.degree, target.distance.between_two_points);
				target.velocity.velocity = get_target_velocity( target.distance.between_two_points, target.distance.vertical, 50.0, 20.0, 45.0);
				//straight = pd_straight(target.distance.between_two_points);
				straight = pd_straight( target.velocity.velocity - robot.velocity.velocity);
				motor.x = get_motor_output_x(straight/* + add_output*/, target.angle.degree);
				motor.y = get_motor_output_y(straight/* + add_output*/, target.angle.degree);
				if(target.distance.between_two_points < 10.0){
					action_task = 0;
					flag = 0;
				}
			case 6:
			break;
			}

			if(robot.coord.c_x >= 1190 - 100){
				action_task = 3;
			}

#elif TARGET_SELECT == SONIC_WAVES
			if(robot.waves == ON){
				target.coord.c_x = robot.coord.c_x + robot.waves;
				target.coord.c_y = robot.coord.c_y;

			}else{
				search(&robot, &target, &motor);
			}
#endif

			if(robot.sw.start_sw == ON){
				if(finish != ON){
					//add_output = get_Average(20, 5, Absolute_duty(80.0, 50.0, robot.velocity.velocity));
					//motor.l = get_motor_output_l(motor.x, motor.y, robot.angle.degree, -120) + add_output;
					//motor.r = get_motor_output_r(motor.x, motor.y, robot.angle.degree, 120) + add_output;
					//motor.b = get_motor_output_b(motor.x, motor.y, robot.angle.degree, 0) + add_output;
					motor.l = get_motor_output_l(motor.x, motor.y, robot.angle.degree, -120) + add_output;
					motor.r = get_motor_output_r(motor.x, motor.y, robot.angle.degree, 120) + add_output;
					motor.b = get_motor_output_b(motor.x, motor.y, robot.angle.degree, 0) + add_output;

				}else{
					position_rock(&robot, &motor);
					buzzer_cycle(300.0);
				}

				#if OUTPUT_MODE == CALIBRATION
					motor.turn = pd_rock(robot.angle.degree ,0 ,CALIBRA_P_GAIN ,CALIBRA_D_GAIN);
					move( motor.turn , motor.turn , motor.turn );

				#elif OUTPUT_MODE == GAIN_ADJUSTMENT
					motor.turn = pd_rock(robot.angle.degree, 0, ROCK_P_GAIN ,ROCK_D_GAIN);
					move( motor.turn , motor.turn , motor.turn );

				#elif OUTPUT_MODE == AUTO_CONTROL
					#if TARGET_SELECT == SONIC_WAVES
						if(robot.waves ==OFF){
							motor.turn = pd(robot.angle.degree, -60, ROCK_P_GAIN, ROCK_D_GAIN);
						}else{
							motor.turn = pd(robot.angle.degree, 0, ROCK_P_GAIN, ROCK_D_GAIN);
						}
					#else
						#if CENTER == ON
							target.angle.degree = (-1) * get_target_degree(1250 - robot.coord.c_x, robot.coord.c_y);
							motor.turn = pd_rock(robot.angle.degree, target.angle.degree, ROCK_P_GAIN, ROCK_D_GAIN);
						#else
							motor.turn = pd_rock(robot.angle.degree, 0, ROCK_P_GAIN, ROCK_D_GAIN);
						#endif
					#endif
					move(motor.l + motor.turn, motor.r + motor.turn, motor.b + motor.turn);

				#else
					buzzer_on();
				#endif
			}//start_sw
			if(old_velocity <= robot.velocity.velocity){
				old_velocity = robot.velocity.velocity;
			}
#if SERIAL == ON
				if(count_time(1) >= 200){
					//reset_count_time(1);

#ifdef DEBUG_TASK
					f_print(PC, "task", debug_task);
#endif
#ifdef DEBUG_AD_DATA
					f_print(PC, "ad_dis", robot.arm_dis);
#endif
#ifdef DEBUG_ROBO_COORD_DATA
					f_print(PC, "x", robot.coord.c_x);
					f_print(PC, "y", robot.coord.c_y);
					f_print(PC, "deg", robot.angle.degree);
#endif
#ifdef DEBUG_OUTPUT_DATA
					f_print(PC, "l", motor.l);
					f_print(PC, "r", motor.r);
					f_print(PC, "b", motor.b);
					f_print(PC, "turn", motor.turn);
#endif
#ifdef DEBUG_ENC_DATA
					f_print(PC, "ENCL", robot.enc_cnt.l);
					f_print(PC, "ENCR", robot.enc_cnt.r);
					f_print(PC, "ENCF", robot.enc_cnt.f);
#endif
#ifdef DEBUG_TARGET_DATA
					f_print(PC, "distance", target.distance.between_two_points);
					f_print(PC, "straight",straight);
					f_print(PC, "targetdeg", target.angle.degree);
					f_print(PC, "targetvelocity", target.velocity.velocity);
					f_print(PC, "x_m",motor.x);
					f_print(PC, "y_m",motor.y);
					f_print(PC, "task", task);
#endif
#ifdef DEBUG_TARGET_COORD
					f2_print(PC, "target_c", target.coord.c_x, target.coord.c_y);
					f_print(PC, "target deg", target.angle.degree);
					f_print(PC, "task", task);
#endif
#ifdef DEBUG_VELOCITY_DATA
					if(old_velocity != robot.velocity.velocity){
						f_print(PC, "velocity", robot.velocity.velocity);
					}
#endif
					put_enter(PC);
				}
#endif
		}//INTERRUPT_TIME

#if DEBUG == ON
			debug();
#endif
    }//while

    return 0;
}

//target.distance.vertical = get_vertical_distance( target.angle.degree, target.distance.between_two_points );
//target.distance.horizontal = get_horizontal_distance( target.angle.degree, target.distance.between_two_points );
//target.velocity.velocity = get_target_velocity( target.distance.between_two_points, target.distance.vertical, 1000, 1000, max_velocity);
//target.velocity.angular_velocity	= get_target_angular_velocity( robot.angle.degree, target.angle.degree, 1000000, 2000 );
