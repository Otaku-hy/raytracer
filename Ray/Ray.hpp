#ifndef Ray_H
#define Ray_H

#include "pbrt.hpp"

using namespace Eigen;

class Ray
{
private:
    /* data */
public:
    Ray(const Vector3f &_origin = Vector3f(0, 0, 0),const Vector3f &_dir = Vector3f(0, 0, 0), const float &_tMax = 5000) : origin(_origin), dir(_dir), tMax(_tMax){};
    
    virtual ~Ray();
    
    inline Vector3f operator()(float t);

    Vector3f origin, dir;
    float tMax;
    // Medium *medium;
};

class RayDifferential : public Ray
{
private:
    /* data */
public:
    RayDifferential(const Vector3f &_origin = Vector3f(0, 0, 0),const Vector3f &_dir = Vector3f(0, 0, 0),const size_t &_tMax = 5000) : Ray(_origin, _dir, _tMax)
    {
        hasDifferentials = false;
    };
    
    ~RayDifferential() override;

    void ScaleDifferentials(float t);

    bool hasDifferentials;
    Vector3f rxOrigin, ryOrigin;
    Vector3f rxDir, ryDir;
};

#endif