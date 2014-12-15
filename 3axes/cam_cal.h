#ifndef CAM_CAL_H
#define CAM_CAL_H

#define UNDER_CAM_HIGH		110.0
#define OVER_CAM_HIGH			260.0

#define CAM_ANGLR_RANGE	15.0//’PˆÊ(“x)

#define UNDER_CAM_ANGLE	30.0
#define OVER_CAM_ANGLE		30.0

#define PC_PICTURE_X				320.0
#define HALF_PC_PICTURE_X	(PC_PICTURE_X / 2.0)
#define PC_PICTURE_Y				180.0

#define UNDER_CAM_POSI_X	95.0
#define UNDER_CAM_POSI_Y	0.0
#define OVER_CAM_POSI_X		85.0
#define OVER_CAM_POSI_Y		0.0

typedef struct{
	float x;
	float y;
	float under_x;
	float under_y;
	float over_x;
	float over_y;
}target_cam_t;

void cam_data(target_cam_t *target_cam, robot_information_t *robot);

#endif
