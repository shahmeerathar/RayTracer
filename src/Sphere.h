#pragma once

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable
{
public:
    Point3 centre;
    double radius;
    shared_ptr<Material> mtrPtr;

    Sphere(Point3 cen, double r, shared_ptr<Material> m);
    bool hit(const Ray &r, double tMin, double tMax, HitRecord &record) const override;
};