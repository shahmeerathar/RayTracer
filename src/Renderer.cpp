//
// Created by Shahmeer Athar on 2022-01-31.
//

#include "Renderer.h"
#include "Materials.h"

Colour Renderer::colourRay(const Ray &r, const Hittable &object, int depth)
{
    HitRecord record;

    if (depth > 50)
    {
        return Colour(0.0, 0.0, 0.0);
    }

    if (object.hit(r, 0.001, infinity, record))
    {
        Ray scattered = r;
        Colour attenuation;

        if (record.mtrPtr->scatter(r, record, attenuation, scattered))
        {
            return attenuation * colourRay(scattered, object, depth + 1);
        }

        return Colour(0.0, 0.0, 0.0);
    }

    Vec3 unitDirection = unit(r.direction);
    auto t = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}

