
#include "calculate.h"

/******************************************************************************
*	タイトル ： 値の上下限制限
*	  関数名 ： Limit_ul
*	  戻り値 ： float型
*	   引数1 ： float型 upper  値の上限
*	   引数2 ： float型 lower  値の下限
*	   引数3 ： float型 figure  入力値
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/10
******************************************************************************/
float limit_ul(float upper, float lower, float figure)
{
	if(figure > upper){
		return (upper);
	}else if(figure < lower){
		return (lower);
	}else{
		return (figure);
	}
}
/******************************************************************************
*	タイトル ： ラジアン→度への変換
*	  関数名 ： Convert_to_degree
*	  戻り値 ： float型
*	   引数1 ： float型 radian  ラジアン[rad]
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/10
******************************************************************************/
float convert_to_degree(float radian)
{
	return (radian * 180.0 / M_PI);
}
/******************************************************************************
*	タイトル ： 度→ラジアンへの変換
*	  関数名 ： Convert_to_radian
*	  戻り値 ： float型
*	   引数1 ： float型 degree  角度[度]
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/10
******************************************************************************/
float convert_to_radian(float degree)
{
	return (degree * M_PI / 180.0);
}
/******************************************************************************
*	タイトル ： 2点間の距離を返す
*	  関数名 ： get_distance
*	  戻り値 ： float型
*	   引数1 ： float型 target_x  目標x座標
*	   引数2 ： float型 target_y  目標y座標
*	   引数3 ： float型 x_now  現在x座標
*	   引数4 ： float型 y_now  現在y座標
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/10
******************************************************************************/
float get_distance(float target_x, float target_y, float x_now, float y_now)
{
	return sqrtf(powf(target_x - x_now, 2) + powf(target_y - y_now, 2));
}
/******************************************************************************
*	タイトル ： 目標座標と現在座標から角度を返す
*	  関数名 ： get_target_degree
*	  戻り値 ： float型
*	   引数1 ： float型 target_x  目標x座標
*	   引数2 ： float型 target_y  目標y座標
*	   引数3 ： float型 x_now  現在x座標
*	   引数4 ： float型 y_now  現在y座標
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/10
******************************************************************************/
float get_target_degree(float target_x, float target_y, float x_now, float y_now)
{
	static float target_degree_old = 0.0;
	float target_degree = 0.0;
	if((target_x - x_now != 0.0) || (target_y - y_now != 0.0)){
		target_degree = convert_to_degree(atan2(target_y - y_now, target_x - x_now));
		target_degree_old = target_degree;
	}else{
		target_degree = target_degree_old;
	}
	return (target_degree);
}
/******************************************************************************
*	タイトル ： 目標角度と現在角度の差分を返す
*	  関数名 ： get_gap_degree
*	  戻り値 ： float型
*	   引数1 ： float型 target_degree  目標角度
*	   引数2 ： float型 degree_now  現在角度
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/10
******************************************************************************/
float get_gap_degree(float target_degree, float degree_now)
{
	float gap_degree = 0.0;
	unsigned short i = 0;

	gap_degree = target_degree - degree_now;
	for(i = 0; i < 5; i ++){
		if(gap_degree > 180.0){
			gap_degree -= 360.0;
		}else if(gap_degree < -180.0){
			gap_degree += 360.0;
		}else{
			break;
		}
	}
	return (gap_degree);
}
/******************************************************************************
*	タイトル ： 値のブレを減少させる
*	  関数名 ： get_Average
*	  戻り値 ： float型
*	   引数1 ： int型 number_scope
*	   引数2 ： int型 box
*	   引数3 ： float型 add
*	  作成者 ： 眞下康宏
*	  作成日 ： 2013/02/16
******************************************************************************/
float get_Average(int number_scope, int box, float add)
{
	static float average[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	static float number[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	if(number[box] >= number_scope){		//回数が増え過ぎたらリセットする
		number[box] = (number_scope-1);
	}

	average[box] *= number[box];			//前回までの平均値と回数から合計を求める
	average[box] += add;				//今回の入力値を加える
	number[box]++;					//回数の値を1加え、今回の回数にする
	average[box] = average[box]/number[box];	//合計を今回の回数で割る

	return (average[box]);				//今回の平均値を返す
}
float get_horizontal_distance(float distance, float degree_gap)
{
	if(degree_gap > 90){
		degree_gap = 180 - degree_gap;
		}
	if(degree_gap < -90){
		degree_gap = -degree_gap - 180;
		}

	if(degree_gap > 0){
		return ((-1)*distance * cos(convert_to_radian(90-fabs(degree_gap))));//車体の向きに対して水平方向が左
	}else{
		return(distance * cos(convert_to_radian(90-fabs(degree_gap))));
	}
}
float get_vertical_distance(float distance, float degree_gap)
{
	int limit_over = OFF;
	if(degree_gap > 90){
		degree_gap = 180 - degree_gap;
		limit_over = ON;
		}
	if(degree_gap < -90){
		degree_gap = -degree_gap - 180;
		limit_over = ON;
		}

	if(limit_over == OFF){
		return (distance * sin(convert_to_radian(90 - fabs(degree_gap))));
	}else{
		return((-1)*distance * sin(convert_to_radian(90 - fabs(degree_gap))));//車体の向きに対して垂直方向が後方
	}
}
float get_horizontal_distance_position(float target_x, float target_y, float x_now, float y_now, float degree_now)
{
	return(get_horizontal_distance(get_distance(target_x,target_y,x_now,y_now),get_gap_degree(get_target_degree(target_x,target_y,x_now,y_now),degree_now)));
}
float get_vertical_distance_position(float target_x, float target_y, float x_now, float y_now, float degree_now)
{
	return(get_vertical_distance(get_distance(target_x,target_y,x_now,y_now),get_gap_degree(get_target_degree(target_x,target_y,x_now,y_now),degree_now)));
}


float get_target_degree_struct(Coordinate_t target, Coordinate_t now)
{
	return(get_target_degree(target.x, target.y, now.x, now.y));
}
float get_horizontal_distance_struct(Coordinate_t target, Coordinate_t now, float degree)
{
	return(get_horizontal_distance_position(target.x, target.y, now.x, now.y, degree));
}
float get_vertical_distance_struct(Coordinate_t target, Coordinate_t now, float degree)
{
	return(get_vertical_distance_position(target.x, target.y, now.x, now.y, degree));
}

