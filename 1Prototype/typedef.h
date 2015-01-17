#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef struct{
	float x;
	float y;
	float z;
}Coordinate_t;

typedef struct{
	float degree;
	float radian;
}Angle_t;

typedef struct{
	Coordinate_t cood;
	float abs;
	float phase;
}Velocity_t;

typedef struct{
	Coordinate_t cood;
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
	Coordinate_t coord;
	Coordinate_t arm_c;
	Coordinate_t camera_u;
	Coordinate_t camera_t;
	Angle_t angle;
	Angle_t omega;
	Velocity_t velocity;
	Velocity_t arm_vel;
}Robot_information_t;

//ポテンショメータ構造体
typedef struct{
	float init_value;
	float now_value;
	float length;
	float degree;
}Potentio_t;

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
	Coordinate_t coord;
	Velocity_t velocity;
	Angle_t angle;
	Angle_t omega;
}Target_t;

typedef struct{
	short LjoyX;
	short LjoyY;
	short RjoyX;
	short RjoyY;

	short robot_LjoyX;
	short robot_LjoyY;
	short robot_RjoyX;
	short robot_RjoyY;

	unsigned short Up;
	unsigned short Right;
	unsigned short Down;
	unsigned short Left;
	unsigned short Triangle;
	unsigned short Circle;
	unsigned short Cross;
	unsigned short Square;
	unsigned short Start;
	unsigned short Select;
	unsigned short PS;
	unsigned short AccX;
	unsigned short AccY;
	unsigned short L1;
	unsigned short L2;
	unsigned short R1;
	unsigned short R2;

	unsigned short connect;
	unsigned short error;
}PS3_Controller_t;

#endif
