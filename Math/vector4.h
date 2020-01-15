#ifndef VECTOR4_H
#define VECTOR4_H
#include "vector3.h"

namespace LXY {

class Vector4
{
public:
    Vector4();
    Vector4(float _x, float _y, float _z, float _w);
    Vector4(const Vector4& v);
    Vector4(const Vector3& v, float w = 0.0f);
    virtual ~Vector4();

    virtual void operator=(const Vector3& v);
    virtual void operator=(const Vector4& v);
    Vector4 operator*(float scalar);
    virtual Vector4 operator/(float scalar);
    virtual Vector4 operator+(float scalar);
    virtual Vector4 operator-(float scalar);
    virtual Vector4 operator+(const Vector4& v);
    virtual Vector4 operator-(const Vector4& v);

    virtual void operator+=(const Vector4& v);
    virtual void operator-=(const Vector4& v);

    virtual float& operator[](int index);
    virtual float operator[](int index) const;
    virtual void normalize();
    Vector4 normalized();
    virtual float length();

    float& X();
    float& Y();
    float& Z();
    float& W();

    float X() const;
    float Y() const;
    float Z() const;
    float W() const;

    float dot(const Vector4& v);


protected:
    float data[4];
};

}

#endif // VECTOR4_H
