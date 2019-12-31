#include "vector3.h"
#include "Utilities/helperFuncs.h"
#include <cassert>

namespace LXY {


Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3::Vector3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Vector3::Vector3(const Vector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector3::~Vector3()
{}

void Vector3::operator=(const Vector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector3 Vector3::operator*(float scalar)
{
    Vector3 v;
    v.x *= scalar;
    v.y *= scalar;
    v.z *= scalar;
    return v;
}

Vector3 Vector3::operator/(float scalar)
{
    assert (!isEqualZeroF(scalar));
    Vector3 v;
    float reverse_scalar = 1.0f / scalar;
    v.x *= reverse_scalar;
    v.y *= reverse_scalar;
    v.z *= reverse_scalar;
    return v;
}

Vector3 Vector3::operator+(float scalar)
{
    Vector3 v;
    v.x += scalar;
    v.y += scalar;
    v.z += scalar;
    return v;
}

Vector3 Vector3::operator-(float scalar)
{
    Vector3 v;
    v.x -= scalar;
    v.y -= scalar;
    v.z -= scalar;
    return v;
}

float& Vector3::operator[](int index)
{
    assert(index >= 0 && index < 3);
    switch (index) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    }
    return x;
}

float Vector3::operator[](int index) const
{
    assert(index >= 0 && index < 3);
    switch (index) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    }
    return x;
}

float& Vector3::X()
{
    return x;
}

float& Vector3::Y()
{
    return y;
}

float& Vector3::Z()
{
    return z;
}

float Vector3::X() const
{
    return x;
}

float Vector3::Y() const
{
    return y;
}

float Vector3::Z() const
{
    return z;
}


Vector3 Vector3::cross(const Vector3& v)
{
    Vector3 res;
    res.x = y * v.z - z * v.y;
    res.y = z * v.x - x * v.z;
    res.z = x * v.y - y * v.x;
    return res;
}

Vector3 Vector3::cross(const Vector3& v) const
{
    Vector3 res;
    res.x = y * v.z - z * v.y;
    res.y = z * v.x - x * v.z;
    res.z = x * v.y - y * v.x;
    return res;
}

float Vector3::dot(const Vector3& v)
{
    float res = 0.0f;
    res += x * v.x;
    res += y * v.y;
    res += z * v.z;
    return res;
}

void Vector3::normalize()
{
    operator/(length());
}

float Vector3::length()
{
    return sqrtf(x * x + y * y + z * z);
}

Vector3 Vector3::operator+(const Vector3& v)
{
    Vector3 res;
    res.x = x + v.x;
    res.y = y + v.y;
    res.z = z + v.z;
    return res;
}

Vector3 Vector3::operator-(const Vector3& v)
{
    Vector3 res;
    res.x = x - v.x;
    res.y = y - v.y;
    res.z = z - v.z;
    return res;
}

}
