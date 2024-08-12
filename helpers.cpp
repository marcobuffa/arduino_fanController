#include <stdio.h>
#include <math.h>
#include "helpers.h"

//dewPoint calculation routine
float dewPoint(float h, float t) {
    return (t - (14.55 + 0.114 * t) * (1 - (0.01 * h)) - pow(((2.5 + 0.007 * t) * (1 - (0.01 * h))),3) - (15.9 + 0.117 * t) * pow((1 - (0.01 * h)), 14));
}
