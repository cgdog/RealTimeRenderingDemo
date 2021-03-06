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
    Matrix4D getPerspective(float aspectRatio, float near, float far);

    Matrix4D getOrtho(float left, float right, float top, float bottom, float far, float near);

    Transform& getTransform();

    void processKeyboard(Direction dir, int deltaTime = 1);
    void updateMouseLeftButtonDown(bool isDown, float x, float y);
    void processMouseMove(float x, float y, bool isConstrainPitch = true);
    void processMouseScroll(float yOffset);

    void processALTKey(bool altFlag);

    void setPos(const Vector3& pos);
    void setWorldUp(const Vector3& worldup);
    void setCameraDirection(const Vector3& _cameraDirection);
    void setYaw(float _yaw);
    void setPitch(float _pitch);

    Vector3 getPos();
    Vector3 getWorldUp();
    Vector3 getCameraDirection();
    float getYaw();
    float getPitch();

private:
    void updateCameraDirection();

private:
    Transform transform;

    Vector3 cameraPos;
    Vector3 cameraTarget;
    Vector3 cameraUp;
    Vector3 cameraWorldUP;
    Vector3 cameraDirection;
    Vector3 cameraRight;

    // Default camera values
    const float YAW         = -90.0f;
    const float PITCH       =  0.0f;
    const float SPEED       =  1.0f;
    const float SENSITIVITY =  0.1f;
    const float ZOOM        =  60.0f;
    const float ZOOMSENSITIVITY = 0.01f;

    const float MIN_ZOOM = 1.0f;
    const float MAX_ZOOM = 70.0f;

    float yaw;
    float pitch;

    float lastX;
    float lastY;
    float mouseSensitivity;
    float zoomSensitivity;

    float zoom;

    bool isLeftMouseButtonDown;
    bool isAltKeyDown;

    float cameraSpeed;
};

}

#endif // CAMERA_H
