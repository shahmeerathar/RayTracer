#pragma once
#include "vec3.h"
#include "hittable.h"
#include "sphere.h"

class ray
{
    public:
    point3 origin;
    vec3 direction;

    ray(const point3& ori, const vec3& dir);
    point3 at(double t) const;
    colour colour_ray(const hittable& object);
};