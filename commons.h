#pragma once
#include <cmath>
#include <cstdlib>
#include <stdlib.h>
#include <limits>
#include <memory>
#include "vec3.h"
#include "ray.h"

using namespace std;

const double infinity = numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double deg_to_rad(double degrees)
{
    return pi * degrees/180.0;
}

inline double rad_to_deg(double rad)
{
    return 180.0 * rad/pi;
}

inline double random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
    return min + (random_double() * (max - min));
}

inline double clamp(double x, double min, double max)
{
    if (x > max)
    {
        return max;
    }
    if (x < min)
    {
        return min;
    }
    return x;
}

inline vec3 random_unit_vector()
{
    double a = random_double(0, 2*pi);
    double z = random_double(-1, 1);
    double r = sqrt(1 - z*z);
    return vec3(r*cos(a), r*sin(a), z);
}