#pragma once
#include "ray.h"
#include "vec3.h"

class ray
{
    public:
    point3 origin;
    vec3 direction;

    ray(const point3& ori, const vec3& dir);
    point3 at(double t) const;
    colour colour_ray();
};