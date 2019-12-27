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
    Matrix4D rotate(float angle, float x, float y, float z);
    Matrix4D translate(float x, float y, float z);
    Matrix4D scale(float x, float y, float z);

private:
    //Matrix4D rotation;
    //Matrix4D scaling;
    //Matrix4D translation;
};

}

#endif // TRANSFORM_H
