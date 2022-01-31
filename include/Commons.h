#pragma once

#include <cmath>
#include <cstdlib>
#include <stdlib.h>
#include <limits>
#include <memory>
#include "vec3.h"
#include "Ray.h"

using namespace std;

const double infinity = numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degToRad(double degrees)
{
    return pi * degrees / 180.0;
}

inline double radToDeg(double rad)
{
    return 180.0 * rad / pi;
}

inline double randomDouble()
{
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max)
{
    return min + (randomDouble() * (max - min));
}

inline double clamp(double x, double min, double max)
{
    if (x > max)
    {
        return max;
    }

    if (x < min)
    {
        return min;
    }

    return x;
}

inline vec3 randomUnitVector()
{
    double a = randomDouble(0, 2 * pi);
    double z = randomDouble(-1, 1);
    double r = sqrt(1 - z * z);
    return vec3(r * cos(a), r * sin(a), z);
}

inline vec3 reflect(const vec3 &v, const vec3 &n)
{
    return unit(v - 2 * dot(v, n) * n);
}

inline vec3 refract(const vec3 &inRay, const vec3 &normal, double &indexRatio)
{
    vec3 rPerp = indexRatio * (inRay + (dot(-unit(inRay), unit(normal)) * normal));
    vec3 rParr = -sqrt(fabs(1 - rPerp.length_squared())) * normal;
    return rPerp + rParr;
}

inline double schlick(double index, double cosine)
{
    double f0 = (index - 1) / (index + 1);
    f0 = f0 * f0;
    return f0 + ((1 - f0) * pow(1 - cosine, 5));
}

inline vec3 randomInUnitDisk()
{
    while (true)
    {
        auto p = vec3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}