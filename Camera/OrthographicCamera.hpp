#ifndef Orthographic_H
#define Orthographic_H

#include "Camera.hpp"
#include "../Acceleration/Bounds.hpp"

class OrthographicCamera : public Camera
{
private:
    /* data */
public:
    OrthographicCamera() = default;
    OrthographicCamera(Film *_film, Bound3D bound);
    ~OrthographicCamera();

    Matrix4_4 ortho;
};

#endif