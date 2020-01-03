#ifndef CAMERA_H
#define CAMERA_H

#include "Math/matrix4d.h"
#include "Math/transform.h"
#include "Math/vector3.h"

namespace LXY {
enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera();
    ~Camera();

    Matrix4D lookAt(const Vector3& pos, const Vector3& target=Vector3(0.0f, 0.0f, 0.0f), const Vector3& worldUp=Vector3(0.0, 1.0f, 0.0f));
    // test keyboard input
    Matrix4D lookAt();
    Matrix4D getPerspective(float left, float right, float top, float bottom, float far, float near);
    Matrix4D getPerspective(float verticalAngle, float aspectRatio, float near, float far);

    Matrix4D getOrtho(float left, float right, float top, float bottom, float far, float near);

    Transform& getTransform();

    void processKeyboard(Direction dir, int deltaTime = 1);

private:
    Transform transform;

    Vector3 cameraPos;
    Vector3 cameraTarget;
    Vector3 cameraUp;
    Vector3 cameraWorldUP;
    Vector3 cameraDirection;
    Vector3 cameraRight;
};

}

#endif // CAMERA_H
