#ifndef ROBO_FUNCTION
#define ROBO_FUNCTION

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#include "robo_data.h"

void buzzer(void);

void buzzer_cycle( float time );

void buzzer_stop(void);

void buzzer_on(void);

void initialize(robot_information_t *robot, target_t *target );

float Absolute_duty(float max_duty, float target, float now);

#endif
