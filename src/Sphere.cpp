#include "Sphere.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <utility>

Sphere::Sphere(point3 cen, double r, shared_ptr<Material> m)
{
    centre = cen;
    radius = r;
    mtrPtr = std::move(m);
}

bool Sphere::hit(const Ray &r, double tMin, double tMax, HitRecord &record) const
{
    vec3 diff = r.origin - centre;
    auto a = r.direction.length_squared();
    auto halfB = dot(diff, r.direction);
    auto c = diff.length_squared() - radius * radius;
    auto discriminant = halfB * halfB - a * c;

    if (discriminant > 0)
    {
        double root = sqrt(discriminant);
        double tempT = (-halfB - sqrt(discriminant)) / a;
        if (tempT > tMin && tempT < tMax)
        {
            record.t = tempT;
            record.point = r.at(record.t);
            vec3 outNormal = unit((record.point - centre) / radius);
            record.setFaceNormal(r, outNormal);
            record.mtrPtr = mtrPtr;

            return true;
        }
        tempT = (-halfB + sqrt(discriminant)) / a;
        if (tempT > tMin && tempT < tMax)
        {
            record.t = tempT;
            record.point = r.at(record.t);
            vec3 outNormal = unit((record.point - centre) / radius);
            record.setFaceNormal(r, outNormal);
            record.mtrPtr = mtrPtr;

            return true;
        }
    }

    return false;
}