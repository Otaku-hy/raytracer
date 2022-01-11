#ifndef Camera_H
#define Camera_H

#include <vector>

#include "Film.hpp"

#include "Ray.hpp"
#include "../Utils/Utils.hpp"
#include "../lib/Eigen/Eigen"
#include "../Filter/MitchellFilter.hpp"
#include "../Matrix4_4/Matrix4_4.hpp"

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
    
    virtual ~Camera();
    virtual float GenerateRay(Ray &ray, cameraSample &sample) = 0;
    virtual Vector3f rasterToWorld(Vector3f &v) = 0;

    float getCameraSample(const Vector2i rasterPos);
    void setViewMat(Vector3f pos, Vector3f lookPos, Vector3f up);

    Film *film;

    Vector3f cameraPos;

    Matrix4_4 view;
    Matrix4_4 viewPort;
};

#endif