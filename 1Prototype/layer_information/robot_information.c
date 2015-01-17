
#include "robot_information.h"

#define ENCODER_DIVISION	1000			//エンコーダ分解数
#define ENCODER_DISTANCE	500.0			//中心からエンコーダタイヤまでの距離
#define ENCODER_0_DINAMETER	50.8		//左エンコーダタイヤ径
#define ENCODER_1_DINAMETER	50.8		//右エンコーダタイヤ径
#define ENCODER_2_DINAMETER	50.8		//後エンコーダタイヤ径
#define ENCODER_0_DIRECTION_DEGREE	150	//左エンコーダ取り付け方向角度
#define ENCODER_1_DIRECTION_DEGREE	30	//右エンコーダ取り付け方向角度
#define ENCODER_2_DIRECTION_DEGREE	-90	//後エンコーダ取り付け方向角度

/*
void Init_Robot_center_infomation(Robot_center_information_t *robot)
{
	Init_coord(&robot->coord);
	Init_velocity(&robot->velocity);
	Init_angle(&robot->angle);
	Init_angle(&robot->omega);
	Init_encoder_value(&robot->enc_tire[0]);
	Init_encoder_value(&robot->enc_tire[1]);
	Init_encoder_value(&robot->enc_tire[2]);
}

void Init_coord(Coordinate_t *coord)
{
	coord->x = 0.0;
	coord->y = 0.0;
	coord->z = 0.0;
}

void Init_velocity(Velocity_t *vel)
{
	vel->abs = 0.0;
	Init_coord(&vel->coord);
	vel->phase = 0.0;
}

void Init_angle(Angle_t *angle)
{
	angle->degree = 0.0;
	angle->radian = 0.0;
}

void Init_encoder_value(Encoder_t *enc)
{
	enc->count = 0;
	enc->count_old = 0;
	enc->gap_count = 0;
	enc->distance = 0;
	enc->degree = 0;
}

void Init_underbody_tire(Underbody_tire_t *under)
{
	under->l_f = 0;
	under->l_b = 0;
	under->r_f = 0;
	under->r_b = 0;
}
void Init_button_information(Button_information_t *button)
{
	button->count = 0;
	button->flag_down_edge = 0;
	button->flag_up_edge = 0;
	button->info = 0;
	button->old = 0;
	button->raw = 0;
	button->state = 0;
	button->timer = 0;
}


void Init_potentio(Potentio_t *potentio)
{
	potentio->init_value = 0;
	potentio->now_value = 0;
	potentio->length = 0;
	potentio->degree = 0;
}

*/
/******************************************************************************
*	タイトル ： 自己位置推定
*	  関数名 ： Calculate_Information_center
*	  戻り値 ： void型
*	   引数1 ： Robot_center_information_t型 *robot  ロボットの中心情報
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/10
******************************************************************************/
/*void calculate_information_center(Robot_center_information_t *robot, unsigned char *flag_safety)
{

	float 		degree_reverse[ENCODER_TIRE_SUM] = {0.0};
	const float encoder_init_degree[ENCODER_TIRE_SUM]  = {ENCODER_0_DIRECTION_DEGREE,
	                                             	 	   ENCODER_1_DIRECTION_DEGREE,
	                                             	 	   ENCODER_2_DIRECTION_DEGREE};
	float 		encoder_direction_degree[ENCODER_TIRE_SUM] = {0.0};
	static float 	radian[ENCODER_TIRE_SUM] = {0.0};
	static float 	movement_x[ENCODER_TIRE_SUM] = {0.0};
	static float 	movement_y[ENCODER_TIRE_SUM] = {0.0};
	static float x_old = START_X, 	y_old = START_Y;
	static float degree_old = START_DEGREE;


//エンコーダが正回転したときのカウントの方向
#if ENCODER_0_COUNT_DIRECTION == FRONT
	robot->enc_tire[0].count = Select_encoder_count(ENCODER_0_TIM);
#elif ENCODER_0_DIRECTION == BACK
	robot->enc_tire[0].count = (-1) * Select_encoder_count(ENCODER_0_TIM);
#endif
#if ENCODER_1_COUNT_DIRECTION == FRONT
	robot->enc_tire[1].count = Select_encoder_count(ENCODER_1_TIM);
#elif ENCODER_1_DIRECTION == BACK
	robot->enc_tire[1].count = (-1) * Select_encoder_count(ENCODER_1_TIM);
#endif
#if ENCODER_2_COUNT_DIRECTION == FRONT
	robot->enc_tire[2].count = Select_encoder_count(ENCODER_2_TIM);
#elif ENCODER_2_DIRECTION == BACK
	robot->enc_tire[2].count = (-1) * Select_encoder_count(ENCODER_2_TIM);
#endif


	int i;
	for(i = 0; i < ENCODER_TIRE_SUM; i ++){
		robot->enc_tire[i].gap_count 	=  robot->enc_tire[i].count - robot->enc_tire[i].count_old;
		if(robot->enc_tire[i].gap_count > 1000){
			*flag_safety = 1;
		}
		robot->enc_tire[i].count_old = robot->enc_tire[i].count_old;
	}

	robot->enc_tire[0].distance = (( (float)(robot->enc_tire[0].gap_count) ) / ENCODER_DIVISION) * (ENCODER_0_DINAMETER  * M_PI);
	robot->enc_tire[1].distance = (( (float)(robot->enc_tire[1].gap_count)) / ENCODER_DIVISION) * (ENCODER_1_DINAMETER * M_PI);
	robot->enc_tire[2].distance = (( (float)(robot->enc_tire[2].gap_count) ) / ENCODER_DIVISION) * (ENCODER_2_DINAMETER  * M_PI);

	for(i = 0; i < ENCODER_TIRE_SUM; i ++){
		robot->enc_tire[i].degree = (float)(robot->enc_tire[i].gap_count) / ENCODER_DIVISION * 360;
	}

	for(i = 0; i < ENCODER_TIRE_SUM; i ++){
		if(robot->enc_tire[i].distance < 0.0){
			degree_reverse[i] = 180.0;
		}
	}

	//各エンコーダから求められる中心角度
	for(i = 0; i < ENCODER_TIRE_SUM; i ++){
		radian[i] = robot->enc_tire[i].distance / ENCODER_DISTANCE;
	}

	//角度格納
	robot->angle.radian += (radian[0] + radian[1] + radian[2]) / 3.0;
	robot->angle.radian = reap_radian_area(robot->angle.radian);
	robot->angle.degree = START_DEGREE + convert_to_degree(robot->angle.radian);
	robot->angle.degree = reap_degree_area(robot->angle.degree);

	for(i = 0; i < ENCODER_TIRE_SUM; i ++){
		encoder_direction_degree[i] = robot->angle.degree + degree_reverse[i] + encoder_init_degree[i];
	}

	//各エンコーダからのx、y移動量を計算
	for(i = 0; i < ENCODER_TIRE_SUM; i ++){
		movement_x[i] = 2.0 * fabs(robot->enc_tire[i].distance) * cos(convert_to_radian(encoder_direction_degree[i]));
		movement_y[i] = 2.0 * fabs(robot->enc_tire[i].distance) * sin(convert_to_radian(encoder_direction_degree[i]));
	}

	robot->coord.x += ((movement_x[0] + movement_x[1] + movement_x[2]) / 3.0);
	robot->coord.y += ((movement_y[0] + movement_y[1] + movement_y[2]) / 3.0);

	robot->omega.degree = (get_gap_degree(robot->angle.degree, degree_old)) * (1000 / INTERRUPT_TIME_MS);
	robot->omega.radian = convert_to_radian(get_gap_degree(robot->angle.degree, degree_old)) * (1000 / INTERRUPT_TIME_MS);

	//速度計算(平均化なし)
	robot->velocity.coord.x = (robot->coord.x - x_old) * (1000 / INTERRUPT_TIME_MS);
	robot->velocity.coord.y = (robot->coord.y - y_old) * (1000 / INTERRUPT_TIME_MS);
	robot->velocity.abs = sqrtf(powf(robot->velocity.coord.x, 2) + powf(robot->velocity.coord.y, 2));


	degree_old = robot->angle.degree;
	x_old = robot->coord.x;
	y_old = robot->coord.y;
}*/
/*
void Calculate_top_racket_reload_length(float ad_value, unsigned short flag_set,Potentio_information_t *potentio)
{
	static int ad_timer = 0;
	static unsigned short flag_potentio_set = 0;

	if(flag_potentio_set == OFF){
		ad_timer += INTERRUPT_TIME_MS;
		potentio->init_value = ad_value;//get_ADC1_value(0);	////ポテンショメータ値格納
		potentio->now_value = potentio->init_value;
		if(ad_timer >= POTENTIO_SET_TIMER_MS){
			ad_timer = 0;
			flag_potentio_set = ON;
		}
	}else{
		if(flag_set == ON){
			potentio->now_value = ad_value;//get_Average(count_average, 8,get_ADC1_value(0));//ポテンショメータ値格納
		}else{
			potentio->init_value = ad_value;
			potentio->now_value = potentio->init_value;
		}
	}


#if	DIRECTION_POTENTIO_TOP_RACKET_RELOAD == FRONT
	potentio->length = MOVEMENT_TOP_RACKET_RELOAD_MM + Convert_from_ad_to_mm_top_racket_reload(potentio->now_value - potentio->init_value);
#elif DIRECTION_POTENTIO_TOP_RACKET_RELOAD == BACK
	potentio->length = MOVEMENT_TOP_RACKET_RELOAD_MM + Convert_from_ad_to_mm_top_racket_reload(potentio->init_value - potentio->now_value);
#endif

}

void Calculate_right_racket_reload_degree(float ad_value, unsigned short flag_set,Potentio_information_t *potentio)
{
	static int ad_timer = 0;
	static unsigned short flag_potentio_set = 0;

	if(flag_potentio_set == OFF){
		ad_timer += INTERRUPT_TIME_MS;
		potentio->init_value = ad_value;//get_ADC1_value(0);	////ポテンショメータ値格納
		potentio->now_value = potentio->init_value;
		if(ad_timer >= POTENTIO_SET_TIMER_MS){
			ad_timer = 0;
			flag_potentio_set = ON;
		}
	}else{
		if(flag_set == ON){
			potentio->now_value = ad_value;//get_Average(count_average, 8,get_ADC1_value(0));//ポテンショメータ値格納
		}else{
			potentio->init_value = ad_value;
			potentio->now_value = potentio->init_value;
		}
	}


#if	DIRECTION_POTENTIO_RIGHT_RACKET_RELOAD == FRONT
	potentio->degree = Convert_from_ad_to_mm_top_racket_reload(potentio->now_value - potentio->init_value);
#elif DIRECTION_POTENTIO_TOP_RACKET_RELOAD == BACK
	potentio->length = Convert_from_ad_to_mm_top_racket_reload(potentio->init_value - potentio->now_value);
#endif

}

void Calculate_Information_top_racket(Robot_center_information_t robot, Racket_each_information_t *top_racket)
{
	const float center_to_init_racket_distance = 1745.5913;
	float center_to_init_racket_distance_xy_cood = 0.0;
	const float center_to_init_racket_degree  = 81.21538;
	const float movement_raket_pitch_degree = 100;

	top_racket->center_cood.z = center_to_init_racket_distance * sin(Convert_to_radian(center_to_init_racket_degree));
	center_to_init_racket_distance_xy_cood = center_to_init_racket_distance * cos(Convert_to_radian(center_to_init_racket_degree));
	top_racket->center_cood.x = center_to_init_racket_distance_xy_cood * cos(Convert_to_radian(robot.angle.degree));
	top_racket->center_cood.y = center_to_init_racket_distance_xy_cood * sin(Convert_to_radian(robot.angle.degree));
}

/******************************************************************************
*	タイトル ： アーム自己位置推定
*	  関数名 ： Calculate_Infomation_arm
*	  戻り値 ： void型
*	   引数1 ： Potentio_information_t型 *potentio  ポテンショメータ情報
*	   引数2 ： Robot_information_t型 *arm  アームの自己位置情報
*	   引数3 ： Robot_information_t型 *robot  ロボット中心の自己位置情報
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/10
******************************************************************************/
/*void Calculate_Information_arm(Potentio_information_t *potentio, Robot_information_t *robot ,float potentio_ad)
{
	static int ad_timer = 0;
	static unsigned short flag_potentio_set = 0;
	float degree_reverse = 0.0;
	static float x_old = 0.0, y_old = 0.0;
	float center_to_arm_length = 0.0;

	if(flag_potentio_set == OFF){
		ad_timer += INTERRUPT_TIME_MS;
		potentio->init_value = potentio_ad;//get_ADC1_value(0);	////ポテンショメータ値格納
		potentio->now_value = potentio->init_value;
		if(ad_timer >= POTENTIO_SET_TIMER_MS){
			ad_timer = 0;
			flag_potentio_set = ON;
		}
	}else{
		potentio->now_value = potentio_ad;//get_Average(count_average, 8,get_ADC1_value(0));//ポテンショメータ値格納
	}

#if	POTENTIO_DIRECTION == FRONT
	potentio->length = Convert_from_ad_to_mm_arm(potentio->now_value - potentio->init_value);
#elif POTENTIO_DIRECTION == BACK
	potentio->length = Convert_from_ad_to_mm_arm(potentio->init_value - potentio->now_value);
#endif

	if(potentio->length < 0.0){
		degree_reverse = 180.0;
	}

	robot->arm_c.x = robot->cood.x + (fabs(potentio->length) + INIT_CENTER_TO_ARM) * cos(Convert_to_radian(robot->angle.degree - 90.0 + degree_reverse));
	robot->arm_c.y = robot->cood.y + (fabs(potentio->length) + INIT_CENTER_TO_ARM) * sin(Convert_to_radian(robot->angle.degree - 90.0 + degree_reverse));

	robot->arm_vel.cood.x = (robot->arm_c.x - x_old) * (1000 / INTERRUPT_TIME_MS);
	robot->arm_vel.cood.y = (robot->arm_c.y - y_old) * (1000 / INTERRUPT_TIME_MS);
	robot->arm_vel.abs = sqrtf(powf(robot->arm_vel.cood.x , 2) + powf(robot->arm_vel.cood.x, 2));

	center_to_arm_length = get_distance(robot->arm_c.x, robot->arm_c.y, robot->cood.x, robot->cood.y);
	robot->arm_vel.phase = center_to_arm_length * robot->omega.radian;

	x_old = robot->arm_c.x;
	y_old = robot->arm_c.y;
}*/
/******************************************************************************
*	タイトル ： AD→mmへの変換関数
*	  関数名 ： Convert_from_ad_to_mm_top_raclet_release
*	  戻り値 ： float型
*	   引数1 ： float型 ad  AD変換した値
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/10
******************************************************************************/
/*float Convert_from_ad_to_mm_top_racket_reload(float ad)
{
	return(ad * (MOVEMENT_TOP_RACKET_RELOAD_MM / MOVEMENT_TOP_RACKET_RELOAD_AD));
}

float Convert_from_ad_to_deg_right_racket_reload(float ad)
{
	return(ad * (MOVEMENT_RIGHT_RACKET_RELOAD_DEGREE / MOVEMENT_RIGHT_RACKET_RELOAD_AD));
}*/

/******************************************************************************
*	タイトル ： ボタン情報を格納する関数
*	  関数名 ： get_button_information
*	  戻り値 ： void型
*	   引数1 ： int型 chattaring_timer  チャタリング待機時間
*	   引数2 ： Button_information_t型 *button  ボタン情報
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/10
******************************************************************************/
void get_button_information(int chattaring_timer, GPIO_TypeDef *GPIOx, uint16_t pin,Button_information_t *button)
{
	button->raw = GPIO_ReadInputDataBit(GPIOx, pin);//ボタン情報格納

	if(button->raw != button->state){
		button->timer += INTERRUPT_TIME_MS;
	}else{
		button->timer = 0;
	}

	if(button->timer >= chattaring_timer){
		button->timer = 0;
		button->state =! button->state;
		if(button->state == ON){
			 button->count ++;
		}
	}
	button->info = button->state;


	if(button->info == ON && button->old == OFF){
		button->flag_up_edge = ON;
		button->flag_down_edge = OFF;
	}else if(button->info == OFF && button->old == ON){
		button->flag_up_edge = OFF;
		button->flag_down_edge = ON;
	}else{
		button->flag_up_edge = OFF;
		button->flag_down_edge = OFF;
	}

	button->old = button->info;
}






