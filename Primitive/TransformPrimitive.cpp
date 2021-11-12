#include "TransformPrimitive.hpp"

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

bool TransformPrimitive::Intersect(const Ray &ray, SurfaceInteraction &interaction)
{
    // transform ray to primitive coord
    Vector3f dir = Vector4to3(*WtoP * Vector3to4(ray.dir, NORM));
    Vector3f origin = Vector4to3(*WtoP * Vector3to4(ray.origin, POS));

    Ray rayT(origin, dir);

    if (!primitive->Intersect(rayT, interaction))
        return false;

    interaction.primitive = this;
    interaction.pos = Vector4to3(*PtoW * Vector3to4(interaction.pos, POS));
    return true;
}

bool TransformPrimitive::IntersectP(Ray &ray)
{
    if (!primitive->IntersectP(ray))
        return false;

    return true;
}
