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
#include "trancemit.h"
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
	Init_PWM(RIGHT_TIRE_PWMSET, 10000);			//左タイヤモーター
	Init_PWM(LEFT_TIRE_PWMSET, 10000);			//右タイヤモーター
	Init_PWM(BACK_TIRE_PWMSET, 10000);			//後ろタイヤモーター
	Init_PWM(ARM_PWMSET, 10000);						//アームモーター
	Init_USART(USART2, 115200, GPIOD, GPIO_Pin_5, GPIOD, GPIO_Pin_6);
	Init_USART(USART3, 115200, GPIOD, GPIO_Pin_8, GPIOD, GPIO_Pin_9);
	//Init_encoder(TIM4, GPIOB, GPIO_Pin_6 | GPIO_Pin_7);	//左エンコ
	//Init_encoder(TIM5, GPIOA, GPIO_Pin_0 | GPIO_Pin_1);	//右エンコ
	//Init_encoder(TIM8, GPIOC, GPIO_Pin_6 | GPIO_Pin_7);	//前エンコ
	//Init_usb();
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
	target_cam_t				target_cam = {0};
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
				cam_x = 0.00,
				cam_y = 0.00,
				add_output = 0.00,
				old_velocity = 0.00;

	unsigned short	start_sw = 0,
								task = 0,
								step = 0,
								debug_task = 0,
								action_task = 0,
								task_flag = 0,
								flag = 0,
								time =0,
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
    		time += INTERRUPT_TIME;

    		get_robot_inf(&robot);
    		arm_length(&robot);
    		start_sw = positive_chattering(START_SW,0);

			if( start_sw == EDGE_DOWN ){
				 robot.sw.start_sw = ON;
			}

			if(robot.sw.start_sw != ON){
				initialize(&robot, &target);
			}else{
				GPIO_ResetBits(ENC_RESET);
			}

#if TARGET_SELECT == COORDINATE
			target.coord.c_x = target_coord[task].target_x;
			target.coord.c_y = target_coord[task].target_y;

