#include "light.h"

namespace LXY {


Light::Light() : position(-1.25247, 1.86265e-09f, -2.10285f, 1.0f), color(1.0f, 0.3f, 0.2f, 1.0f)
{
}

Light::Light(const Vector4& pos, const Vector4& _color) : position(pos), color(_color)
{
}

Light::~Light()
{
}

Vector4 Light::getPosition()
{
    return  position;
}

Vector4 Light::getColor()
{
    return  color;
}

void Light::setPosition(const Vector4& pos)
{
    position = pos;
}

void Light::setColor(const Vector4& _color)
{
    color = _color;
}

}
