#include "sphere.h"
#include <cmath>
#include <iostream>
#include <algorithm>

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

    if (discriminant > 0)
    {
        double root = sqrt(discriminant);
        double temp_t = ((-1 * b) + root) / 2*a;
        if (temp_t > t_min && temp_t < t_max)
        {
            record.t = temp_t;
            record.point = r.at(record.t);
            vec3 out_normal = (record.point - centre) / radius;
            record.set_face_normal(r, out_normal);
            return true;
        }
        temp_t = ((-1 * b) - root) / 2*a;
        if (temp_t > t_min && temp_t < t_max)
        {
            record.t = temp_t;
            record.point = r.at(record.t);
            vec3 out_normal = (record.point - centre) / radius;
            record.set_face_normal(r, out_normal);
            return true;
        }
    }
    return false;
}