#ifndef Primitive_H
#define Primitive_H

#include "pbrt.hpp"

class Primitive
{
private:
    /* data */
public:
    Primitive();
    
    virtual ~Primitive();
    virtual bool Intersect(const Ray &ray, SurfaceInteraction &interaction) = 0;
    virtual bool IntersectP(Ray &ray) = 0;

    virtual AreaLight *getAreaLight() = 0;
    virtual Material *getMaterial() = 0;
    virtual Bound3D worldBound() = 0;
};

#endif