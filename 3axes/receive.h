#ifndef RECEIVE_H
#define RCEIVE_H

#include <string.h>
#include <math.h>

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#define EN 							'#'			//�ʐM�f�[�^�̏I�[����
#define RECEIVE_STR_COLUMN 32		//1�f�[�^������̍ő啶����		��: a123# (6����)

void receive_att( void );

void receive_order_depot( int target_box , char *storage_str , int minus_flag , int after_point_count , int large_size_flag );

void receive_order_c(char character);

float change_float(char *str);

char Receive_usart1_c(void);

char Receive_usart2_c(void);

char Receive_usart3_c(void);

float get_atoz_value(int i);

float get_AtoZ_value(int i);

#endif
