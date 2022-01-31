#include "hittable_list.h"

hittable_list::hittable_list()
{
    std::cout << "Initialised hittable_list object\n";
}

void hittable_list::add(shared_ptr<hittable> object)
{
    objects.push_back(object);
}

void hittable_list::clear()
{
    objects.clear();
}

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& record) const
{
    hit_record temp;
    bool hits_made = false;
    double closest = t_max;

    for (const auto& object : objects)
    {
        if (object->hit(r, t_min, closest, temp))
        {
            hits_made = true;
            closest = temp.t;
            record = temp;
        }
    }

    return hits_made;
}