#elif TARGET_SELECT == CAM_DATA

			if(time >= 20){
				time = 0;
				cam_data(&target_cam, &robot);
#if STORN_COORD == ON
				if(robot.angle.degree != 90.0){
					cam_x = target_cam.x / cos(D_TO_R(robot.angle.degree));
				}else{
					cam_x = 0;
				}
				cam_y = target_cam.y * sin(D_TO_R(robot.angle.degree));
#else
				cam_x = target_cam.x;
				cam_y = target_cam.y;
#endif
			}

			switch(action_task){
			case 0:
				//ストーン検知してない
				if( target_cam.x == UNDISCOVERED && target_cam.y == UNDISCOVERED ){
					switch(task){
						case 0:
							target.coord.c_x = robot.coord.c_x;
							target.coord.c_y = 350.0;
						break;
						case 1:
							target.coord.c_x = robot.coord.c_x;
							target.coord.c_y = 0.0;
						break;
						case 2:
							target.coord.c_x = robot.coord.c_x;
							target.coord.c_y = -350.0;
						break;
					}
					buzzer_stop();
					debug_task = 0;
					target.distance.between_two_points = get_twopoints_distance( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
					#if ABSOLUTE_D == ON
						if(target.distance.between_two_points < 20.0){
							//add_output = get_Average(20, 1, Absolute_duty(100.0, 100.0, robot.velocity.velocity));
						}else{
							add_output = 0.00;
						}
						#else
						add_output = 0.00;
					#endif
					target.angle.degree = get_target_degree( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
					//target.distance.vertical = get_vertical_distance(target.angle.degree, target.distance.between_two_points);
					target.velocity.velocity = get_target_velocity(target.distance.between_two_points, target.distance.vertical, 800.0, 500.0, MAX_VELOCITY);
					//straight = pd_straight(target.distance.between_two_points);
					straight = pd_straight(target.velocity.velocity - robot.velocity.velocity);
					motor.x = get_motor_output_x(straight + add_output, target.angle.degree);
					motor.y = get_motor_output_y(straight + add_output, target.angle.degree);
					motor.arm = pd_arm_rock(robot.arm_dis, ROBO_TO_ARM - 10.0, ROCK_P_ARMGAIN, ROCK_D_ARMGAIN, 0);

					if(target.distance.between_two_points < 20.0){
						task ++;

						if(task >= 3){
							action_task = 2;
							task = 0;
						}
					}
				//ストーン検知したが上カメラである。
				}else if(target_cam.x == OVER_DISCOVERD && target_cam.y == OVER_DISCOVERD){
					action_task = 1;
				//ストーン検知したが押せる範囲に入ってない。
				}else{
					task_flag = 0;

					if(flag == 0){
						target.angle.degree = (-1) * get_target_degree(ROBO_TO_CENTER - robot.coord.c_x, robot.coord.c_y);
#if STORN_COORD == ON
						target.coord.c_x = cam_x + robot.coord.c_x - ROBO_TO_ARM - 100.0;
						target.coord.c_y = - (cam_y / (ROBO_TO_CENTER -  cam_x)) * target.coord.c_x + ROBO_TO_CENTER / (ROBO_TO_CENTER - cam_x);
#else
						target.coord.c_x = robot.coord.c_x;
						target.coord.c_y = target_cam.y + robot.coord.c_y;
#endif
						flag = 1;
					}

					debug_task = 1;
					target.distance.between_two_points = get_twopoints_distance(target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
					#if ABSOLUTE_D == ON
						if(target.distance.between_two_points > 20.0){
							//add_output = get_Average(20, 2, Absolute_duty(100.0, 100.0, robot.velocity.velocity));
						}else{
							add_output = 0.00;
						}
						#else
						add_output = 0.00;
					#endif
					target.angle.degree = get_target_degree( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
					//target.distance.vertical = get_vertical_distance( target.angle.degree, target.distance.between_two_points );
					target.velocity.velocity = get_target_velocity( target.distance.between_two_points, target.distance.vertical, 800.0, 500.0, MAX_VELOCITY);
					//straight = pd_straight(target.distance.between_two_points);
					straight = pd_straight( target.velocity.velocity - robot.velocity.velocity);
					motor.x = get_motor_output_x(straight + add_output, target.angle.degree);
					motor.y = get_motor_output_y(straight + add_output, target.angle.degree);
					motor.arm = pd_arm_rock(robot.arm_dis, ROBO_TO_ARM - 10.0, ROCK_P_ARMGAIN, ROCK_D_ARMGAIN, 1);

					buzzer_cycle(1500.0);
					if(target.distance.between_two_points < 20.0){
#if STORN_RANGE_CAM == ON
						action_task = 3;
#else
						if( -6.0 <= target.coord.c_y && target.coord.c_y <= 6.0){
							task_flag ++;
							if(task_flag >= 200){
								action_task = 4;
							}
						}else{
							task_flag = 0;
							action_task = 0;
							flag = 0;
						}
#endif
					}
				}
			break;
			//検知したかカメラが上なので前に進む
			case 1:
				if(step != 1){
					target.coord.c_x = robot.coord.c_x + 20.0 * cos(D_TO_R(robot.angle.degree));
					target.coord.c_y = robot.coord.c_y + 20.0 * sin(D_TO_R(robot.angle.degree));
					step = 1;
				}
				target.angle.degree = get_target_degree( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y);
				target.distance.between_two_points = get_twopoints_distance(target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				//target.distance.vertical = get_vertical_distance(target.angle.degree, target.distance.between_two_points);
				target.velocity.velocity = get_target_velocity(target.distance.between_two_points, target.distance.vertical, 500.0, 400.0, MAX_VELOCITY);
				//straight = pd_straight(target.distance.between_two_points);
				straight = pd_straight(target.velocity.velocity - robot.velocity.velocity);
				motor.x = get_motor_output_x(straight, target.angle.degree);
				motor.y = get_motor_output_y(straight, target.angle.degree);
				motor.arm = pd_arm_rock(robot.arm_dis, ROBO_TO_ARM - 10.0, ROCK_P_ARMGAIN, ROCK_D_ARMGAIN, 2);

				if(target.distance.between_two_points < 20.0){
					action_task = 0;
					step = 0;
				}
			break;
			//探してもなかったので下がる
			case 2:
				if(step != 2){
					target.coord.c_x = robot.coord.c_x - 100.0;
					target.coord.c_y = robot.coord.c_y;
					step = 2;
				}
				target.angle.degree = get_target_degree( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				target.distance.between_two_points = get_twopoints_distance(target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				//target.distance.vertical = get_vertical_distance(target.angle.degree, target.distance.between_two_points);
				target.velocity.velocity = get_target_velocity(target.distance.between_two_points, target.distance.vertical, 500.0, 400.0, MAX_VELOCITY);
				//straight = pd_straight(target.distance.between_two_points);
				straight = pd_straight(target.velocity.velocity - robot.velocity.velocity);
				motor.x = get_motor_output_x(straight, target.angle.degree);
				motor.y = get_motor_output_y(straight, target.angle.degree);
				motor.arm = pd_arm_rock(robot.arm_dis, ROBO_TO_ARM - 10.0, ROCK_P_ARMGAIN, ROCK_D_ARMGAIN, 2);

				if(target.distance.between_two_points < 20.0){
					action_task = 0;
					step = 0;
				}
			break;
			//押せる範囲か判定
			case 3:
				if( -6.0 <= cam_y && cam_y <= 6.0){
					task_flag ++;
					if(task_flag >= 200){
						action_task = 4;
					}
				}else{
					task_flag = 0;
					action_task = 0;
					flag = 0;
				}
			break;
			//	ストーン押す
			case 4:
				if(flag == 1){
					target.angle.degree = (-1) * get_target_degree(ROBO_TO_CENTER - robot.coord.c_x, robot.coord.c_y);
#if STORN_COORD == ON
					target.coord.c_x = robot.coord.c_x + 200.0;
					target.coord.c_y = -(cam_y / (ROBO_TO_CENTER -  cam_x)) * target.coord.c_x + (ROBO_TO_CENTER / (ROBO_TO_CENTER - cam_x)) + 10.0;
#else
					//target.coord.c_x = robot.coord.c_x + cam_x + 10.0;
					//target.coord.c_y = -(cam_y / (ROBO_TO_CENTER -  cam_x)) * target.coord.c_x + (ROBO_TO_CENTER / (ROBO_TO_CENTER - cam_x)) + 10.0;
					target.coord.c_x = cam_x + robot.coord.c_x + 60.0 * cos(D_TO_R(robot.angle.degree)) - ROBO_TO_ARM;
					target.coord.c_y = cam_y + robot.coord.c_y + 60.0 * sin(D_TO_R(robot.angle.degree));
#endif
					flag = 2;
				}
				debug_task = 3;
				target.distance.between_two_points = get_twopoints_distance( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				target.angle.degree = get_target_degree( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				#if ABSOLUTE_D == ON
					if(target.distance.between_two_points > 10){
						//add_output = get_Average(20, 3, Absolute_duty(100.0, 100.0, robot.velocity.velocity));
					}else{
						add_output = 0.00;
					}
					#else
					add_output = 0.00;
				#endif
				//target.distance.vertical = get_vertical_distance( target.angle.degree, target.distance.between_two_points );
				target.velocity.velocity = get_target_velocity( target.distance.between_two_points, target.distance.vertical, 500.0, 400.0, MAX_VELOCITY);
				//straight = pd_straight(target.distance.between_two_points);
				straight = pd_straight(target.velocity.velocity - robot.velocity.velocity);
				motor.x = get_motor_output_x(straight + add_output, target.angle.degree);
				motor.y = get_motor_output_y(straight + add_output, target.angle.degree);

#if MOVE_ARM_CAL == ON
				motor.arm = pd_arm_rock(robot.arm_dis, get_twopoints_distance(ROBO_TO_CENTER - robot.coord.arm_x, 0 - robot.coord.arm_y), ROCK_P_ARMGAIN, ROCK_D_ARMGAIN, 3);
#else
				//アームが伸びる長さ変えた 90 -> 150 -> 120
				motor.arm = pd_arm_rock(robot.arm_dis, ROBO_TO_ARM + 120.0, ROCK_P_ARMGAIN, ROCK_D_ARMGAIN, 3);
#endif
				buzzer_cycle(800.0);

				if(target.distance.between_two_points < 20.0){
					action_task = 2;
					robot.old_coord.c_x = robot.coord.c_x;
					robot.old_coord.c_y = robot.coord.c_y;
				}
			break;
			//ストーン押してから下がる
			case 5:
				if(flag == 2){
					target.coord.c_x = robot.old_coord.c_x - 100.0;
					target.coord.c_y = robot.old_coord.c_y;
					flag = 3;
				}
				debug_task = 4;
				buzzer_cycle(400.0);
				//add_output = get_Average(20 , 4, Absolute_duty(100.0, 150.0, robot.velocity.velocity));
				target.distance.between_two_points = get_twopoints_distance( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				target.angle.degree = get_target_degree(target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				//target.distance.vertical = get_vertical_distance(target.angle.degree, target.distance.between_two_points );
				target.velocity.velocity = get_target_velocity(target.distance.between_two_points, target.distance.vertical, 1500.0, 500.0, 400.0);
				//straight = pd_straight(target.distance.between_two_points);
				straight = pd_straight(target.velocity.velocity - robot.velocity.velocity);
				motor.x = get_motor_output_x(straight, target.angle.degree);
				motor.y = get_motor_output_y(straight, target.angle.degree);
				motor.arm = pd_arm_rock(robot.arm_dis, ROBO_TO_ARM - 10.0, ROCK_P_ARMGAIN, ROCK_D_ARMGAIN, 4);

				if(target.distance.between_two_points < 20.0){
					action_task = 0;
					flag = 0;
				}
			break;
			case 6:
				target.coord.c_x = 0.00;
				target.coord.c_y = 0.00;
				//add_output = get_Average(20, 5, Absolute_duty(100.0, 10000.0, robot.velocity.velocity));
				target.distance.between_two_points = get_twopoints_distance(target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y);
				target.angle.degree = get_target_degree( target.coord.c_x - robot.coord.c_x, target.coord.c_y - robot.coord.c_y );
				//target.distance.vertical = get_vertical_distance( target.angle.degree, target.distance.between_two_points);
				target.velocity.velocity = get_target_velocity( target.distance.between_two_points, target.distance.vertical, 10000.0, 10000.0, 1000.0);
				//straight = pd_straight(target.distance.between_two_points);
				straight = pd_straight( target.velocity.velocity - robot.velocity.velocity);
				motor.x = get_motor_output_x(straight, target.angle.degree);
				motor.y = get_motor_output_y(straight, target.angle.degree);
				motor.arm = pd_arm_rock(robot.arm_dis, ROBO_TO_ARM - 10.0, ROCK_P_ARMGAIN, ROCK_D_ARMGAIN, 5);

				if(target.distance.between_two_points < 20.0){
					action_task = 7;
					//flag = 0;
					finish = ON;
					robot.old_coord.c_x = robot.coord.c_x;
					robot.old_coord.c_y = robot.coord.c_y;
				}
			break;
			default:
				break;
			}

#if FINISH_ARM == ON
			if(get_twopoints_distance(ROBO_TO_CENTER - robot.coord.arm_x, 0 - robot.coord.arm_y) < 5.0){
				action_task = 6;
			}
#else
			if(get_twopoints_distance(ROBO_TO_CENTER - robot.coord.c_x, 0 - robot.coord.c_y) < 300.0){
				action_task = 6;
			}
#endif


#elif TARGET_SELECT == SONIC_WAVES
			if(robot.waves == ON){
				target.coord.c_x = robot.coord.c_x + robot.waves;
				target.coord.c_y = robot.coord.c_y;

			}else{
				search(&robot, &target, &motor);
			}
#endif

			if(robot.sw.start_sw == ON){
				if(robot.sw.limit_sw != 1 ){
					init_arm(&robot);
				}else{
					move_arm(motor.arm);

					if(finish != ON){
						target.angle.degree = (-1) * get_target_degree(ROBO_TO_CENTER - robot.coord.c_x, robot.coord.c_y);
						//add_output = get_Average(20, 5, Absolute_duty(80.0, 50.0, robot.velocity.velocity));
						//motor.l = get_motor_output_l(motor.x, motor.y, robot.angle.degree, -120) + add_output;
						//motor.r = get_motor_output_r(motor.x, motor.y, robot.angle.degree, 120) + add_output;
						//motor.b = get_motor_output_b(motor.x, motor.y, robot.angle.degree, 0) + add_output;
						motor.l = get_motor_output_l(motor.x, motor.y, target.angle.degree, -120);
						motor.r = get_motor_output_r(motor.x, motor.y, target.angle.degree, 120);
						motor.b = get_motor_output_b(motor.x, motor.y, target.angle.degree, 0);

					}else{
						position_rock(&robot, &motor);

						buzzer_cycle(300.0);
					}

					#if OUTPUT_MODE == CALIBRATION
						motor.turn = pd_rock(robot.angle.degree ,0 ,CALIBRA_P_GAIN ,CALIBRA_D_GAIN);
						move( motor.turn, motor.turn, motor.turn );

					#elif OUTPUT_MODE == GAIN_ADJUSTMENT
						motor.turn = pd_rock(robot.angle.degree, 0, ROCK_P_GAIN ,ROCK_D_GAIN);
						move( motor.turn , motor.turn , motor.turn );

					#elif OUTPUT_MODE == AUTO_CONTROL
						#if TARGET_SELECT == SONIC_WAVES
							if(robot.waves == OFF){
								motor.turn = pd(robot.angle.degree, -60, ROCK_P_GAIN, ROCK_D_GAIN);
							}else{
								motor.turn = pd(robot.angle.degree, 0, ROCK_P_GAIN, ROCK_D_GAIN);
							}
						#else
							#if CENTER == ON
								target.angle.degree = (-1) * get_target_degree(ROBO_TO_CENTER - robot.coord.c_x, robot.coord.c_y);
								motor.turn = pd_rock(robot.angle.degree, target.angle.degree, ROCK_P_GAIN, ROCK_D_GAIN);
							#else
								motor.turn = pd_rock(robot.angle.degree, 0, ROCK_P_GAIN, ROCK_D_GAIN);
							#endif
						#endif
						move(motor.l + motor.turn, motor.r + motor.turn, motor.b + motor.turn);
					#else
						buzzer_on();
					#endif
				}//limit_sw
			}//start_sw
			if(old_velocity < robot.velocity.velocity){
				old_velocity = robot.velocity.velocity;
			}
#if SERIAL == ON
				if(count_time(1) >= 200){
					reset_count_time(1);

#ifdef DEBUG_TASK
					f_print(PC, "d_task", debug_task);
					f_print(PC, "a_task", action_task );
#endif
#ifdef DEBUG_AD_DATA
					//f_print(PC,"ad", robot.sw.limit_sw);
					f_print(PC, "ad_dis", robot.arm_dis);
					f2_print(PC, "arm", robot.coord.arm_x, robot.coord.arm_y);
#endif
#ifdef DEBUG_ROBO_COORD_DATA
					f_print(PC, "x", robot.coord.c_x);
					f_print(PC, "y", robot.coord.c_y);
					f2_print(PC, "arm", robot.coord.arm_x, robot.coord.arm_y);
					f_print(PC, "deg", robot.angle.degree);
#endif
#ifdef DEBUG_OUTPUT_DATA
					f_print(PC, "straight", straight);
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
					//f_print(PC, "straight",straight);
					//f_print(PC, "targetdeg", target.angle.degree);
					//f_print(PC, "targetvelocity", target.velocity.velocity);
					//f_print(PC, "x_m",motor.x);
					//f_print(PC, "y_m",motor.y);
#endif
#ifdef DEBUG_TARGET_COORD
					f2_print(PC, "target_c", target.coord.c_x, target.coord.c_y);
					f_print(PC, "target_deg", target.angle.degree);
#endif
#ifdef DEBUG_VELOCITY_DATA
					f_print(PC, "now_velocity", robot.velocity.velocity);
					f_print(PC, "target_velocity", target.velocity.velocity);
					f_print(PC, "straight", straight);
#endif
#ifdef CAM_DATA2
					f2_print(PC, "coord", robot.coord.c_x, robot.coord.c_y);
					f_print(PC, "deg", robot.angle.degree);
					f2_print(PC, "cam", cam_x, cam_y);
					f2_print(PC, "target_cam", cam_x + robot.coord.c_x,cam_y + robot.coord.c_y);
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
