#ifndef TransformPrimitive_H
#define TransformPrimitive_H

#include <memory>

#include "Primitive.hpp"

#include "../lib/Eigen/Eigen"
#include "../Matrix4_4/Matrix4_4.hpp"

using namespace Eigen;

class TransformPrimitive : public Primitive
{
private:
    /* data */
public:
    TransformPrimitive() = default;
    TransformPrimitive(std::shared_ptr<Matrix4_4> _WtoP,
                       std::shared_ptr<Matrix4_4> _PtoW,
                       std::shared_ptr<Primitive> _primitive) : WtoP(_WtoP), PtoW(_PtoW), primitive(_primitive){};
    ~TransformPrimitive();

    bool intersect(Ray &ray, Intersection &intersection) override;
    AreaLight *getAreaLight() override;
    Material *getMaterial() override;
    Bound3D worldBound() override;

    std::shared_ptr<Matrix4_4> WtoP;
    std::shared_ptr<Matrix4_4> PtoW;
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
    Vector3f dir = Vector4to3(*WtoP * Vector3to4(ray.dir, NORM));
    Vector3f origin = Vector4to3(*WtoP * Vector3to4(ray.origin, POS));

    Ray rayT(origin, dir);

    if (!primitive->intersect(rayT, intersection))
        return false;

    intersection.primitive = this;
    intersection.pos = Vector4to3(*PtoW * Vector3to4(intersection.pos, POS));
    return true;
}

#endif
