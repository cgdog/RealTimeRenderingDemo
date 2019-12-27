#include "camera.h"
#include "Utilities/helperFuncs.h"
namespace LXY {


Camera::Camera()
{

}

Camera::~Camera()
{

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

    return orthoTransform;
}

Transform& Camera::getTransform()
{
    return transform;
}

}
