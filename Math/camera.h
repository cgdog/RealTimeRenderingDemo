#ifndef CAMERA_H
#define CAMERA_H

#include "Math/matrix4d.h"
#include "Math/transform.h"
#include "Math/vector3.h"

namespace LXY {

class Camera
{
public:
    Camera();
    ~Camera();

    Matrix4D lookAt(const Vector3& pos, const Vector3& target, const Vector3& worldUp);

    Matrix4D getPerspective(float left, float right, float top, float bottom, float far, float near);
    Matrix4D getPerspective(float verticalAngle, float aspectRatio, float near, float far);

    Matrix4D getOrtho(float left, float right, float top, float bottom, float far, float near);

    Transform& getTransform();

private:
    Transform transform;

    Vector3 cameraPos;
    Vector3 cameraTarget;
    Vector3 cameraUp;
    Vector3 cameraDirection;
    Vector3 cameraRight;
};

}

#endif // CAMERA_H
