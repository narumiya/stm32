#ifndef CALCULATE_H
#define CALCULATE_H

#include <math.h>
#include "define.h"
#include "typedef.h"

float limit_ul(float upper, float lower, float figure);
float convert_to_degree(float radian);
float convert_to_radian(float degree);
float get_distance(float target_x, float target_y, float x_now, float y_now);
float get_target_degree(float target_x, float target_y, float x_now, float y_now);
float get_gap_degree(float target_degree, float degree_now);
float get_Average(int number_scope, int box, float add);
float get_horizontal_distance(float distance, float degree);
float get_vertical_distance(float distance, float degree);
float get_horizontal_distance_position(float target_x, float target_y, float x_now, float y_now, float degree_now);
float get_vertical_distance_position(float target_x, float target_y, float x_now, float y_now, float degree_now);
float get_target_degree_struct(Coordinate_t target, Coordinate_t now);
float get_horizontal_distance_struct(Coordinate_t target, Coordinate_t now, float degree);
float get_vertical_distance_struct(Coordinate_t target, Coordinate_t now, float degree);

#endif
