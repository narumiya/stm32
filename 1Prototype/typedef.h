#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef struct{
	float x;
	float y;
	float z;
}Coodinate_t;

typedef struct{
	float degree;
	float radian;
}Angle_t;

typedef struct{
	Coodinate_t cood;
	float abs;
	float phase;
}Velocity_t;

typedef struct{
	Coodinate_t cood;
	float abs;
	float down;
	float up;
}Accel_t;

typedef struct {
	float l;
	float r;
	float b;
}Underbody_tire_t;

typedef struct{
	float l;
	float r;
	float f;
}Encoder_tire_t;

typedef struct{
	Encoder_tire_t enc_cnt;
	Coodinate_t cood;
	Coodinate_t arm_c;
	Coodinate_t camera_u;
	Coodinate_t camera_t;
	Angle_t angle;
	Angle_t omega;
	Velocity_t velocity;
	Velocity_t arm_vel;
}Robot_information_t;

typedef struct{
	float init_value;
	float now_value;
	float length;
}Potentio_information_t;

typedef struct{
	unsigned short raw;						//チャタリングありのデータ
	unsigned short info;						//チャタリングなしのデータ
	unsigned int count;						//押した回数
	unsigned short flag_up_edge;		//アップエッジフラグ
	unsigned short flag_down_edge;	//ダウンエッジフラグ
	unsigned short state;					//一時的に保存しておくボタンデータ
	unsigned int timer;						//チャタリング回避カウント
	unsigned short old;						//一つ前のボタン情報
}Button_information_t;

typedef struct{
	float data1;
	float data2;
	float data3;
	float data4;
	float data5;
	float data6;
	float data7;
	float data8;
}String_data_t;

typedef struct{
	float kp;
	float ki;
	float kd;
}Gain_t;

typedef struct{
	Coodinate_t cood;
	Velocity_t velocity;
	Angle_t angle;
	Angle_t omega;
}Target_t;

#endif
