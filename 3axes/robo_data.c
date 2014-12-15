#include "robo_data.h"
#include "config_adc.h"
#include "chata.h"

/******************************************************************************
*	タイトル ： 設定した範囲内の値を返す
*	  関数名 ： Limit_ul
*	  戻り値 ： float型 出力値
*	   引数1 ： float型 upper  上限の数値
*	   引数2 ： float型 lower  下限の数値
*	   引数3 ： float型 figure  比較する数値
*	  作成者 ： 市川 智章
*	  作成日 ： 2011/08/31
******************************************************************************/
float Limit_ul(float upper,float lower,float figure)
{
	if(upper < figure){
		return(upper);
	}else if(figure < lower){
		return(lower);
	}else{
		return(figure);
	}
}

float pd_rock( float present , float target , float p_gain, float d_gain )					//pd 直進中のロック
{
	float	output		= 0.00,
			deviation	= 0.00;											//deviation 偏差
			
	static float old_deviation = 0.00;
	
	deviation = revision_degree( target - present );

	output = ( p_gain * deviation ) + ( d_gain * ( deviation - old_deviation ) );

	output = Limit_ul( 100 , -100 , output );
	
	old_deviation = deviation;

	return ( output );
}

float pd_arm_rock( float present , float target , float p_gain, float d_gain , int box)					//pd 直進中のロック
{
	float	output		= 0.00,
			deviation	= 0.00;											//deviation 偏差

	static float old_deviation[10] = {0.00};

	deviation = target - present;

	output = ( p_gain * deviation ) + ( d_gain * ( deviation - old_deviation[box] ) );

	output = Limit_ul( 100 , -100 , output );

	old_deviation[box] = deviation;

	return ( output );
}

float pd_straight( float deviation )											//pd 直進 deviation 偏差
{							
	float 	output		= 0.00;																	//deviation 偏差
			
	static float old_deviation = 0.00;

	output = ( STRAIGHT_P_GAIN * deviation ) + ( STRAIGHT_D_GAIN * ( deviation - old_deviation ) );
	
	output = Limit_ul( 100 , -100 , output );

	//output = get_Average(10, 3, output);
	
	old_deviation = deviation;

	return ( output );
}

/******************************************************************************
*	タイトル ： 左オムニタイヤの出力決定
*	  関数名 ： get_motor_output_l
*	  戻り値 ： float型
*	    引数1 ：float型 motor_output_x
*	    引数2 ：float型 motor_output_y
*	    引数3 ：float型 degree_now
*	    degree  150
*	  作成者 ： 坂下文彦
*	  作成日 ： 2013/11/21
******************************************************************************/
float get_motor_output_l(float motor_output_x,float motor_output_y,float degree_now, const float degree)
{
	float 	motor_output_l = 0.0,
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
	
	motor_output_l = fabs(motor_output_x) * cos(D_TO_R(revision_degree(degree_now + (degree + degree_reverse_x)))) + fabs(motor_output_y) * sin(D_TO_R(revision_degree(degree_now + (degree + degree_reverse_y))));
	
	return(motor_output_l);
}

/******************************************************************************
*	タイトル ： 右オムニタイヤの出力決定
*	  関数名 ： get_motor_output_r
*	  戻り値 ： float型
*	    引数1 ：float型 motor_output_x
*	    引数2 ：float型 motor_output_y
*	    引数3 ：float型 degree_now
*	    degree 30.0
*	  作成者 ： 坂下文彦
*	  作成日 ： 2013/11/21
******************************************************************************/
float get_motor_output_r(float motor_output_x,float motor_output_y,float degree_now, const float degree)
{
	float 	motor_output_r = 0.0,
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
	
	motor_output_r = fabs(motor_output_x) * cos(D_TO_R(revision_degree(degree_now +( degree + degree_reverse_x)))) + fabs(motor_output_y) * sin(D_TO_R(revision_degree(degree_now + (degree + degree_reverse_y))));
	
	return(motor_output_r);
}

