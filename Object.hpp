#ifndef Object_H
#define Object_H

#include "lib/Eigen/Eigen"
#include "Ray.hpp"
#include "Material.hpp"
#include "Intersection.hpp"

using namespace Eigen;

class Object
{
private:
    /* data */
public:
    Object(/* args */);
    ~Object();

    virtual bool ray_intersection(Ray ray, float &t1) = 0;
    virtual void computeIntersection(Intersection &intersection, float t, Ray ray) = 0;
    virtual float getArea() = 0;
    virtual bool hasEmit() = 0;
};

Object::Object(/* args */)
{
}

Object::~Object()
{
}

#endif