#include "debug.h"

#include "config_adc.h"
#include "config_systick.h"
#include "robo_data.h"
#include "trancemit.h"
#include "chata.h"
#include "my_standard_io.h"
#include "cam_cal.h"
#include "robo_finction.h"

void debug(void)
{
	robot_information_t robot;
	target_cam_t target_cam;

	unsigned char str[10] = "\0";

	unsigned short 	old_sw = 0,
								start_sw =0,
								old_limit_sw = 0;

	float target_degree = 0.00;

	transmit_usb("[ r : reset] \n\r");
	transmit_usb("[ 1 : encoder]\n\r");
	transmit_usb("[ 2 : AD]\n\r");
	transmit_usb("[ 3 : coordinate]\n\r");
	transmit_usb("[ 4 : sonic_waves]\n\r");
	transmit_usb("[ 5 : encoder reset]\n\r");
	transmit_usb("[ 6 : cam_inf]\n\r");
	transmit_usb("[ 7 : target_cam]\n\r");
	transmit_usb("[ 8 : inf&target]\n\r");
	transmit_usb("[ 9 : start_switch]\n\r");
	transmit_usb("[10 : limit_switch]\n\r");
	transmit_usb("[11 : motor]\n\r");
	transmit_usb("[12 : reverse motor]\n\r");
	transmit_usb("[13 : stop motor]\n\r");
	transmit_usb("[14 : arm motor]\n\r");
	transmit_usb("[15 : reverse arm motor]\n\r");
	//transmit_usb("[p : p gain adjustment]\n\r");
	//transmit_usb("[d : d gain adjustment]\n\r");
	GPIO_ResetBits(ENC_RESET);

	while(strcmp(str, "r") != 0){
		if(usb_available() != 0){
			usb_get_string(str);
		}
		buzzer_stop();
		//sonic_waves(&robot);

		if(count_time(3) >= INTERRUPT_TIME){
			reset_count_time(3);
			get_robot_inf( &robot );
			cam_data(&target_cam, &robot);
			start_sw =positive_chattering(START_SW,1);
			robot.sw.limit_sw = negative_chattering(LIMIT_SW,2);
			robot.ad = get_ADC1_value(0);
		}

		if(strcmp(str, "1") == 0){
			f_print(PC,"ENCL",robot.enc_cnt.l);
			f_print(PC,"ENCR",robot.enc_cnt.r);
			f_print(PC,"ENCF",robot.enc_cnt.f);
			put_enter(PC);

		}else if(strcmp(str, "2") == 0){
			f_print(PC,"AD",robot.ad);
			put_enter(PC);

		}else if(strcmp(str, "3") == 0){
			f2_print(PC,"now_coord",robot.coord.c_x, robot.coord.c_y);
			f_print(PC,"deg",robot.angle.degree);
			put_enter(PC);

		}else if(strcmp(str, "4") == 0){
			f_print(PC,"time",count_time(2));
			f_print(PC,"dis",robot.waves);
			put_enter(PC);

		}else if(strcmp(str, "5") == 0){
			GPIO_SetBits(ENC_RESET);
			//str[0] = 'r';

		}else if(strcmp(str, "6") == 0){
			f2_print(PC, "under", target_cam.under_x, target_cam.under_y );
			f2_print(PC, "over", target_cam.over_x, target_cam.over_y );
			put_enter(PC);

		}else if(strcmp(str, "7") == 0){
			f2_print(PC, "target_cam", (target_cam.x) * cos(D_TO_R(robot.angle.degree))+robot.coord.c_x, (target_cam.y)*sin(D_TO_R(robot.angle.degree))+robot.coord.c_y);
			put_enter(PC);

		}else if(strcmp(str, "8") == 0){
			f2_print(PC, "under", target_cam.under_x, target_cam.under_y);
			f2_print(PC, "over", target_cam.over_x, target_cam.over_y );
			target_degree = get_target_degree(ROBO_TO_CENTER - robot.coord.c_x, robot.coord.c_y);
			f2_print(PC, "target_cam", (target_cam.x) * cos(D_TO_R(target_degree)) + robot.coord.c_x, (target_cam.y) * sin(D_TO_R(target_degree)) + robot.coord.c_y);
			put_enter(PC);

		}else if(strcmp(str, "9") == 0){
			if(robot.sw.start_sw != old_sw ){
				f_print(PC,"sw",start_sw);
				put_enter(PC);
			}

		}else if(strcmp(str, "10") == 0){
			if(robot.sw.limit_sw != old_limit_sw ){
				f_print(PC,"limit_sw",robot.sw.limit_sw);
				put_enter(PC);
			}

		}else if(strcmp(str, "11") == 0){
			move(50, 50, 50);

		}else if(strcmp(str, "12") == 0){
			move(-50, -50, -50);

		}else if(strcmp(str, "13") == 0){
			move(0, 0, 0);
			move_arm(0);

		}else if(strcmp(str, "14") == 0){
			move_arm(100);

		}else if(strcmp(str, "15") == 0){
			move_arm(-100);
		}

		old_limit_sw = robot.sw.start_sw;
		old_sw = start_sw;
	}
}
