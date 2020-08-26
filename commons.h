#pragma once
#include <cmath>
#include <cstdlib>
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