/******************************************************************************
*	タイトル ： 後ろオムニタイヤの出力決定
*	  関数名 ： get_motor_output_b
*	  戻り値 ： float型
*	    引数1 ：float型 motor_output_x
*	    引数2 ：float型 motor_output_y
*	    引数3 ：float型 degree_now
*	    degree -90
*	  作成者 ： 坂下文彦
*	  作成日 ： 2013/11/21
******************************************************************************/
float get_motor_output_b(float motor_output_x,float motor_output_y,float degree_now, const float degree)
{
	float 	motor_output_b = 0.0,
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
	
	motor_output_b = fabs(motor_output_x) * cos(D_TO_R(revision_degree(degree_now  + (degree_reverse_x + degree)))) + fabs(motor_output_y) * sin(D_TO_R(revision_degree(degree_now +( degree_reverse_y + degree))));
	
	return(motor_output_b);
}

/******************************************************************************
*	タイトル ： √(x^2)+(y^2)
*	  関数名 ： get_twopoints_distance
*	   引数1 ： float型 deviation_x  目標のx座標と現在のx座標の偏差
*	   引数2 ： float型 deviation_y  目標のy座標と現在のy座標の偏差
*	  作成者 ： 成宮陽生
*	  作成日 ： 2014/09/19
******************************************************************************/
float get_twopoints_distance( float deviation_x , float deviation_y )
{
	return ( sqrt( ( deviation_x ) * ( deviation_x ) + ( deviation_y) * ( deviation_y ) ) );
}

/******************************************************************************
*	タイトル ： 目標と現在の座標の偏差の角度
*	  関数名 ： get_target_degree
*	   引数1 ： float型 deviation_x  目標のx座標と現在のx座標の偏差
*	   引数2 ： float型 deviation_y  目標のy座標と現在のy座標の偏差
*	  作成者 ： 成宮陽生
*	  作成日 ： 2014/09/19
******************************************************************************/
float get_target_degree( float deviation_x , float deviation_y )
{	
	float target_degree = 0.00;
	static float old_target_degree = 0.00;
	
	if( deviation_x !=0 || deviation_y != 0 ){
		target_degree = atan2f( deviation_y , deviation_x) * ( 180 / M_PI );
	}else{
		target_degree = old_target_degree;
	}
	
	return ( target_degree );
}

/******************************************************************************
*	タイトル ： 水平距離算出
*	  関数名 ： get_horizontal_distance
*	   引数1 ： float型 degree   目標地と現在地の偏差の角度
*	   引数2 ： float型 distance  座標から距離
*	  作成者 ： 成宮陽生
*	  作成日 ： 2014/09/19
******************************************************************************/
float get_horizontal_distance(float degree,float distance)
{
	if(degree > 90){
		degree = 180 - degree;
	}
	if(degree < -90){
		degree = - degree - 180;
	}
	
	if(degree > 0){
		return ((-1)*distance * cos(D_TO_R(90-fabs(degree))));//車体の向きに対して水平方向が左
	}else{
		return(distance * cos(D_TO_R(90-fabs(degree))));
	}
}

/******************************************************************************
*	タイトル ： 垂直距離算出
*	  関数名 ： get_vertical_distance
*	   引数1 ： float型 degree  目標地と現在地の偏差の角度
*	   引数2 ： float型 distance  座標から距離
*	  作成者 ： 成宮陽生
*	  作成日 ： 2014/09/19
******************************************************************************/
float get_vertical_distance(float degree , float distance )
{
	float		vertical_distance	= 0.00;
	
	if( degree > 90 ){
     	degree	= 180 - degree;
     	vertical_distance	= ( -1 ) * distance * sin( (90-degree) * ( M_PI / 180) );
  
	}else if( degree < -90 ){
		degree	= -degree - 180;
   		vertical_distance	= ( -1 ) * distance * sin( (90-degree) * (M_PI / 180 ) );
	
	}else{
		vertical_distance	= distance * sin( (90-degree) * ( M_PI / 180 ) );
	}

	return ( vertical_distance );
}

