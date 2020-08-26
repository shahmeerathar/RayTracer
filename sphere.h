#pragma once
#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
    public:
    point3 centre;
    double radius;

    sphere(point3 cen, double r);
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const override;
};