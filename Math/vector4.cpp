#include "vector4.h"
#include "Utilities/helperFuncs.h"
#include <cassert>

namespace LXY {


Vector4::Vector4()
{
    memset(data, 0, sizeof(float)*4);
}

Vector4::Vector4(float _x, float _y, float _z, float _w)
{
    data[0] = _x;
    data[1] = _y;
    data[2] = _z;
    data[3] = _w;
}

Vector4::Vector4(const Vector3& v, float w)
{
    data[0] = v.X();
    data[1] = v.Y();
    data[2] = v.Z();
    data[3] = w;
}

Vector4::Vector4(const Vector4& v)
{
    memcpy(data, v.data, sizeof(float)*4);
}

Vector4::~Vector4()
{}

void Vector4::operator=(const Vector4& v)
{
    if (data == v.data)
    {
        logErr() << "Error: could not apply operator= to the same operand.\n";
        return;
    }
    memcpy(data, v.data, sizeof(float)*4);
}

void Vector4::operator=(const Vector3& v)
{
    data[0] = v.X();
    data[1] = v.Y();
    data[2] = v.Z();
    data[3] = 0.0f;
}

Vector4 Vector4::operator*(float scalar)
{
    Vector4 v(*this);
    for (int i = 0; i < 4; ++i)
    {
        v.data[i] *= scalar;
    }
    return v;
}

Vector4 Vector4::operator/(float scalar)
{
    assert (!isEqualZeroF(scalar));
    Vector4 v(*this);
    float reverse_scalar = 1.0f / scalar;
    for (int i = 0; i < 4; ++i)
    {
        v.data[i] *= reverse_scalar;
    }
    return v;
}

Vector4 Vector4::operator+(float scalar)
{
    Vector4 v(*this);
    for (int i = 0; i < 4; ++i)
    {
        v.data[i] += scalar;
    }
    return v;
}

Vector4 Vector4::operator-(float scalar)
{
    Vector4 v(*this);
    for (int i = 0; i < 4; ++i)
    {
        v.data[i] -= scalar;
    }
    return v;
}

float& Vector4::operator[](int index)
{
    assert(index >= 0 && index < 4);
    return data[index];
}

float Vector4::operator[](int index) const
{
    assert(index >= 0 && index < 4);
    return data[index];
}

float& Vector4::X()
{
    return data[0];
}

float& Vector4::Y()
{
    return data[1];
}

float& Vector4::Z()
{
    return data[2];
}

float& Vector4::W()
{
    return data[3];
}

float Vector4::X() const
{
    return data[0];
}

float Vector4::Y() const
{
    return data[1];
}

float Vector4::Z() const
{
    return data[2];
}

float Vector4::W() const
{
    return data[3];
}

float Vector4::dot(const Vector4& v)
{
    float res = 0.0f;
    for (int i = 0; i < 4; ++i)
    {
        res += data[i] * v.data[i];
    }
    return res;
}

void Vector4::normalize()
{
    operator/(length());
}

Vector4 Vector4::normalized()
{
    Vector4 res(*this);
    res.normalize();
    return res;
}

float Vector4::length()
{
    float len2 = 0.0f;
    for (int i = 0; i < 4; ++i)
    {
        len2 += data[i] * data[i];
    }
    return sqrtf(len2);
}

Vector4 Vector4::operator+(const Vector4& v)
{
    Vector4 res;
    for (int i = 0; i < 4; ++i)
    {
        res.data[i] = data[i] + v.data[i];
    }
    return res;
}

Vector4 Vector4::operator-(const Vector4& v)
{
    Vector4 res;
    for (int i = 0; i < 4; ++i)
    {
        res.data[i] = data[i] - v.data[i];
    }
    return res;
}

void Vector4::operator+=(const Vector4& v)
{
    for (int i = 0; i < 4; ++i)
    {
        data[i] += v.data[i];
    }
}

void Vector4::operator-=(const Vector4& v)
{
    for (int i = 0; i < 4; ++i)
    {
        data[i] -= v.data[i];
    }
}

}
