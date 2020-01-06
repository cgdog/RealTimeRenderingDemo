#include "camera.h"
#include "Utilities/helperFuncs.h"
namespace LXY {


Camera::Camera() : cameraPos(Vector3(0, 0, -3)), cameraTarget(Vector3(0.0f, 0.0f, 0.0f)),
    cameraWorldUP(Vector3(0.0, 1.0f, 0.0f)), cameraDirection(Vector3(0.0f, 0.0f, -1.0f)),
    yaw(YAW), pitch(PITCH), isLeftMouseButtonDown(false), mouseSensitivity(SENSITIVITY),
    zoom(ZOOM), zoomSensitivity(ZOOMSENSITIVITY), cameraSpeed(0.1f)
{

}

Camera::~Camera()
{

}

Matrix4D Camera::lookAt(const Vector3& pos, const Vector3& target, const Vector3& worldUp)
{
    Matrix4D viewMatrix;

    cameraPos = pos;
    cameraTarget = target;
    cameraDirection = cameraPos - cameraTarget;
    cameraDirection.normalize();

    cameraWorldUP = worldUp;
    cameraRight = cameraWorldUP.cross(cameraDirection);
    cameraRight.normalize();
    cameraUp = cameraDirection.cross(cameraRight);

    viewMatrix(0, 0) = cameraRight.X();
    viewMatrix(0, 1) = cameraRight.Y();
    viewMatrix(0, 2) = cameraRight.Z();
    viewMatrix(0, 3) = -cameraRight.X() * cameraPos.X() - cameraRight.Y() * cameraPos.Y() - cameraRight.Z() * cameraPos.Z();

    viewMatrix(1, 0) = cameraUp.X();
    viewMatrix(1, 1) = cameraUp.Y();
    viewMatrix(1, 2) = cameraUp.Z();
    viewMatrix(1, 3) = -cameraUp.X() * cameraPos.X() - cameraUp.Y() * cameraPos.Y() - cameraUp.Z() * cameraPos.Z();

    viewMatrix(2, 0) = cameraDirection.X();
    viewMatrix(2, 1) = cameraDirection.Y();
    viewMatrix(2, 2) = cameraDirection.Z();
    viewMatrix(2, 3) = -cameraDirection.X() * cameraPos.X() - cameraDirection.Y() * cameraPos.Y() - cameraDirection.Z() * cameraPos.Z();

    viewMatrix(3, 0) = 0;
    viewMatrix(3, 1) = 0;
    viewMatrix(3, 2) = 0;
    viewMatrix(3, 3) = 1;

    return viewMatrix;
}

Matrix4D Camera::lookAt()
{
    Matrix4D viewMatrix;

    cameraRight = cameraWorldUP.cross(cameraDirection);
    cameraRight.normalize();
    cameraUp = cameraDirection.cross(cameraRight);

    viewMatrix(0, 0) = cameraRight.X();
    viewMatrix(0, 1) = cameraRight.Y();
    viewMatrix(0, 2) = cameraRight.Z();
    viewMatrix(0, 3) = -cameraRight.X() * cameraPos.X() - cameraRight.Y() * cameraPos.Y() - cameraRight.Z() * cameraPos.Z();

    viewMatrix(1, 0) = cameraUp.X();
    viewMatrix(1, 1) = cameraUp.Y();
    viewMatrix(1, 2) = cameraUp.Z();
    viewMatrix(1, 3) = -cameraUp.X() * cameraPos.X() - cameraUp.Y() * cameraPos.Y() - cameraUp.Z() * cameraPos.Z();

    viewMatrix(2, 0) = cameraDirection.X();
    viewMatrix(2, 1) = cameraDirection.Y();
    viewMatrix(2, 2) = cameraDirection.Z();
    viewMatrix(2, 3) = -cameraDirection.X() * cameraPos.X() - cameraDirection.Y() * cameraPos.Y() - cameraDirection.Z() * cameraPos.Z();

    viewMatrix(3, 0) = 0;
    viewMatrix(3, 1) = 0;
    viewMatrix(3, 2) = 0;
    viewMatrix(3, 3) = 1;

    return viewMatrix;
}

Matrix4D Camera::getPerspective(float left, float right, float top, float bottom, float far, float near)
{
    Matrix4D perspectiveTransform;
    perspectiveTransform(0, 0) = (2 * near) / (right - left);
    perspectiveTransform(0, 2) = (right + left) / (right - left);
    perspectiveTransform(1, 1) = (2 * near) / (top - bottom);
    perspectiveTransform(1, 2) = (top + bottom) / (top - bottom);
    perspectiveTransform(2, 2) = -(far + near) / (far - near);
    perspectiveTransform(2, 3) = -(2 * far * near) / (far - near);
    perspectiveTransform(3, 2) = -1;
    perspectiveTransform(3, 3) = 0;
    return perspectiveTransform;
}

// aspectRatio = width / height;
Matrix4D Camera::getPerspective(float verticalAngle, float aspectRatio, float near, float far)
{
    verticalAngle = degreeToRadian(verticalAngle / 2.0f);
    float c = 1.0f / tan(verticalAngle);
    Matrix4D perspectiveTransform;
    perspectiveTransform(0, 0) = c / aspectRatio;
    perspectiveTransform(1, 1) = c;
    perspectiveTransform(2, 2) = -(far + near) / (far - near);
    perspectiveTransform(2, 3) = -(2 * far * near) / (far - near);
    perspectiveTransform(3, 2) = -1;
    perspectiveTransform(3, 3) = 0;
    return perspectiveTransform;
}

Matrix4D Camera::getPerspective(float aspectRatio, float near, float far)
{
    return getPerspective(zoom, aspectRatio, near, far);
}

Matrix4D Camera::getOrtho(float left, float right, float top, float bottom, float far, float near)
{
    Matrix4D orthoTransform;
    orthoTransform(0, 0) = 2/(right - left);
    orthoTransform(0, 3) = -(right + left) / (right - left);
    orthoTransform(1, 1) = 2/(top - bottom);
    orthoTransform(1, 3) = -(top + bottom) / (top - bottom);
    orthoTransform(2, 2) = 2 / (far - near);
    orthoTransform(2, 3) = -(far + near) / (far - near);
    orthoTransform(3, 3) = 1;

    return orthoTransform;
}

Transform& Camera::getTransform()
{
    return transform;
}

void Camera::processKeyboard(Direction dir, int deltaTime)
{
    Q_UNUSED(deltaTime)
    //cameraSpeed *= deltaTime + 0.1f;
    //log() << "deltaTime=" << deltaTime << endl;
    if (dir == Direction::UP)
    {
        cameraPos += cameraDirection * cameraSpeed;
    }
    else if (dir == Direction::DOWN)
    {
        cameraPos -= cameraDirection * cameraSpeed;
    }
    else if (dir == Direction::LEFT)
    {
        cameraPos -= (cameraDirection.cross(cameraUp)).normalized() * cameraSpeed;
    }
    else if (dir == Direction::RIGHT)
    {
        cameraPos += (cameraDirection.cross(cameraUp)).normalized() * cameraSpeed;
    }
}

void Camera::updateMouseLeftButtonDown(bool isDown, float x, float y)
{
    isLeftMouseButtonDown = isDown;
    if (isDown)
    {
        lastX = x;
        lastY = y;
    }
}

void Camera::processMouseMove(float x, float y, bool isConstrainPitch)
{
    if (isLeftMouseButtonDown)
    {
        float xOffset = x - lastX;
        float yOffset = y - lastY;
        xOffset *= mouseSensitivity;
        yOffset *= mouseSensitivity;
        lastX = x;
        lastY = y;

        yaw -= xOffset;
        pitch -= yOffset;

        if (isConstrainPitch)
        {
            if (pitch > 89.0f)
            {
                pitch = 89.0f;
            }
            if (pitch < -89.0f)
            {
                pitch = -89.0f;
            }
        }

        updateCameraDirection();
    }
}

void Camera::processMouseScroll(float yOffset)
{
    yOffset *= zoomSensitivity;
    if (zoom >= MIN_ZOOM && zoom <= MAX_ZOOM)
    {
        zoom -= yOffset;
    }
    if (zoom <= MIN_ZOOM)
    {
        zoom = MIN_ZOOM;
    }
    if (zoom >= MAX_ZOOM)
    {
        zoom = MAX_ZOOM;
    }
}

void Camera::updateCameraDirection()
{
    cameraDirection.X() = cos(degreeToRadian(yaw)) * cos(degreeToRadian(pitch));
    cameraDirection.Y() = sin(degreeToRadian(pitch));
    cameraDirection.Z() = sin(degreeToRadian(yaw)) * cos(degreeToRadian(pitch));
    cameraDirection.normalize();
}

void Camera::setPos(const Vector3& pos)
{
    this->cameraPos = pos;
}

void Camera::setWorldUp(const Vector3& worldup)
{
    this->cameraWorldUP = worldup;
}

void Camera::setCameraDirection(const Vector3& _cameraDirection)
{
    this->cameraDirection = _cameraDirection;
}

Vector3 Camera::getPos()
{
    return cameraPos;
}

Vector3 Camera::getWorldUp()
{
    return cameraWorldUP;
}

Vector3 Camera::getCameraDirection()
{
    return cameraDirection;
}

}
