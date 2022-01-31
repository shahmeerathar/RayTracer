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

bool HittableList::hit(const Ray &r, double tMin, double tMax, HitRecord &record) const
{
    HitRecord temp;
    bool hitsMade = false;
    double closest = tMax;

    for (const auto &object: objects)
    {
        if (object->hit(r, tMin, closest, temp))
        {
            hitsMade = true;
            closest = temp.t;
            record = temp;
        }
    }

    return hitsMade;
}