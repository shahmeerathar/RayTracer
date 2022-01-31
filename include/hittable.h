#pragma once
#include "Commons.h"

class material;

struct hit_record
{
    point3 point;
    vec3 normal;
    shared_ptr<material> mtr_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable
{
    public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const = 0;
};