#ifndef Intersection_H
#define Intersection_H
#include "lib/Eigen/Eigen"
#include "Material.hpp"

using namespace Eigen;

class Intersection
{
private:
    /* data */
public:
    Intersection() = default;
    ~Intersection();

    Vector3f pos;
    Vector3f norm;
    Material *material = NULL;
    bool happen = false;

};

Intersection::~Intersection()
{
}

#endif