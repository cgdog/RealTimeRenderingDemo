#include "transform.h"
#include "Utilities/helperFuncs.h"

namespace LXY {

Transform::Transform()
{

}

Transform::~Transform()
{

}

// to be optimized
Matrix4D Transform::rotate(float angle, float x, float y, float z)
{
    float radianAngle = degreeToRadian(angle);
    float c = cos(radianAngle);
    float s = sin(radianAngle);
    Matrix4D rotation;
    rotation[0] = c + (1 - c) * x * x;
    rotation[1] = (1 - c) * x * y - s * z;
    rotation[2] = (1 - c) * x * z + s * y;
    rotation[4] = (1 - c) * x * y + s * z;
    rotation[5] = c + (1 - c) * y * y;
    rotation[6] = (1 - c) * y * z - s * x;
    rotation[8] = (1 - c) * x * z - s * y;
    rotation[9] = (1 - c) * y * z + s * x;
    rotation[10] = c + (1 - c) * z * z;
    rotation[15] = 1;

    return rotation;
}

Matrix4D Transform::translate(float x, float y, float z)
{
    Matrix4D translation;
    translation(0, 0) = 1;
    translation(1, 1) = 1;
    translation(2, 2) = 1;
    translation(3, 3) = 1;
    translation[3] = x;
    translation[7] = y;
    translation[11] = z;
    return translation;
}

Matrix4D Transform::scale(float x, float y, float z)
{
    Matrix4D scaling;
    scaling[0] *= x;
    scaling[5] *= y;
    scaling[10] *= z;
    return scaling;
}

}
