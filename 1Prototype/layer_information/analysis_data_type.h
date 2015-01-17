
#ifndef ANALYSIS_DATA_TYPE_H
#define ANALYSIS_DATA_TYPE_H

//short�^�̃f�[�^��2byte�̃f�[�^�ɕϊ�
void convert_short_2byte(char *result, short data, unsigned char min_array);

//int�^�̃f�[�^��4byte�̃f�[�^�ɕϊ�
void convert_int_4byte(char *result, int data, unsigned char min_array);

//float�^�̃f�[�^��4byte�̃f�[�^�ɕϊ�
void convert_float_4byte(char *result, float data, unsigned char min_array);

//double�^�̃f�[�^��8byte�̃f�[�^�ɕϊ�
void convert_double_8byte(char *result, double data, unsigned char min_array);

//2byte��char�^�f�[�^��short�^�ɕϊ�
short convert_2byte_short(char data[], unsigned char min_array);

//4byte��char�^�f�[�^��int�^�ɕϊ�
int convert_4byte_int(char data[], unsigned char min_array);

//4byte��char�^�f�[�^��float�^�ɕϊ�
float convert_4byte_float(char data[], unsigned char min_array);

//8byte��char�^�f�[�^��double�^�ɕϊ�
double convert_8byte_double(char data[],  unsigned char min_array);

#endif
