#ifndef Intersection_H
#define Intersection_H

#include "Material.hpp"
#include "lib/Eigen/Eigen"

using namespace Eigen;

class Primitive;

class Intersection
{
private:
    /* data */
public:
    Intersection() = default;
    Intersection(float tMax) : t1(tMax){};
    ~Intersection();

    float t1;

    bool happen = false;

    Vector3f pos = Vector3f(0, 0, 0);
    Vector3f norm = Vector3f(0, 0, 0);
    Vector2f uv = Vector2f(0, 0);

    Primitive *primitive = NULL;
};

Intersection::~Intersection()
{
}

#endif