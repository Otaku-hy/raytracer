#ifndef Light_H
#define Light_H
#include "lib/Eigen/Eigen"

using namespace Eigen;

class PointLight
{
private:
    /* data */
public:
    PointLight();
    ~PointLight();

    Vector3f pos;
    Vector3f color;
};

PointLight::PointLight()
{
}

PointLight::~PointLight()
{
}

class AreaLight : public PointLight
{
private:
    /* data */
public:
    AreaLight(Vector3f _pos, Vector3f _color, float _area);
    ~AreaLight();
    Vector3f SampleLight();
    float lightPdf();

    Vector3f u, v;
    Vector3f norm;
    float area;
};

AreaLight::AreaLight(Vector3f _pos, Vector3f _color, float _area)
{
    pos = _pos;
    color = _color;
    area = _area;
    u = Vector3f(1, 0, 0);
    v = Vector3f(0, 0, 1);
    norm = Vector3f(0, -1, 0);
}

AreaLight::~AreaLight()
{
}

Vector3f AreaLight::SampleLight()
{
    float random_u = randomFloat(100);
    float random_v = randomFloat(100);

    return pos + random_u * u + random_v * v;
}

float AreaLight::lightPdf()
{
    return 1.0 / area;
}

#endif