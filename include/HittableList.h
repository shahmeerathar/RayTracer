#pragma once

#include "Hittable.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class HittableList : public Hittable
{
public:
    vector<shared_ptr<Hittable>> objects;

    HittableList();
    void add(shared_ptr<Hittable> object);
    void clear();
    bool hit(const ray &r, double tMin, double tMax, HitRecord &record) const override;
};