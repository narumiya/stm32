
#include "analysis_data_type.h"
#include <math.h>
#include <string.h>

void convert_short_2byte(char *result, short data, unsigned char min_array)
{
	result[min_array] = data;
	result[min_array + 1] = data >> 8;
}
void convert_int_4byte(char *result, int data, unsigned char min_array)
{
	result[min_array] = data;
	result[min_array + 1] = data >> 8;
	result[min_array + 2] = data >> 16;
	result[min_array + 3] = data >> 24;
}
void convert_float_4byte(char *result, float data, unsigned char min_array)
{
	union{
		float f;
		char byte[4];
	}buffer;

	buffer.f = data;
	result[min_array] 	  = buffer.byte[0];
	result[min_array + 1] = buffer.byte[1];
	result[min_array + 2] = buffer.byte[2];
	result[min_array + 3] = buffer.byte[3];
}
void convert_double_8byte(char *result, double data, unsigned char min_array)
{
	union{
		double d;
		char byte[8];
	}buffer;

	buffer.d = data;
	result[min_array]	  = buffer.byte[0];
	result[min_array + 1] = buffer.byte[1];
	result[min_array + 2] = buffer.byte[2];
	result[min_array + 3] = buffer.byte[3];
	result[min_array + 4] = buffer.byte[4];
	result[min_array + 5] = buffer.byte[5];
	result[min_array + 6] = buffer.byte[6];
	result[min_array + 7] = buffer.byte[7];
}

short convert_2byte_short(char data[], unsigned char min_array)
{
	short result = 0;
	result  = (short)(data[min_array]);
	result += (short)(data[min_array + 1] << 8);
	return (result);
}

int convert_4byte_int(char data[], unsigned char min_array)
{
	int result = 0;
	result  = (int)(data[min_array]);
	result += (int)(data[min_array + 1] << 8);
	result += (int)(data[min_array + 2] << 16);
	result += (int)(data[min_array + 3] << 24);
	return (result);
}

float convert_4byte_float(char data[], unsigned char min_array)
{
	float result = 0.0;
	float fraction = 0.0;
	int exponent = 0;
	const int bias = 127;
	int sign = 0;
	int i = 0,j = 0, k = 0;

	char bit[32];
	unsigned char ch = 0;

	for(i=3; i >= 0; i--) { //　文字型で１バイトごとに取り出す
		ch = data[i + min_array];
		for(j = 7; j >= 0; j--){//  １バイト単位で２進数に変換を行う
		   if( (ch >> j) & 1 ){
				bit[k] = 1;
		   }else{
				bit[k] = 0;
		   }
			// ビットを出力
		   k++;
		}
	}

	sign = 1 - 2 * bit[0];	//符号ビット
	//指数部を10進数に変換
	for(i = 8; i >= 1; i --){
		exponent += (int)(bit[i] * powf(2, 8 - i));
	}
	//仮数部を10進数に変換
	for(i = 9; i <= 31; i ++){
		fraction += (float)bit[i] * powf(2, 8 - i);
	}
	result = (float)(sign * (1.0 + fraction)) * powf(2.0, (float)exponent - bias);

	return(result);
}

double convert_8byte_double(char data[], unsigned char min_array)
{
	double result = 0.0;
	double fraction = 0.0;
	int exponent = 0;
	const int bias = 1023;
	int sign = 0;
	int i = 0,j = 0, k = 0;

	char bit[32];
	unsigned char ch = 0;

	for(i = 7; i >= 0; i--) { //　文字型で１バイトごとに取り出す
		ch = data[i + min_array];
		for(j = 7; j >= 0; j--){//  １バイト単位で２進数に変換を行う
		   if( (ch >> j) & 1 ){
				bit[k] = 1;
		   }else{
				bit[k] = 0;
		   }
			// ビットを出力
		   k++;
		}
	}

	sign = 1 - 2 * bit[0];
	for(i = 11; i >= 1; i --){
		exponent += (int)(bit[i] * pow(2, 11 - i));
	}
	for(i = 12; i <= 63; i ++){
		fraction += (double)bit[i] * pow(2,11 - i);
	}
	result = (double)(sign * (1.0 + fraction)) * pow(2.0, (double)exponent - bias);

	return(result);
}
