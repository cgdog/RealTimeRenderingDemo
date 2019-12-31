#ifndef VECTOR3_H
#define VECTOR3_H

namespace LXY {


class Vector3
{
public:
    Vector3();
    Vector3(float _x, float _y, float _z);
    Vector3(const Vector3& v);
    virtual ~Vector3();

    virtual void operator=(const Vector3& v);
    virtual Vector3 operator*(float scalar);
    virtual Vector3 operator/(float scalar);
    virtual Vector3 operator+(float scalar);
    virtual Vector3 operator-(float scalar);
    virtual Vector3 operator+(const Vector3& v);
    virtual Vector3 operator-(const Vector3& v);
    virtual float& operator[](int index);
    virtual float operator[](int index) const;
    virtual void normalize();
    virtual float length();

    float& X();
    float& Y();
    float& Z();

    float X() const;
    float Y() const;
    float Z() const;

    Vector3 cross(const Vector3& v);
    Vector3 cross(const Vector3& v) const;
    float dot(const Vector3& v);

protected:
    float x, y, z;

};

}

#endif // VECTOR3_H
