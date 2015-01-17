#ifndef DEFINE_H
#define DEFINES_H

#define 	OFF			0
#define 	ON			1
#define	LOW			0
#define 	HIGH		1
#define	CW			3
#define	CCW			4
#define	FRONT		5
#define 	BACK		6
#define 	TOP			7
#define 	UNDER		8
#define 	BRAKE		9999

#define 	INTERRUPT_UNIT_TIME_S		0.001
#define 	INTERRUPT_TIME_US				10000
#define 	INTERRUPT_TIME_MS				10
#define 	INTERRUPT_TIME_S				0.01

#define SERVE_TIME								1000
//#define 	M_PI	3.14159265

#define MOTOR_MODE	MOTOR_DOUBLE
#define MOTOR_SINGLE	1
#define MOTOR_DOUBLE	2

//サーボの初期角度
#define INIT_ANGLE			90.0

#define SERVE_START_BOTTUN 			PS3.Circle
#define AIR1  GPIOD, GPIO_Pin_0

#define	PC transmit_usart2_c
//#define 	PC usb_put_char
//#define	SERVO transmit_usart3_c

#endif
