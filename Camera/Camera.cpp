#include "Camera.hpp"

Camera::Camera(Film *_film) : film(_film)
{
    Matrix4f viewPortMat = Matrix4f::Identity();
    viewPortMat(0, 0) = film->fullResolution[0];
    viewPortMat(1, 1) = film->fullResolution[1];

    viewPort(viewPortMat);
}


void Camera::setViewMat(Vector3f pos, Vector3f lookPos, Vector3f up)
{
    cameraPos = pos;

    Matrix4f translate = Matrix4f::Identity();
    translate(0, 3) = -pos[0];
    translate(1, 3) = -pos[1];
    translate(2, 3) = -pos[2];

    Vector3f z = (pos - lookPos).normalized();
    Vector3f x = up.cross(z).normalized();
    Vector3f y = z.cross(x).normalized();

    Matrix4f viewMat = Matrix4f::Identity();

    viewMat.row(0) = Vector4f(x[0], x[1], x[2], 0);
    viewMat.row(1) = Vector4f(y[0], y[1], y[2], 0);
    viewMat.row(2) = Vector4f(z[0], z[1], z[2], 0);
    viewMat(3, 3) = 1.0f;

    view(viewMat * translate);

    view.inverse();
}

Camera::~Camera()
{
}