/******************************************************************************
*	タイトル ： 台形制御
*	  関数名 ： get_target_velocity
*	   引数1 ： float型 distance_rest  2乗のルート
*	   引数2 ： float型 vertical_distance  垂直距離
*	   引数3 ： float型 a_up  加速度
*	   引数4 ： float型 a_down  減速度
*	  作成者 ： 成宮陽生
*	  作成日 ： 2014/09/19
******************************************************************************/
float get_target_velocity( float distance_rest , float vertical_distance , float a_up ,  float a_down , float max_velocity)	//rest余り
{	
	static float target_velocity	= 0.00;
	
	if( distance_rest > 0.5 * max_velocity * max_velocity / a_down ){
		if( target_velocity < max_velocity ){
			target_velocity += ( a_up * (INTERRUPT_TIME * 0.001) );
												
		}else{
			target_velocity = max_velocity;
		}
	}else if( vertical_distance < 0 ){
		target_velocity = ( -1 ) * sqrt( fabs( 2.0 * a_down * distance_rest ) );
	}else{
		target_velocity =  sqrt( fabs( 2.0 * a_down * distance_rest ) );
	}
	
	//target_velocity = get_Average(5 ,2, target_velocity);

	return ( target_velocity );
}

float get_target_angular_velocity( float degree , float target_degree , float a_up , float a_down )
{
	float rest_degree = 0.00;
	static float target_angular_velocity = 0.00;

	rest_degree	= target_degree - degree;
	rest_degree	= revision_degree( rest_degree );

	if( fabs( rest_degree ) > 0.5 * MAX_ANGULAR_VELOCITY * MAX_ANGULAR_VELOCITY / a_down ){
		if(  fabs( target_angular_velocity ) < MAX_ANGULAR_VELOCITY ){
			target_angular_velocity += ( a_up * INTERRUPT_TIME );
		}else{
			target_angular_velocity = MAX_ANGULAR_VELOCITY;
		}
		if( rest_degree < 0 ){
			target_angular_velocity = target_angular_velocity * ( -1 );
		}

	}else if( rest_degree < 0 ){
		target_angular_velocity = ( -1 ) * sqrt( fabs( 2 * a_down * rest_degree ) );

	}else{
		target_angular_velocity =  sqrt( fabs( 2 * a_down * rest_degree ) );
	}

	return ( target_angular_velocity );
}

/******************************************************************************
*	タイトル ： x方向出力決定
*	  関数名 ： get_motor_output_x
*	   引数1 ： float型 straight  直進方向の出力
*	   引数2 ： float型 target_degree  現在座標と目標座標の角度
*	  作成者 ： 成宮陽生
*	  作成日 ： 2014/09/22
******************************************************************************/
float get_motor_output_x( float straight , float target_degree )
{
	float	degree_reverse	= 0.00,
			Motor_output_x	= 0.00;

	if( straight < 0 ){
		degree_reverse = 180.0;
	}else{
		degree_reverse = 0.00;
	}
	
	Motor_output_x = fabs( straight ) * cos( D_TO_R( revision_degree( target_degree + degree_reverse ) ) );

	return( Motor_output_x );
}

/******************************************************************************
*	タイトル ： y方向出力決定
*	  関数名 ： get_motor_output_y
*	   引数1 ： float型 straight  直進方向の出力
*	   引数2 ： float型 target_degree  現在座標と目標座標の角度
*	  作成者 ： 成宮陽生
*	  作成日 ： 2014/09/22
******************************************************************************/
float get_motor_output_y( float straight , float target_degree )
{
	float	degree_reverse	= 0.00,
			Motor_output_y	= 0.00;

	if( straight < 0 ){
		degree_reverse = 180.0;
	}else{
		degree_reverse = 0.00;
	}
	
	Motor_output_y = fabs( straight ) * sin( D_TO_R( revision_degree( target_degree + degree_reverse ) ) );

	return( Motor_output_y );
}

