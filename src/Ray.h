#pragma once

#include "Vec3.h"

class Ray
{
public:
    Point3 origin;
    Vec3 direction;

    Ray(const Point3 &ori, const Vec3 &dir);
    Point3 at(double t) const;
};