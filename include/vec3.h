#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class vec3
{
    public:
    double x, y, z;

    vec3(double e1 = 0.0, double e2 = 0.0, double e3 = 0.0);
    vec3 operator-() const;
    void operator+=(const vec3 &vec);
    void operator-=(const vec3 &vec);
    void operator*=(const double t);
    void operator/=(const double t);
    double length_squared() const;
    double length() const;
};

using point3 = vec3;
using colour = vec3;


//Vector3 utility functions:
inline ostream& operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z << '\n';
}

inline vec3 operator+(const vec3 &a, const vec3 &b)
{
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline vec3 operator-(const vec3 &a, const vec3 &b)
{
    return a + (-b);
}

inline vec3 operator*(const vec3 &a, const vec3 &b)
{
    return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline vec3 operator*(const vec3 &a, double t)
{
    return vec3(a.x * t, a.y * t, a.z * t);
}

inline vec3 operator*(double t, const vec3 &a)
{
    return a*t;
}

inline vec3 operator/(const vec3 &a, double t)
{
    return a*(1/t);
}

inline double dot(const vec3 &a, const vec3 &b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

inline vec3 cross(const vec3 &a, const vec3 &b)
{
    return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y-a.y*b.x);
}

inline vec3 unit(const vec3 &a)
{
    return a / a.length();
}