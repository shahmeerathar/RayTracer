#include "sphere.h"
#include <cmath>
#include <iostream>
#include <algorithm>

sphere::sphere(point3 cen, double r, shared_ptr<Material> m)
{
    centre = cen;
    radius = r;
    mtr_ptr = m;
}

bool sphere::hit(const ray& r, double t_min, double t_max, HitRecord& record) const
{
    vec3 diff = r.origin - centre;
    auto a = r.direction.length_squared();
    auto half_b = dot(diff, r.direction);
    auto c = diff.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant > 0)
    {
        double root = sqrt(discriminant);
        double temp_t = (-half_b - sqrt(discriminant) ) / a;
        if (temp_t > t_min && temp_t < t_max)
        {
            record.t = temp_t;
            record.point = r.at(record.t);
            vec3 out_normal = unit((record.point - centre) / radius);
            record.setFaceNormal(r, out_normal);
            record.mtrPtr = mtr_ptr;
            return true;
        }
        temp_t = (-half_b + sqrt(discriminant) ) / a;
        if (temp_t > t_min && temp_t < t_max)
        {
            record.t = temp_t;
            record.point = r.at(record.t);
            vec3 out_normal = unit((record.point - centre) / radius);
            record.setFaceNormal(r, out_normal);
            record.mtrPtr = mtr_ptr;
            return true;
        }
    }
    return false;
}