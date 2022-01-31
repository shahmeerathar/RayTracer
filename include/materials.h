#pragma once
#include "Hittable.h"

struct HitRecord;

class Material
{
    public:
    virtual bool scatter(const ray& in_ray, const HitRecord& record, colour& attenuation, ray& scattered) const = 0;
};

class Lambertian : public Material
{
    public:
    colour albedo;
    Lambertian(const colour& a) : albedo(a) {}
    virtual bool scatter(const ray& in_ray, const HitRecord& record, colour& attenuation, ray& scattered) const override;
};

class metal : public Material
{
    public:
    colour albedo;
    double fuzz;
    metal(const colour& a, double f) : albedo(a), fuzz(f) {}
    virtual bool scatter(const ray& in_ray, const HitRecord& record, colour& attenuation, ray& scattered) const override;
};

class dielectric : public Material
{
    public:
    double refractive_index;
    dielectric(double ri);
    virtual bool scatter(const ray& in_ray, const HitRecord& record, colour& attenuation, ray& scattered) const override;
};