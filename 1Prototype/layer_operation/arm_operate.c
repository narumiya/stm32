#include "arm_operate.h"
#include "Config_port.h"
#include "motor.h"
#include "define.h"
#include "config_systick.h"

void serve_short(short start)
{
	short task = 0;

	if(task == 0){
#if MOTOR_MODE == MOTOR_SINGLE
		Move_motor_number(20, RIGHT_ARM1);
#elif MOTOR_MODE == MOTOR_DOUBLE
		Move_motor_number(20, RIGHT_ARM1);
		Move_motor_number(-20, RIGHT_ARM2);
#endif
	}else if(task == 1){
		Set_GPIO_output(AIR1, HIGH);

	}else if(task == 2){
#if MOTOR_MODE == MOTOR_SINGLE
		Move_motor_number(-20, RIGHT_ARM1);
#elif MOTOR_MODE == MOTOR_DOUBLE
		Move_motor_number(-20, RIGHT_ARM1);
		Move_motor_number(20, RIGHT_ARM1);
#endif

	}else if(task ==3){
		if(start != ON){
			reset_count_time(4);
		}
		if(count_time(4) >= SERVE_TIME){
			task = 4;
		}

	}else if(task == 4){
		Set_GPIO_output(AIR1, LOW);
		task = 0;
	}
}
