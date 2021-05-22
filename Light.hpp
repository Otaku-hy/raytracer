#ifndef Light_H
#define Light_H
#include "lib/Eigen/Eigen"

using namespace Eigen;

class PointLight
{
private:
    /* data */
public:
    PointLight(Vector3f _pos, Vector3f _color);
    ~PointLight();

    Vector3f pos;
    Vector3f color;
};

PointLight::PointLight(Vector3f _pos, Vector3f _color)
{
    pos = _pos;
    color = _color;
}

PointLight::~PointLight()
{
}

class AreaLight
{
private:
    /* data */
public:
    AreaLight(/* args */);
    ~AreaLight();
};

AreaLight::AreaLight(/* args */)
{
}

AreaLight::~AreaLight()
{
}


#endif