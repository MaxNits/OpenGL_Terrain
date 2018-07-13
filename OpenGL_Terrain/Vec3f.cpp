#include "Vec3f.h"
#include "math.h"

Vec3f::Vec3f()
    : x(0)
    , y(0)
    , z(0)
{
}

Vec3f::Vec3f(float x_, float y_, float z_)
    : x(x_)
    , y(y_)
    , z(z_)
{
}

Vec3f::Vec3f(const Vec3f& vector)
    : x(vector.x)
    , y(vector.y)
    , z(vector.z)
{
}

Vec3f::~Vec3f()
{
}

Vec3f Vec3f::operator+(const Vec3f& rhs)
{
    return Vec3f(x + rhs.x, y + rhs.y, z + rhs.z);
}

void Vec3f::operator+=(const Vec3f& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
}

Vec3f Vec3f::operator-(const Vec3f& rhs)
{
    return Vec3f(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vec3f Vec3f::operator*(float factor)
{
    return Vec3f(x * factor, y * factor, z * factor);
}

void Vec3f::operator=(const Vec3f& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
}

std::ostream& operator<<(std::ostream& os, Vec3f& vec)
{
    os << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')';
    return os;
}

Vec3f Vec3f::cross(const Vec3f& other)
{
    return Vec3f((y * other.z) - (z * other.y),
                 (x * other.z) - (z * other.x),
                 (x * other.y) - (y * other.z));
}

float Vec3f::magnitude()
{
    return pow(x * x + y * y + z * z, 0.5);
}

Vec3f Vec3f::normilize()
{
    float length = pow(x * x + y * y + z * z, 0.5);
    return Vec3f(x / length, y / length, z / length);
}
