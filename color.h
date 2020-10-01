#ifndef __COLOR_H__
#define __COLOR_H__

#include <stdio.h>
#include "vector3.h"

#define color_set vec3_set
#define color_get_r vec3_get_x
#define color_get_g vec3_get_y
#define color_get_b vec3_get_z

typedef vec3_t color_t;

void write_color(FILE *stream, color_t *color);

#endif
