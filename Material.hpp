#ifndef Material_H
#define Material_H

#include "lib/Eigen/Eigen"
#include "Utils.hpp"

const float PI = 3.1415926;

using namespace Eigen;

class Material
{
private:
    /* data */
public:
    Material(Vector3f _albedo);
    ~Material();
    Vector3f eval(Vector3f wi, Vector3f norm);
    Vector3f sample(Vector3f norm);
    float pdf();

    Vector3f albedo;
};

Material::Material(Vector3f _albedo)
{
    albedo = _albedo;
}

Material::~Material()
{
}

Vector3f Material::eval(Vector3f wi, Vector3f norm)
{
    if (wi.dot(norm) > 0)
    {
        Vector3f brdf = albedo / PI;
        return brdf;
    }
    else
    {
        return Vector3f(0, 0, 0);
    }
}

Vector3f Material::sample(Vector3f norm)
{
    float x = randomNeg(100);
    float y = randomNeg(100);
    float z = randomFloat(100);

    Vector3f dir(x, y, z);
    dir = dir.normalized();
    dir = toWorld(dir,norm);

    return dir;
}

float Material::pdf()
{
    return 1.0/(2*PI);
}

#endif