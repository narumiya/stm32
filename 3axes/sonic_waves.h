#ifndef SONIC_WAVES_H
#define SONIC_WAVES_H

#define TRIG 		GPIOB, GPIO_Pin_8
#define ECOH 	GPIOB, GPIO_Pin_9

#include "defines.h"

void sonic_waves(robot_information_t *robot);

#endif
