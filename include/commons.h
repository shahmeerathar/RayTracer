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

inline vec3 reflect(const vec3& v, const vec3& n)
{
    return unit(v - 2*dot(v,n)*n);
}

inline vec3 refract(const vec3& in_ray, const vec3& normal, double& index_ratio)
{
    vec3 r_perp = index_ratio * (in_ray + (dot(-unit(in_ray), unit(normal)) * normal));
    vec3 r_parr = -sqrt(fabs(1 - r_perp.length_squared())) * normal;
    return r_perp + r_parr;
}

inline double schlick(double index, double cosine)
{
    double f_0 = (index - 1) / (index + 1);
    f_0 = f_0 * f_0;
    return f_0 + ((1-f_0)*pow(1-cosine, 5));
}

inline vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}