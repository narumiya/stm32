#include "robo_data.h"
#include "defines.h"
#include "chata.h"

void move_left_tire( float left_duty )
{
	 if( left_duty == FREE ){
		GPIO_ResetBits(LEFT_TIRE_CW);
		GPIO_ResetBits(LEFT_TIRE_CCW);
		left_duty = 0;

	}else if( left_duty > 0 ){
		GPIO_SetBits(LEFT_TIRE_CW);
		GPIO_ResetBits(LEFT_TIRE_CCW);
		
	}else if( left_duty < 0 ){
		GPIO_ResetBits(LEFT_TIRE_CW);
		GPIO_SetBits(LEFT_TIRE_CCW);

	}else if(left_duty == 0){
		GPIO_ResetBits(LEFT_TIRE_CW);
		GPIO_ResetBits(LEFT_TIRE_CCW);
	}
	
	left_duty = Limit_ul( MAX_DUTY , 0 , fabs(left_duty) );
	Set_duty(LEFT_TIRE_PWM, ( (100 - left_duty ) / 100 ) );
}

void move_right_tire( float right_duty )
{		
	 if( right_duty == FREE ){
		GPIO_ResetBits(RIGHT_TIRE_CW);
		GPIO_ResetBits(RIGHT_TIRE_CCW);
		right_duty = 0;

	}else if( right_duty > 0 ){
		GPIO_SetBits(RIGHT_TIRE_CW);
		GPIO_ResetBits(RIGHT_TIRE_CCW);

	}else if( right_duty < 0 ){
		GPIO_ResetBits(RIGHT_TIRE_CW);
		GPIO_SetBits(RIGHT_TIRE_CCW);
		right_duty *= ( -1 );

	}else if(right_duty == 0){
		GPIO_ResetBits(RIGHT_TIRE_CW);
		GPIO_ResetBits(RIGHT_TIRE_CCW);
	}
	
	right_duty = Limit_ul( MAX_DUTY , 0 ,fabs( right_duty) );
	Set_duty(RIGHT_TIRE_PWM, ( (100 - right_duty) / 100 ) );
}

void move_back_tire( float back_duty )
{		
	 if( back_duty == FREE ){
		GPIO_ResetBits(BACK_TIRE_CW);
		GPIO_ResetBits(BACK_TIRE_CCW);
		back_duty = 0;

	}else if( back_duty > 0 ){
		GPIO_SetBits(BACK_TIRE_CW);
		GPIO_ResetBits(BACK_TIRE_CCW);
		
	}else if( back_duty < 0 ){
		GPIO_ResetBits(BACK_TIRE_CW);
		GPIO_SetBits(BACK_TIRE_CCW);
		back_duty *= ( -1 );

	}else if(back_duty == 0){
		GPIO_ResetBits(BACK_TIRE_CW);
		GPIO_ResetBits(BACK_TIRE_CCW);
	}
	
	back_duty = Limit_ul( MAX_DUTY , 0 , fabs(back_duty) );
	Set_duty(BACK_TIRE_PWM, ((100 - back_duty) / 100) );
}

void move_arm(float arm_duty)
{
	 if( arm_duty == FREE ){
		GPIO_ResetBits(ARM_PUSH);
		GPIO_ResetBits(ARM_PULL);
		arm_duty = 0;

	}else if( arm_duty > 0 ){
		GPIO_SetBits(ARM_PUSH);
		GPIO_ResetBits(ARM_PULL);

	}else if( arm_duty < 0 ){
		GPIO_ResetBits(ARM_PUSH);
		GPIO_SetBits(ARM_PULL);
		arm_duty *= ( -1 );

	}else if(arm_duty == 0){
		GPIO_ResetBits(ARM_PUSH);
		GPIO_ResetBits(ARM_PULL);
	}

	arm_duty = Limit_ul( MAX_DUTY , 0 , fabs(arm_duty) );
	Set_duty(ARM_PWM, ((100 - arm_duty) / 100) );
}

void move( float left_duty , float right_duty , float back_duty )
{
	move_left_tire(left_duty);
	move_right_tire(right_duty);
	move_back_tire(back_duty);
}

void deadtime(void)
{
	GPIO_ResetBits(BACK_TIRE_CW);
	GPIO_ResetBits(BACK_TIRE_CCW);
	GPIO_ResetBits(RIGHT_TIRE_CW);
	GPIO_ResetBits(RIGHT_TIRE_CCW);
	GPIO_ResetBits(LEFT_TIRE_CW);
	GPIO_ResetBits(LEFT_TIRE_CCW);
	GPIO_ResetBits(ARM_PUSH);
	GPIO_ResetBits(ARM_PULL);
}
