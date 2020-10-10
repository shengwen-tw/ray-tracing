#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdlib.h>
#include <math.h>

#define deg_to_rad(degree) (degree * M_PI / 180.0f)

float clamp(float x, float min, float max);
float random_float(void);
float clamped_random_float(float min, float max);

#endif
