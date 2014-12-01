#include <math.h>

#include "robo_data.h"
#include "cam_cal.h"
#include "receive.h"
#include "my_standard_io.h"
#include "trancemit.h"
#include "robo_finction.h"
#include "defines.h"

void cam_data(target_cam_t *target_cam, robot_information_t *robot)
{
	target_cam->under_x = get_atoz_value((int)('d'-'a'));
	target_cam->under_y = get_atoz_value((int)('e'-'a'));
	target_cam->over_x = get_atoz_value((int)('f'-'a'));
	target_cam->over_y = get_atoz_value((int)('g'-'a'));

	if(target_cam->under_x == 0 && target_cam->under_y == 0 && target_cam->over_x == 0 && target_cam->over_y == 0){
		buzzer_on( );
		GPIO_SetBits(GPIOD,  GPIO_Pin_14);
	}else{
		if(target_cam->under_x == -1 && target_cam->under_y == -1 && target_cam->over_x == -1 && target_cam->over_y == -1){
			GPIO_ResetBits(GPIOD,  GPIO_Pin_14);
			target_cam->x = UNDISCOVERED;
			target_cam->y = UNDISCOVERED;

		}else if(target_cam->under_x == -1 && target_cam->under_y == -1){
			GPIO_ResetBits(GPIOD,  GPIO_Pin_14);
			target_cam->x = OVER_CAM_HIGH * tan(D_TO_R(90 - CAM_ANGLR_RANGE - (target_cam->over_y / 6))) + OVER_CAM_POSI_X;
			target_cam->y = ( (HALF_PC_PICTURE_X - target_cam->over_x ) / (HALF_PC_PICTURE_X ) ) * (target_cam->x / 2) + OVER_CAM_POSI_Y;

		}else if(target_cam->over_x == -1 && target_cam->over_y == -1){
			GPIO_ResetBits(GPIOD,  GPIO_Pin_14);
			target_cam->x = UNDER_CAM_HIGH * tan(D_TO_R(90 - CAM_ANGLR_RANGE - (target_cam->under_y / 6))) + UNDER_CAM_POSI_X;
			target_cam->y = ( (HALF_PC_PICTURE_X - target_cam->under_x)/ (HALF_PC_PICTURE_X * 2) ) * (target_cam->x / 2) + UNDER_CAM_POSI_Y;

		}else{
			GPIO_ResetBits(GPIOD,  GPIO_Pin_14);
			target_cam->x = OVER_CAM_HIGH * tan(D_TO_R(90 - CAM_ANGLR_RANGE - (target_cam->over_y / 6))) + OVER_CAM_POSI_X;
			target_cam->y = ( (HALF_PC_PICTURE_X - target_cam->over_x ) / (HALF_PC_PICTURE_X ) ) * (target_cam->x / 2) + OVER_CAM_POSI_Y;
		}
	}

#ifdef DEBUG_CAM_DATA
	f2_print(PC, "under", target_cam->under_x, target_cam->under_y);
	f2_print(PC, "over", target_cam->over_x, target_cam->over_y);
#endif
}
