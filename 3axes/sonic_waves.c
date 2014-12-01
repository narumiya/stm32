#include "sonic_waves.h"

void sonic_waves(robot_information_t *robot)
{
	static int phase_count = 0;

	Init_port(GPIO_Mode_OUT,TRIG, GPIO_PuPd_UP, GPIO_OType_PP);
	Init_port(GPIO_Mode_IN, ECOH, GPIO_PuPd_NOPULL, GPIO_OType_PP);

	if(phase_count == 0){
		GPIO_SetBits(TRIG);

		if(count_time(2) >= 10){
			GPIO_ResetBits(TRIG);
			phase_count = 1;
			reset_count_time(2);
		}
	}else if(phase_count == 1){
		if(GPIO_ReadInputDataBit(ECOH) == SET){
			reset_count_time(2);
			phase_count = 2;
		}
	}else if(phase_count == 2){

		if(GPIO_ReadInputDataBit(ECOH) == RESET){
			robot->waves = get_Average( 20 ,1 ,count_time(2) * 0.17 );

			reset_count_time(2);
			phase_count = 0;
		}
	}
}
