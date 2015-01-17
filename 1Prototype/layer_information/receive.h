#ifndef RECEIVE_H
#define RCEIVE_H

#include <string.h>
#include <math.h>

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#include "typedef.h"

#define EN 									'#'		//通信データの終端文字
#define RECEIVE_STR_COLUMN 	32		//1データあたりの最大文字数		例: a123# (6文字)

#define MAX_TYPE							1

#define TYPE0_DATA0	PS3->Up
#define TYPE0_DATA1	PS3->Down
#define TYPE0_DATA2	PS3->Left
#define TYPE0_DATA3	PS3->Right
#define TYPE0_DATA4	PS3->Triangle
#define TYPE0_DATA5	PS3->Circle
#define TYPE0_DATA6	PS3->Cross
#define TYPE0_DATA7	PS3->Square

#define TYPE1_DATA0	PS3->L1
#define TYPE1_DATA1	PS3->L2
#define TYPE1_DATA2	PS3->R1
#define TYPE1_DATA3	PS3->R2
#define TYPE1_DATA4	PS3->Start
#define TYPE1_DATA5	PS3->Select
#define TYPE1_DATA6	PS3->error
#define TYPE1_DATA7	PS3->connect

#define TYPE2_DATA1
#define TYPE2_DATA2
#define TYPE2_DATA3
#define TYPE2_DATA4
#define TYPE2_DATA5
#define TYPE2_DATA6
#define TYPE2_DATA7

void receive_att( void );

void receive_order_depot( int target_box , char *storage_str , int minus_flag , int after_point_count , int large_size_flag );

void receive_order_c(char character);

float change_float(char *str);

char receive_usart1_c(void);

char receive_usart2_c(void);

char receive_usart3_c(void);

float get_atoz_value(int i);

float get_AtoZ_value(int i);

void receive_can_att(void);

void receive_data(char data[], PS3_Controller_t *PS3);

#endif
