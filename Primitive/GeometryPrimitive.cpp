#include "GeometryPrimitive.hpp"

bool GeometryPrimitive::Intersect(const Ray &ray, SurfaceInteraction &interaction)
{
    float tHit;
    if (!shape->Intersect(ray, tHit, interaction))
        return false;
    interaction.primitive = this;
    interaction.w0 = -ray.dir;
    if(material)
        material->ComputeScatteringFunctions(interaction);
    return true;
}

bool GeometryPrimitive::IntersectP(Ray &ray)
{
    if (!shape->IntersectP(ray))
        return false;

    return true;
}

Material *GeometryPrimitive::getMaterial()
{
    return material.get();
}

AreaLight *GeometryPrimitive::getAreaLight()
{
    return light.get();
}

Bound3D GeometryPrimitive::worldBound()
{
    return shape->genBoundingBox();
}

GeometryPrimitive::~GeometryPrimitive()
{
}