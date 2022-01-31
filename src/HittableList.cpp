#include "HittableList.h"

HittableList::HittableList()
{
    std::cout << "Initialised HittableList object\n";
}

void HittableList::add(shared_ptr<Hittable> object)
{
    objects.push_back(object);
}

void HittableList::clear()
{
    objects.clear();
}

bool HittableList::hit(const ray& r, double tMin, double tMax, HitRecord& record) const
{
    HitRecord temp;
    bool hits_made = false;
    double closest = tMax;

    for (const auto& object : objects)
    {
        if (object->hit(r, tMin, closest, temp))
        {
            hits_made = true;
            closest = temp.t;
            record = temp;
        }
    }

    return hits_made;
}