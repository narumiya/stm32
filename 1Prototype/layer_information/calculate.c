
#include "calculate.h"

/******************************************************************************
*	�^�C�g�� �F �l�̏㉺������
*	  �֐��� �F Limit_ul
*	  �߂�l �F float�^
*	   ����1 �F float�^ upper  �l�̏��
*	   ����2 �F float�^ lower  �l�̉���
*	   ����3 �F float�^ figure  ���͒l
*	  �쐬�� �F �≺���F
*	  �쐬�� �F 2014/11/10
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
*	�^�C�g�� �F ���W�A�����x�ւ̕ϊ�
*	  �֐��� �F Convert_to_degree
*	  �߂�l �F float�^
*	   ����1 �F float�^ radian  ���W�A��[rad]
*	  �쐬�� �F �≺���F
*	  �쐬�� �F 2014/11/10
******************************************************************************/
float convert_to_degree(float radian)
{
	return (radian * 180.0 / M_PI);
}
/******************************************************************************
*	�^�C�g�� �F �x�����W�A���ւ̕ϊ�
*	  �֐��� �F Convert_to_radian
*	  �߂�l �F float�^
*	   ����1 �F float�^ degree  �p�x[�x]
*	  �쐬�� �F �≺���F
*	  �쐬�� �F 2014/11/10
******************************************************************************/
float convert_to_radian(float degree)
{
	return (degree * M_PI / 180.0);
}
/******************************************************************************
*	�^�C�g�� �F 2�_�Ԃ̋�����Ԃ�
*	  �֐��� �F get_distance
*	  �߂�l �F float�^
*	   ����1 �F float�^ target_x  �ڕWx���W
*	   ����2 �F float�^ target_y  �ڕWy���W
*	   ����3 �F float�^ x_now  ����x���W
*	   ����4 �F float�^ y_now  ����y���W
*	  �쐬�� �F �≺���F
*	  �쐬�� �F 2014/11/10
******************************************************************************/
float get_distance(float target_x, float target_y, float x_now, float y_now)
{
	return sqrtf(powf(target_x - x_now, 2) + powf(target_y - y_now, 2));
}
/******************************************************************************
*	�^�C�g�� �F �ڕW���W�ƌ��ݍ��W����p�x��Ԃ�
*	  �֐��� �F get_target_degree
*	  �߂�l �F float�^
*	   ����1 �F float�^ target_x  �ڕWx���W
*	   ����2 �F float�^ target_y  �ڕWy���W
*	   ����3 �F float�^ x_now  ����x���W
*	   ����4 �F float�^ y_now  ����y���W
*	  �쐬�� �F �≺���F
*	  �쐬�� �F 2014/11/10
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
*	�^�C�g�� �F �ڕW�p�x�ƌ��݊p�x�̍�����Ԃ�
*	  �֐��� �F get_gap_degree
*	  �߂�l �F float�^
*	   ����1 �F float�^ target_degree  �ڕW�p�x
*	   ����2 �F float�^ degree_now  ���݊p�x
*	  �쐬�� �F �≺���F
*	  �쐬�� �F 2014/11/10
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
*	�^�C�g�� �F �l�̃u��������������
*	  �֐��� �F get_Average
*	  �߂�l �F float�^
*	   ����1 �F int�^ number_scope
*	   ����2 �F int�^ box
*	   ����3 �F float�^ add
*	  �쐬�� �F �����N�G
*	  �쐬�� �F 2013/02/16
******************************************************************************/
float get_Average(int number_scope, int box, float add)
{
	static float average[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	static float number[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	if(number[box] >= number_scope){		//�񐔂������߂����烊�Z�b�g����
		number[box] = (number_scope-1);
	}

	average[box] *= number[box];			//�O��܂ł̕��ϒl�Ɖ񐔂��獇�v�����߂�
	average[box] += add;				//����̓��͒l��������
	number[box]++;					//�񐔂̒l��1�����A����̉񐔂ɂ���
	average[box] = average[box]/number[box];	//���v������̉񐔂Ŋ���

	return (average[box]);				//����̕��ϒl��Ԃ�
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
		return ((-1)*distance * cos(convert_to_radian(90-fabs(degree_gap))));//�ԑ̂̌����ɑ΂��Đ�����������
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
		return((-1)*distance * sin(convert_to_radian(90 - fabs(degree_gap))));//�ԑ̂̌����ɑ΂��Đ������������
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

