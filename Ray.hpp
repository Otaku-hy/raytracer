#ifndef Ray_H
#define Ray_H

#include "Medium.hpp"

#include "pbrt.hpp"

using namespace Eigen;

class Ray
{
private:
    /* data */
public:
    Ray(Vector3f _origin = Vector3f(0, 0, 0), Vector3f _dir = Vector3f(0, 0, 0), size_t _tMax = 5000, Medium *_medium = NULL) : origin(_origin), dir(_dir), tMax(_tMax),medium(_medium)  {};
    ~Ray();

    inline Vector3f operator()(float t);

    Vector3f origin;
    Vector3f dir;

    size_t tMax;

    Medium *medium;
};    

Vector3f Ray::operator()(float t)
{
    return origin + t * dir;
}

Ray::~Ray()
{
}

class RayDifferential : public Ray
{
private:
    /* data */
public:
    RayDifferential(Vector3f _origin = Vector3f(0, 0, 0), Vector3f _dir = Vector3f(0, 0, 0), size_t _tMax = 500,Medium *_medium = NULL) : Ray(_origin, _dir,_tMax,_medium)
    {
        hasDifferentials = false;
    };
    ~RayDifferential();

    void ScaleDifferentials(float t);

    bool hasDifferentials;
    Vector3f rxOrigin, ryOrigin;
    Vector3f rxDir, ryDir;
};

void RayDifferential::ScaleDifferentials(float s)
{
    rxOrigin = origin + (rxOrigin - origin) * s;
    ryOrigin = origin + (ryOrigin - origin) * s;

    rxDir = dir + (rxDir - dir) * s;
    ryDir = dir + (ryDir - dir) * s;
}

RayDifferential::~RayDifferential()
{
}

#endif