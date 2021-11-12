#include "Ray.hpp"

Vector3f Ray::operator()(float t)
{
    return origin + t * dir;
}

Ray::~Ray()
{
}

void RayDifferential::ScaleDifferentials(float s)
{
    rxOrigin = origin + (rxOrigin - origin) * s;
    ryOrigin = origin + (ryOrigin - origin) * s;

    rxDir = dir + (rxDir - dir) * s;
    ryDir = dir + (ryDir - dir) * s;
}

RayDifferential::~RayDifferential()
{
}
