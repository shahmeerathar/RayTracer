#pragma once
#include "hittable.h"

struct hit_record;

class material
{
    public:
    virtual bool scatter(const ray& in_ray, const hit_record& record, colour& attenuation, ray& scattered) const = 0;
};

class Lambertian : public material
{
    public:
    colour albedo;
    Lambertian(const colour& a) : albedo(a) {}
    virtual bool scatter(const ray& in_ray, const hit_record& record, colour& attenuation, ray& scattered) const override;
};

class metal : public material
{
    public:
    colour albedo;
    metal(const colour& a) : albedo(a) {}
    virtual bool scatter(const ray& in_ray, const hit_record& record, colour& attenuation, ray& scattered) const override;
};