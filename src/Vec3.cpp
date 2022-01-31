#include "Vec3.h"

Vec3::Vec3(double e1, double e2, double e3)
{
    x = e1;
    y = e2;
    z = e3;
}

Vec3 Vec3::operator-() const
{
    return Vec3(-x, -y, -z);
}

void Vec3::operator+=(const Vec3 &vec)
{
    x = x + vec.x;
    y = y + vec.y;
    z = z + vec.z;
}

void Vec3::operator-=(const Vec3 &vec)
{
    *this += (-vec);
}

void Vec3::operator*=(const double t)
{
    x = x * t;
    y = y * t;
    z = z * t;
}

void Vec3::operator/=(const double t)
{
    *this *= (1 / t);
}

double Vec3::lengthSquared() const
{
    return (x * x + y * y + z * z);
}

double Vec3::length() const
{
    return sqrt(lengthSquared());
}

using Point3 = Vec3;
using Colour = Vec3;