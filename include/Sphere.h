#pragma once

#include "Hittable.h"
#include "vec3.h"

class Sphere : public Hittable
{
public:
    point3 centre;
    double radius;
    shared_ptr<Material> mtrPtr;

    Sphere(point3 cen, double r, shared_ptr<Material> m);
    bool hit(const Ray &r, double tMin, double tMax, HitRecord &record) const override;
};