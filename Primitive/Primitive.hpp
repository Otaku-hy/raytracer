#ifndef Primitive_H
#define Primitive_H

#include "../Material.hpp"
#include "../Light/Light.hpp"
#include "../Intersection.hpp"
#include "../lib/Eigen/Eigen"
#include "../Shape/Shapes.hpp"
#include "../Light/AreaLight.hpp"
#include "../Acceleration/Bounds.hpp"

using namespace Eigen;

class Primitive
{
private:
    /* data */
public:
    Primitive() = default;
    ~Primitive();

    virtual bool intersect(Ray &ray, Intersection &intersection) = 0;
    virtual AreaLight *getAreaLight() = 0;
    virtual Material *getMaterial() = 0;
    virtual Bound3D worldBound() = 0;
};

Primitive::~Primitive()
{
}

#endif