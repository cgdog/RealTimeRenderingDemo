#ifndef CAMERA_H
#define CAMERA_H

#include "Math/matrix4d.h"
#include "Math/transform.h"

namespace LXY {

class Camera
{
public:
    Camera();
    ~Camera();

    Matrix4D getPerspective(float left, float right, float top, float bottom, float far, float near);
    Matrix4D getPerspective(float verticalAngle, float aspectRatio, float near, float far);

    Matrix4D getOrtho(float left, float right, float top, float bottom, float far, float near);

    Transform& getTransform();

private:
    Transform transform;
};

}

#endif // CAMERA_H
