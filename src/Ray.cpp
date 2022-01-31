#include "Ray.h"

Ray::Ray(const Point3 &ori, const Vec3 &dir)
{
    origin = ori;
    direction = dir;
}

Point3 Ray::at(double t) const
{
    return origin + t * direction;
}