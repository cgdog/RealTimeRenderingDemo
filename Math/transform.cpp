#include "transform.h"
#include "Utilities/helperFuncs.h"

namespace LXY {

Transform::Transform() : xRot(0.0f), yRot(0.0f), zRot(0.0f)
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

void Transform::rotateX(float deltaAngle)
{
    xRot += deltaAngle;
}

void Transform::rotateY(float deltaAngle)
{
    yRot += deltaAngle;
}

void Transform::rotateZ(float deltaAngle)
{
    zRot += deltaAngle;
}

Matrix4D Transform::rotateX()
{
    float radianRot = degreeToRadian(xRot);
    float c = cos(radianRot);
    float s = sin(radianRot);
    Matrix4D rotation;
    rotation(0, 0) = 1.0f;
    rotation(1, 1) = c;
    rotation(2, 2) = c;
    rotation(1, 2) = -s;
    rotation(2, 1) = s;
    rotation(3, 3) = 1.0f;

    return rotation;
}

Matrix4D Transform::rotateY()
{
    float radianRot = degreeToRadian(yRot);
    float c = cos(radianRot);
    float s = sin(radianRot);
    Matrix4D rotation;
    rotation(0, 0) = c;
    rotation(1, 1) = 1.0f;
    rotation(2, 2) = c;
    rotation(0, 2) = s;
    rotation(2, 0) = -s;
    rotation(3, 3) = 1.0f;

    return rotation;
}

Matrix4D Transform::rotateZ()
{
    float radianRot = degreeToRadian(zRot);
    float c = cos(radianRot);
    float s = sin(radianRot);
    Matrix4D rotation;
    rotation(0, 0) = c;
    rotation(1, 1) = c;
    rotation(2, 2) = 1;
    rotation(0, 1) = -s;
    rotation(1, 0) = s;
    rotation(3, 3) = 1.0f;

    return rotation;
}

Matrix4D Transform::rotate()
{
    Matrix4D rotX = rotateX();
    Matrix4D rotY = rotateY();
    Matrix4D rotZ = rotateZ();

    return rotX * rotY * rotZ;
}

}
