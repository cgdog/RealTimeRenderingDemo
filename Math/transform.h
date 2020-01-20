#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Math/matrix4d.h"

namespace LXY {

class Transform
{
public:
    Transform();
    ~Transform();

    // https://zhuanlan.zhihu.com/p/78987582
    // https://zhuanlan.zhihu.com/p/96717729
    Matrix4D rotate(float angle, float x, float y, float z);
    void rotateX(float deltaAngle);
    void rotateY(float deltaAngle);
    void rotateZ(float deltaAngle);

    Matrix4D rotateX();
    Matrix4D rotateY();
    Matrix4D rotateZ();
    Matrix4D rotate();

    Matrix4D translate(float x, float y, float z);
    Matrix4D scale(float x, float y, float z);

private:

    float xRot;
    float yRot;
    float zRot;

    //Matrix4D rotation;
    //Matrix4D scaling;
    //Matrix4D translation;
};

}

#endif // TRANSFORM_H
