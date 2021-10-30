#ifndef Primitive_H
#define Primitive_H

#include "../pbrt.hpp"
#include "../Shape/Shapes.hpp"
#include "../Matrix4_4/Matrix4_4.hpp"
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