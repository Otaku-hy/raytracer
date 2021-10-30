#ifndef Aggregate_H
#define Aggregate_H

#include "../pbrt.hpp"
#include "../Primitive/Primitive.hpp"

class Aggregate : public Primitive
{
private:
    /* data */
public:
    Aggregate() = default;
    ~Aggregate();

    bool intersect(Ray &ray, Intersection &intersection);
    AreaLight *getAreaLight();
    Material *getMaterial();
    Bound3D worldBound();
};

Aggregate::~Aggregate()
{
}

#endif