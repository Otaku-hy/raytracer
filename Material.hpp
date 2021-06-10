#ifndef Material_H
#define Material_H

#include "lib/Eigen/Eigen"
#include "Utils.hpp"

const float PI = 3.1415926;

using namespace Eigen;

enum MaterialType
{
    DIFFUSE,
    GLOSSY,
    MICROFACET,
};

class Material
{
private:
    /* data */
public:
    Material(Vector3f _albedo, MaterialType _type, Vector3f _emissiom);
    Material() = default;
    ~Material();
    Vector3f eval(Vector3f wi, Vector3f norm);
    Vector3f sample(Vector3f norm);
    bool hasEmission();
    float pdf();

    Vector3f albedo;
    MaterialType type;
    Vector3f emission;
};

Material::Material(Vector3f _albedo, MaterialType _type, Vector3f _emissiom)
{
    albedo = _albedo;
    type = _type;
    emission = _emissiom;
}

Material::~Material()
{
}

Vector3f Material::eval(Vector3f wi, Vector3f norm)
{
    switch (type)
    {
    case DIFFUSE:
        if (wi.dot(norm) > 0)
        {
            Vector3f brdf = albedo / PI;
            return brdf;
        }
        else
        {
            return Vector3f(0, 0, 0);
        }
        break;

    default:
        break;
    }
}

Vector3f Material::sample(Vector3f norm)
{
    switch (type)
    {
    case DIFFUSE:
        float x = randomNeg(100);
        float y = randomNeg(100);
        float z = randomFloat(100);

        Vector3f dir(x, y, z);
        dir = dir.normalized();
        dir = toWorld(dir, norm);

        return dir;
        break;

    default:
        break;
    }
}

float Material::pdf()
{
    switch (type)
    {
    case DIFFUSE:
        return 1.0 / (2 * PI);
        break;

    default:
        break;
    }
}

bool Material::hasEmission()
{
    if (emission.norm() > 0)
    {
        return true;
    }

    return false;
}

#endif