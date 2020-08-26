#pragma once
#include "hittable.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class hittable_list : public hittable
{
    public:
    vector<shared_ptr<hittable>> objects;

    hittable_list();
    void add(shared_ptr<hittable> object);
    void clear();
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const override;
};