#include "Ray.h"

Ray::Ray(const point3 &ori, const vec3 &dir)
{
    origin = ori;
    direction = dir;
}

point3 Ray::at(double t) const
{
    return origin + t * direction;
}