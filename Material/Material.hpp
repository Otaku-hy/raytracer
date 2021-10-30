#ifndef Material_H
#define Material_H

#include "../pbrt.hpp"
#include "../BxDF/BxDF.hpp"

class Material
{
private:
    /* data */
public:
    Material();
    ~Material();

    virtual void ComputeScatteringFunctions(Intersection &intersection) = 0;
};

Material::Material(/* args */)
{
}

Material::~Material()
{
}

#endif