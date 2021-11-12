#include "Light.hpp"

Light::Light()
{
}

Light::~Light()
{
}

Vector3f Light::Le(const Interaction &itLight, const Vector3f &wi)
{
    return itLight.norm.dot(wi) > 0 ? Lemit : Vector3f(0, 0, 0);
}