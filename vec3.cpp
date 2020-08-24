#include "vec3.h"

vec3::vec3(double e1, double e2, double e3)
{
    x = e1;
    y = e2;
    z = e3;
}

vec3 vec3::operator-() const
{
    return vec3(-x, -y, -z);
}

void vec3::operator+=(const vec3 &vec)
{
    x = x + vec.x;
    y = y + vec.y;
    z = z + vec.z;
}

void vec3::operator-=(const vec3 &vec)
{
    *this += (-vec);
}

void vec3::operator*=(const double t)
{
    x = x * t;
    y = y * t;
    z = z * t;
}

void vec3::operator/=(const double t)
{
    *this *= (1 / t);
}

double vec3::length_squared() const
{
    return (x * x + y * y + z * z);
}

double vec3::length() const
{
    return sqrt(length_squared());
}

using point3 = vec3;
using colour = vec3;