/******************************************************************************
*	タイトル ： 角度を-180度～180度に変換する関数
*	  関数名 ： revision_degree
*	  戻り値 ： float型 -180度～180度変換
*	   引数1 ： float型 degree  
*	  作成者 ： 成宮陽生
*	  作成日 ： 2014/09/22
******************************************************************************/
float revision_degree( float degree )
{
	for( ; degree> 180.0;degree -= 360.0 ){}

	for( ; degree < -180.0; degree += 360.0){}

	return ( degree );
}
/*
void Calculate_Information_3tire(robot_information_t *robot)
{
	static int encoder_count_old_f = 0,	encoder_count_old_l = 0,	encoder_count_old_r = 0;
	float d_distance_f = 0.0, d_distance_l = 0.0, d_distance_r = 0.0;
	float reverse_degree_f = 0.0, reverse_degree_l = 0.0, reverse_degree_r = 0.0;
	int gap_left_encoder_count = 0, gap_right_encoder_count = 0, gap_front_encoder_count = 0;
	float radian_f = 0.0, radian_l = 0.0, radian_r = 0.0 ;
	float velocity_x = 0.00, velocity_y = 0.00;
	float old_degree = 0.00;
	static float movement_f_x = 0.0,	movement_f_y = 0.0,
						movement_l_x = 0.0, movement_l_y = 0.0,
						movement_r_x = 0.0, movement_r_y = 0.0;
	static float old_x = 0.00, old_y = 0.00;

	//車体を真上から見て、車体が反時計回転する方向に動くときのエンコーダカウントを正とする

	robot->enc_cnt.f = (-1) * ENCF();
	robot->enc_cnt.l = ENCL();
	robot->enc_cnt.r = ENCR();

	robot->enc_cnt.f = (-1)*(int)(get_atoz_value('b'-'a'));
	robot->enc_cnt.l = (int)(get_atoz_value('a'-'a'));
	robot->enc_cnt.r = (int)(get_atoz_value('c'-'a'));

	gap_left_encoder_count = robot->enc_cnt.l - encoder_count_old_l;
	gap_right_encoder_count = robot->enc_cnt.r - encoder_count_old_r;
	gap_front_encoder_count = robot->enc_cnt.f - encoder_count_old_f;

	//各エンコーダの微小移動距離を算出
	d_distance_f = (((float)(gap_front_encoder_count)) /PULSE)  * (ENC_DIAMETER_F);
	d_distance_l = (((float)(gap_left_encoder_count)) / PULSE)* (ENC_DIAMETER_L);
	d_distance_r = (((float)(gap_right_encoder_count)) / PULSE) * (ENC_DIAMETER_R);

	//各エンコーダの微小移動距離からラジアンを求める
	radian_f = d_distance_f / CENTER_TO_ENC;
	radian_l = d_distance_l / CENTER_TO_ENC;
	radian_r = d_distance_r / CENTER_TO_ENC;

	//車体角度を算出
	robot->angle.degree += R_TO_D( (radian_f + radian_l + radian_r) / 3);
	//robot->angle.degree = revision_degree(robot->angle.degree);

	//各エンコーダの微小移動方向からの角度反転
	if(d_distance_l < 0){
		 reverse_degree_l = 180.0;
	}
	if(d_distance_r < 0){
		reverse_degree_r = 180.0;
	}
	if(d_distance_f < 0){
		reverse_degree_f = 180.0;
	}

	//各エンコーダの微小移動から求まるｘ、y方向の移動量を計算して2倍する
	movement_f_x += 2.0 * ( fabs( d_distance_f ) * cos( D_TO_R( robot->angle.degree + 90.0 + reverse_degree_f )));
	movement_f_y += 2.0 * ( fabs( d_distance_f ) * sin( D_TO_R( robot->angle.degree + 90.0 + reverse_degree_f )));
	movement_l_x += 2.0 * ( fabs( d_distance_l ) * cos( D_TO_R( robot->angle.degree - 150.0 + reverse_degree_l )));
	movement_l_y += 2.0 * ( fabs( d_distance_l ) * sin( D_TO_R( robot->angle.degree - 150.0 + reverse_degree_l )));
	movement_r_x += 2.0 * ( fabs( d_distance_r ) * cos( D_TO_R( robot->angle.degree - 30.0 + reverse_degree_r )));
	movement_r_y += 2.0 * ( fabs( d_distance_r ) * sin( D_TO_R( robot->angle.degree - 30.0 + reverse_degree_r )));

	movement_f_x += 2.0 * ( fabs( d_distance_f ) * cos( D_TO_R( robot->angle.degree + 0.0 + reverse_degree_f )));
	movement_f_y += 2.0 * ( fabs( d_distance_f ) * sin( D_TO_R( robot->angle.degree + 0.0 + reverse_degree_f )));
	movement_l_x += 2.0 * ( fabs( d_distance_l ) * cos( D_TO_R( robot->angle.degree - 150.0 + reverse_degree_l )));
	movement_l_y += 2.0 * ( fabs( d_distance_l ) * sin( D_TO_R( robot->angle.degree - 150.0 + reverse_degree_l )));
	movement_r_x += 2.0 * ( fabs( d_distance_r ) * cos( D_TO_R( robot->angle.degree - 30.0 + reverse_degree_r )));
	movement_r_y += 2.0 * ( fabs( d_distance_r ) * sin( D_TO_R( robot->angle.degree - 30.0 + reverse_degree_r )));

	//車体中心座標を算出
	robot->cood.c_x = (movement_f_x + movement_l_x + movement_r_x) / 3.0;
	robot->cood.c_y = (movement_f_y + movement_l_y + movement_r_y) / 3.0;

	velocity_x	= ( robot->cood.c_x - old_x ) / INTERRUPT_TIME;
	velocity_y	= ( robot->cood.c_y - old_y ) / INTERRUPT_TIME;

	robot->velocity.velocity	= sqrt( ( velocity_x * velocity_x ) + ( velocity_y * velocity_y ) );
	robot->velocity.angular_velocity = ( revision_degree(robot->angle.degree - old_degree) ) / INTERRUPT_TIME;

	encoder_count_old_f = robot->enc_cnt.f;
	encoder_count_old_l = robot->enc_cnt.l;
	encoder_count_old_r = robot->enc_cnt.r;
	old_x = robot->cood.c_x, old_y = robot->cood.c_y;
	old_degree = robot->angle.degree;
}*/

