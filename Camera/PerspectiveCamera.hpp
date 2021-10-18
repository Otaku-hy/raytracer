#ifndef Perspective_H
#define Perspective_H

#include <iostream>

#include "Camera.hpp"

class PerspectiveCamera : public Camera
{
private:
    /* data */
public:
    PerspectiveCamera() = default;
    PerspectiveCamera(Film *_film, float zNear, float zFar, float aspect_ratio, float fov);
    ~PerspectiveCamera();

    Vector3f rasterToWorld(Vector3f &v) override;
    float GenerateRay(Ray &ray, cameraSample &sample) override;

    TransformMat perspective;
};

PerspectiveCamera::PerspectiveCamera(Film *_film, float zNear, float zFar, float aspect_ratio, float fov) : Camera(_film)
{
    float height = 2 * tan(radians(fov / 2.0)) * -zNear;
    float width = aspect_ratio * height;

    Matrix4f perspectiveMat, ortho, translateToOrigin, translateToNDC;
    perspectiveMat << zNear, 0, 0, 0,
        0, zNear, 0, 0,
        0, 0, (zNear + zFar), -zNear * zFar,
        0, 0, 1, 0;

    translateToNDC << 1, 0, 0, 0.5,
        0, 1, 0, 0.5,
        0, 0, 1, 0.5,
        0, 0, 0, 1;
    ortho << 1.0 / width, 0, 0, 0,
        0, 1.0 / height, 0, 0,
        0, 0, 1.0 / (zNear - zFar), 0,
        0, 0, 0, 1;
    translateToOrigin = Matrix4f::Identity();
    translateToOrigin(2, 3) = -(zNear + zFar) / 2.0;

    perspective = perspectiveMat;
    projection = translateToNDC * ortho * translateToOrigin;

    viewPort.inverse();
    projection.inverse();
    perspective.inverse();
}

PerspectiveCamera::~PerspectiveCamera()
{
}

float PerspectiveCamera::GenerateRay(Ray &ray, cameraSample &sample)
{
    Vector3f rasterPos = Vector3f(sample.pFilm[0], sample.pFilm[1], 1.0);
    Vector3f worldPos = rasterToWorld(rasterPos);

    Vector3f dir = (worldPos - cameraPos).normalized();

    ray.origin = cameraPos;
    ray.dir = dir;

    return 1;
}

Vector3f PerspectiveCamera::rasterToWorld(Vector3f &v)
{
    return view.trans(perspective.trans(projection.trans(viewPort.trans(v, Pos), Pos), Pos), Pos);
}

#endif