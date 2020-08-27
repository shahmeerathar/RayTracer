#pragma once
#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
    public:
    point3 centre;
    double radius;
    shared_ptr<material> mtr_ptr;

    sphere(point3 cen, double r, shared_ptr<material> m);
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const override;
};