#ifndef Camera_H
#define Camera_H

#include <vector>

#include "Film.hpp"

#include "../Ray.hpp"
#include "../Utils.hpp"
#include "../lib/Eigen/Eigen"
#include "../Filter/MitchellFilter.hpp"
#include "../TransformMat/TransformMat.hpp"

using namespace Eigen;

struct cameraSample
{
    Vector2f pFilm;
};

class Camera
{
private:
    /* data */
public:
    Camera() = default;
    Camera(Film *_film);
    ~Camera();

    virtual float GenerateRay(Ray &ray, cameraSample &sample) = 0;
    virtual Vector3f rasterToWorld(Vector3f &v) = 0;

    float getCameraSample(const Vector2i rasterPos);
    void setViewMat(Vector3f pos, Vector3f lookPos, Vector3f up);

    Film *film;

    Vector3f cameraPos;

    TransformMat view;
    TransformMat projection;
    TransformMat viewPort;
};

Camera::Camera(Film *_film) : film(_film)
{
    Matrix4f viewPortMat = Matrix4f::Identity();
    viewPortMat(0, 0) = film->fullResolution[0];
    viewPortMat(1, 1) = film->fullResolution[1];

    viewPort = viewPortMat;
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

    view = viewMat * translate;

    view.inverse();
}

Camera::~Camera()
{
}

#endif