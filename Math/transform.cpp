#include "transform.h"

namespace LXY {

Transform::Transform()
{

}

Transform::~Transform()
{

}

// to be optimized
Matrix4D& Transform::rotate(float angle, float x, float y, float z)
{
    float c = cos(angle);
    float s = sin(angle);
    rotation[0] = c + (1 - c) * x * x;
    rotation[1] = (1 - c) * x * y - s * z;
    rotation[2] = (1 - c) * x * z + s * y;
    rotation[4] = (1 - c) * x * y + s * z;
    rotation[5] = c + (1 - c) * y * y;
    rotation[6] = (1 - c) * y * z - s * x;
    rotation[8] = (1 - c) * x * z - s * y;
    rotation[9] = (1 - c) * y * z + s * x;
    rotation[10] = c + (1 - c) * z * z;
    return rotation;
}

Matrix4D& Transform::translate(float x, float y, float z)
{
    translation[3] = x;
    translation[7] = y;
    translation[11] = z;
    return translation;
}

Matrix4D& Transform::scale(float x, float y, float z)
{
    scaling[0] *= x;
    scaling[5] *= y;
    scaling[10] *= z;
    return scaling;
}

}
