#ifndef LIGHT_H
#define LIGHT_H

#include "Math/vector4.h"

namespace LXY {


class Light
{
public:
    Light();
    Light(const Vector4& pos, const Vector4& _color);
    ~Light();

    Vector4 getPosition();
    Vector4 getColor();
    void setPosition(const Vector4& pos);
    void setColor(const Vector4& _color);
protected:
    Vector4 position;
    Vector4 color;
};

}
#endif // LIGHT_H