void get_robot_inf( robot_information_t *robot )
{
	float	enc_dis_f				= 0.00,
			enc_dis_r				= 0.00,
			enc_dis_l				= 0.00,
			enc_dis_subt_f		= 0.00,
			enc_dis_subt_r	= 0.00,
			enc_dis_subt_l		= 0.00,
			radian_f					= 0.00,
			radian_r					= 0.00,
			radian_l					= 0.00,
			degree_reverse_f	= 0.00,
			degree_reverse_r	= 0.00,
			degree_reverse_l 	= 0.00,
			velocity_x				= 0.00,
			velocity_y				= 0.00;

	static float	enc_x_f			= 0.00,
					enc_y_f				= 0.00,
					enc_x_r				= 0.00,
					enc_y_r				= 0.00,
					enc_x_l				= 0.00,
					enc_y_l				= 0.00,
					old_x					= 0.00,
					old_y					= 0.00,
					degree					= 0.00,
					old_degree			= 0.00,
					old_enc_dis_f		= 0.00,
					old_enc_dis_r		= 0.00,
					old_enc_dis_l		= 0.00;

	if(robot->sw.start_sw == ON){
		robot->enc_cnt.f = (-1)*(get_atoz_value('b'-'a'));
		robot->enc_cnt.l = (get_atoz_value('a'-'a'));
		robot->enc_cnt.r = (get_atoz_value('c'-'a'));

		enc_dis_f = ENC_DIAMETER_F * M_PI * ( robot->enc_cnt.f / PULSE );
		enc_dis_r = ENC_DIAMETER_R * M_PI * (robot->enc_cnt.r / PULSE );
		enc_dis_l = ENC_DIAMETER_L * M_PI * ( robot->enc_cnt.l / PULSE );

		enc_dis_subt_f = enc_dis_f - old_enc_dis_f;
		enc_dis_subt_r = enc_dis_r - old_enc_dis_r;
		enc_dis_subt_l = enc_dis_l - old_enc_dis_l;

		radian_f = enc_dis_subt_f / CENTER_TO_ENC;
		radian_r = enc_dis_subt_r / CENTER_TO_ENC;
		radian_l = enc_dis_subt_l / CENTER_TO_ENC;

		degree += R_TO_D( ( radian_f + radian_r + radian_l ) / 3 );

		robot->angle.degree = revision_degree( degree );

		if( enc_dis_subt_f < 0 ){
			 degree_reverse_f = 180.0;
		}
		if( enc_dis_subt_r < 0 ){
			degree_reverse_r = 180.0;
		}
		if( enc_dis_subt_l < 0 ){
			degree_reverse_l = 180.0;
		}

		/*enc_x_f += 2 * fabs( enc_dis_subt_f ) * cos( D_TO_R( revision_degree( 90 + robot->angle.degree + degree_reverse_f ) ) );
		enc_y_f += 2 * fabs( enc_dis_subt_f ) * sin( D_TO_R( revision_degree( 90 + robot->angle.degree +degree_reverse_f ) ) );
		enc_x_r += 2 * fabs( enc_dis_subt_r ) * cos( D_TO_R( revision_degree( -30 + robot->angle.degree + degree_reverse_r ) ) );
		enc_y_r += 2 * fabs( enc_dis_subt_r ) * sin( D_TO_R( revision_degree(-30 + robot->angle.degree + degree_reverse_r ) ) );
		enc_x_l += 2 * fabs( enc_dis_subt_l ) * cos( D_TO_R( revision_degree( 30 + 180 + robot->angle.degree + degree_reverse_l ) ) );
		enc_y_l += 2 * fabs( enc_dis_subt_l ) * sin( D_TO_R( revision_degree( 30 + 180 + robot->angle.degree + degree_reverse_l ) ) );*/

		enc_x_f += 2 * fabs( enc_dis_subt_f ) * cos( D_TO_R( revision_degree( -180 + robot->angle.degree + degree_reverse_f ) ) );
		enc_y_f += 2 * fabs( enc_dis_subt_f ) * sin( D_TO_R( revision_degree( -180 + robot->angle.degree +degree_reverse_f ) ) );
		enc_x_r += 2 * fabs( enc_dis_subt_r ) * cos( D_TO_R( revision_degree( 60 + robot->angle.degree + degree_reverse_r ) ) );
		enc_y_r += 2 * fabs( enc_dis_subt_r ) * sin( D_TO_R( revision_degree( 60 + robot->angle.degree + degree_reverse_r ) ) );
		enc_x_l += 2 * fabs( enc_dis_subt_l ) * cos( D_TO_R( revision_degree( -60 + robot->angle.degree + degree_reverse_l ) ) );
		enc_y_l += 2 * fabs( enc_dis_subt_l ) * sin( D_TO_R( revision_degree( -60  + robot->angle.degree + degree_reverse_l ) ) );

		robot->coord.c_x = ( enc_x_f + enc_x_r + enc_x_l ) / 3;
		robot->coord.c_y = ( enc_y_f + enc_y_r + enc_y_l ) / 3;

		old_enc_dis_f = enc_dis_f;
		old_enc_dis_r = enc_dis_r;
		old_enc_dis_l = enc_dis_l;

		velocity_x = (( robot->coord.c_x - old_x ) / (INTERRUPT_TIME / 1000));
		velocity_y = (( robot->coord.c_y - old_y ) / (INTERRUPT_TIME / 1000));

		robot->velocity.velocity	= sqrt( ( velocity_x * velocity_x ) + ( velocity_y * velocity_y ) );
		robot->velocity.angular_velocity = ( revision_degree(robot->angle.degree - old_degree) ) / INTERRUPT_TIME;

		old_x = robot->coord.c_x;
		old_y = robot->coord.c_y;
		old_degree = robot->angle.degree;
	}
}

