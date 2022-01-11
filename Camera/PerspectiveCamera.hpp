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
    
    ~PerspectiveCamera() override;

    Vector3f rasterToWorld(Vector3f &v) override;
    float GenerateRay(Ray &ray, cameraSample &sample) override;

    Matrix4_4 perspective;
    Matrix4_4 NDC;
    Matrix4_4 orthoM;
};

#endif