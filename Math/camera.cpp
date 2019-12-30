#include "camera.h"
#include "Utilities/helperFuncs.h"
namespace LXY {


Camera::Camera()
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
    cameraRight = worldUp.cross(cameraDirection);
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

}
