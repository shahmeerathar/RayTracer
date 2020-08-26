#include "sphere.h"
#include "ray.h"
#include "vec3.h"
#include <cmath>

sphere::sphere(point3 cen, double r)
    {
        centre = cen;
        radius = r;
    }

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& record) const
{
    vec3 diff = r.origin - centre;
    double a = dot(r.direction, r.direction);
    double b = 2 * dot(r.direction, diff);
    double c = dot(diff, diff) - radius*radius;
    double discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}