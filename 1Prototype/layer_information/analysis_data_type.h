
#ifndef ANALYSIS_DATA_TYPE_H
#define ANALYSIS_DATA_TYPE_H

//short型のデータを2byteのデータに変換
void convert_short_2byte(char *result, short data, unsigned char min_array);

//int型のデータを4byteのデータに変換
void convert_int_4byte(char *result, int data, unsigned char min_array);

//float型のデータを4byteのデータに変換
void convert_float_4byte(char *result, float data, unsigned char min_array);

//double型のデータを8byteのデータに変換
void convert_double_8byte(char *result, double data, unsigned char min_array);

//2byteのchar型データをshort型に変換
short convert_2byte_short(char data[], unsigned char min_array);

//4byteのchar型データをint型に変換
int convert_4byte_int(char data[], unsigned char min_array);

//4byteのchar型データをfloat型に変換
float convert_4byte_float(char data[], unsigned char min_array);

//8byteのchar型データをdouble型に変換
double convert_8byte_double(char data[],  unsigned char min_array);

#endif
