#include "SurfaceInteraction.hpp"

Vector3f SurfaceInteraction::Le(Vector3f wi)
{
    AreaLight *light = primitive->getAreaLight();
    if (light)
    {
        return light->Le(*this, wi);
    }
    return Vector3f(0, 0, 0);
}

SurfaceInteraction::~SurfaceInteraction()
{
    if (bsdf)
        delete bsdf;
    if (bssrdf)
        delete bssrdf;
}
