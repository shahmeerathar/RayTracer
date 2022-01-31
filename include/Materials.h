#pragma once

#include "Hittable.h"

struct HitRecord;

class Material
{
public:
    virtual bool scatter(const Ray &inRay, const HitRecord &record, colour &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material
{
public:
    colour albedo;

    explicit Lambertian(const colour &a);
    bool scatter(const Ray &inRay, const HitRecord &record, colour &attenuation, Ray &scattered) const override;
};

class Metal : public Material
{
public:
    colour albedo;
    double fuzz;

    Metal(const colour &a, double f);
    bool scatter(const Ray &inRay, const HitRecord &record, colour &attenuation, Ray &scattered) const override;
};

class Dielectric : public Material
{
public:
    double refractiveIndex;

    explicit Dielectric(double ri);
    bool scatter(const Ray &inRay, const HitRecord &record, colour &attenuation, Ray &scattered) const override;
};