void init_robot_inf(robot_information_t *robot)
{
	robot->coord.c_x = START_X;
	robot->coord.c_y = START_Y;
	robot->angle.degree = START_DEGREE;
}

float get_Average( int number_scope, int box, float add ){
    static float average[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    static float number[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    if(number[box] >= number_scope){
        number[box] = (number_scope - 1);
    }

    average[box] *= number[box];
    average[box] += add;
    number[box] ++;
    average[box] = average[box] / number[box];

    return (average[box]);
}

void sonic_waves(robot_information_t *robot)
{
	static int phase_count = 0;

	Init_port(GPIO_Mode_OUT,TRIG, GPIO_PuPd_UP, GPIO_OType_PP);	//超音波
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
			robot->waves = get_Average( 20 , 1 ,count_time(2) * 0.17 );

			if(robot->waves <= 50){
				robot->waves = 0;
				robot->waves_on = OFF;
			}else{
				robot->waves_on = ON;
			}

			reset_count_time(2);
			phase_count = 0;
		}
	}
}

void position_rock(robot_information_t *robot, motor_output_t *motor)
{
	float	output				 = 0.00,
			output_x			 = 0.00,
			output_y			 = 0.00;
	float	p_gain			     = 0.50,
			d_gain				 = 1.00;
	float	now_gap			 = 0.00;
	float target_degree	 = 0.00;

	static float old_gap	= 0.00;

	now_gap = get_twopoints_distance(robot->old_coord.c_x - robot->coord.c_x, robot->old_coord.c_y - robot->coord.c_y );

	output = ( p_gain * now_gap ) + ( d_gain * ( now_gap - old_gap ) );

	old_gap = now_gap;

	target_degree = get_target_degree( robot->old_coord.c_x - robot->coord.c_x, robot->old_coord.c_y - robot->coord.c_y );

	output_x = output * cos( D_TO_R( revision_degree( target_degree ) ) );
	output_y = output * sin( D_TO_R( revision_degree( target_degree ) ) );

	motor->l	 = get_motor_output_l( output_x, output_y, robot->angle.degree ,-120);
	motor->r = get_motor_output_r( output_x, output_y, robot->angle.degree ,120);
	motor->b = get_motor_output_b( output_x, output_y, robot->angle.degree ,0);
}

