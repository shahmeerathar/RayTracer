#pragma once

#include "Commons.h"

class Material;

struct HitRecord
{
    Point3 point;
    Vec3 normal;
    shared_ptr<Material> mtrPtr;
    double t;
    bool frontFace;

    inline void setFaceNormal(const Ray &r, const Vec3 &outwardNormal)
    {
        frontFace = dot(r.direction, outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
public:
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const = 0;
};