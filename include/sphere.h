#pragma once
#include "Hittable.h"
#include "vec3.h"

class sphere : public Hittable
{
    public:
    point3 centre;
    double radius;
    shared_ptr<Material> mtr_ptr;

    sphere(point3 cen, double r, shared_ptr<Material> m);
    virtual bool hit(const ray& r, double t_min, double t_max, HitRecord& record) const override;
};