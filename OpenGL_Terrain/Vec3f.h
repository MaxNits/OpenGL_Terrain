#pragma once

#include <iostream>

class Vec3f
{
public:
    Vec3f();

    Vec3f(float x_, float y_, float z_);

    Vec3f(const Vec3f& vector);

    ~Vec3f();

    void operator=(const Vec3f& rhs);

    Vec3f operator+(const Vec3f& rhs);

    void operator+=(const Vec3f& rhs);

    Vec3f operator-(const Vec3f& rhs);

    Vec3f operator*(float factor);

    Vec3f cross(const Vec3f& other);

    float magnitude();

    Vec3f normilize();

    friend std::ostream& operator<<(std::ostream& os, Vec3f& vec);

    float x;
    float y;
    float z;
};
