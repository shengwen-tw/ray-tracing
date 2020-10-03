#include <stdlib.h>
#include <math.h>
#include "common.h"

float clamp(float x, float min, float max)
{
        if(x < min) return min;
        if(x > max) return max;
        return x;
}

float random_float(void)
{
        return random() / ((float)RAND_MAX + 1.0f);
}

float clamped_random_float(float min, float max)
{
        return min + ((max - min) * random_float());
}
