#pragma once
#include "Hittable.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class hittable_list : public Hittable
{
    public:
    vector<shared_ptr<Hittable>> objects;

    hittable_list();
    void add(shared_ptr<Hittable> object);
    void clear();
    virtual bool hit(const ray& r, double t_min, double t_max, HitRecord& record) const override;
};