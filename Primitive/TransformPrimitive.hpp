#ifndef TransformPrimitive_H
#define TransformPrimitive_H

#include <memory>

#include "Primitive.hpp"

#include "../lib/Eigen/Eigen"
#include "../TransformMat/TransformMat.hpp"

using namespace Eigen;

class TransformPrimitive : public Primitive
{
private:
    /* data */
public:
    TransformPrimitive() = default;
    TransformPrimitive(std::shared_ptr<TransformMat> _WtoP,
                       std::shared_ptr<TransformMat> _PtoW,
                       std::shared_ptr<Primitive> _primitive) : WtoP(_WtoP), PtoW(_PtoW), primitive(_primitive){};
    ~TransformPrimitive();

    bool intersect(Ray &ray, Intersection &intersection) override;
    AreaLight *getAreaLight() override;
    Material *getMaterial() override;
    Bound3D worldBound() override;

    std::shared_ptr<TransformMat> WtoP;
    std::shared_ptr<TransformMat> PtoW;
    std::shared_ptr<Primitive> primitive;
};

TransformPrimitive::~TransformPrimitive()
{
}

Bound3D TransformPrimitive::worldBound()
{
    return primitive->worldBound();
}

AreaLight *TransformPrimitive::getAreaLight()
{
    return primitive->getAreaLight();
}

Material *TransformPrimitive::getMaterial()
{
    return primitive->getMaterial();
}

bool TransformPrimitive::intersect(Ray &ray, Intersection &intersection)
{
    // transform ray to primitive coord
    Vector3f dir = WtoP->trans(ray.dir, Norm);
    Vector3f origin = WtoP->trans(ray.origin, Pos);

    Ray rayT(origin, dir);

    if (!primitive->intersect(rayT, intersection))
        return false;

    intersection.primitive = this;
    intersection.pos = PtoW->trans(intersection.pos, Pos);
    return true;
}

#endif
