#pragma once

#include "vec3.h"

class Ray
{
public:
    point3 origin;
    vec3 direction;

    Ray(const point3 &ori, const vec3 &dir);
    point3 at(double t) const;
};