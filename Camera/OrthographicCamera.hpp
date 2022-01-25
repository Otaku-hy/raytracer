#ifndef Orthographic_H
#define Orthographic_H

#include "Camera.hpp"
#include "Bounds.hpp"

class OrthographicCamera : public Camera
{
private:
    /* data */
public:
    OrthographicCamera() = default;
    OrthographicCamera(Film *_film, Bound3D bound);
    
    ~OrthographicCamera() override;
    
    Matrix4_4 ortho;
};

#endif