void init_arm(robot_information_t *robot)
{
	static short limit_sw = 0;

	limit_sw = positive_chattering(LIMIT_SW,3);

	if(limit_sw == EDGE_UP){
		robot->sw.limit_sw = 1;
	}

	if(robot->sw.limit_sw != 1){
		move_arm(-100);
	}else{
		move_arm(0);
	}
}

void arm_length(robot_information_t *robot)
{
	static int start = 0;
	static short init_ad_value = 0;
	static int flag = 0;

	if(robot->sw.limit_sw == 1 && flag == 0) {
		if(start >= 100){
			flag = 1;
		}
		if(flag != 1){
			init_ad_value =  get_Average( 20, 0, get_ADC1_value(0) );
		}
		if(start <=100){
			start += INTERRUPT_TIME;
		}
	}

	if(robot->sw.limit_sw == 1){
		robot->ad = get_Average(20, 0, get_ADC1_value(0));
		robot->arm_dis =  ( ( ((float)robot->ad - (float)init_ad_value) * 150.0 ) / 267.0 ) + 150.0;
		robot->coord.arm_x = (robot->arm_dis) * cos(D_TO_R(robot->angle.degree)) + robot->coord.c_x;
		robot->coord.arm_y = (robot->arm_dis) * sin(D_TO_R(robot->angle.degree)) + robot->coord.c_y;
	}else{
		robot->coord.arm_x = 0.00;
		robot->coord.arm_y = 0.00;
	}
}

void search(robot_information_t *robot, target_t *target, motor_output_t *motor)
{
	static int task = 0;
	float straight = 0.00;

	switch(task){
		case 0:
			target->coord.c_x = robot->coord.c_x;
			target->coord.c_y = 200;
		break;
		case 1:
			target->coord.c_x = robot->coord.c_x;
			target->coord.c_y = 0;
		break;
		case 2:
			target->coord.c_x = robot->coord.c_x;
			target->coord.c_y = -200;
		break;
	}

	//add_output = get_Average(20, 1, Absolute_duty(100, 50, robot.velocity.velocity));
	target->distance.between_two_points = get_twopoints_distance( target->coord.c_x - robot->coord.c_x, target->coord.c_y - robot->coord.c_y );
	target->angle.degree = get_target_degree( target->coord.c_x - robot->coord.c_x, target->coord.c_y - robot->coord.c_y );
	target->distance.vertical = get_vertical_distance( target->angle.degree, target->distance.between_two_points );
	target->velocity.velocity = get_target_velocity( target->distance.between_two_points, target->distance.vertical, 1000, 1000, 10);
	straight = pd_straight(target->velocity.velocity - robot->velocity.velocity);
	motor->x = get_motor_output_x(straight, target->angle.degree);
	motor->y = get_motor_output_y(straight, target->angle.degree);

	if(target->distance.between_two_points < 10){
		task ++;
	}
	if(task == 3){
		task = 0;
	}
}

