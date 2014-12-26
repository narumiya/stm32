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
	unsigned short raw;						//�`���^�����O����̃f�[�^
	unsigned short info;						//�`���^�����O�Ȃ��̃f�[�^
	unsigned int count;						//��������
	unsigned short flag_up_edge;		//�A�b�v�G�b�W�t���O
	unsigned short flag_down_edge;	//�_�E���G�b�W�t���O
	unsigned short state;					//�ꎞ�I�ɕۑ����Ă����{�^���f�[�^
	unsigned int timer;						//�`���^�����O����J�E���g
	unsigned short old;						//��O�̃{�^�����
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
