#ifndef MatteMaterial_H
#define MatteMaterial_H

#include "Material.hpp"
#include "BSDF.hpp"

#include "../BxDF/Lambertain.hpp"

class MatteMaterial : public Material
{
private:
    /* data */
public:
    MatteMaterial(const Vector3f &_kd, const float _roughness) : kd(_kd), roughness(_roughness){};
    ~MatteMaterial();

    void ComputeScatteringFunctions(Intersection &intersection) override;

    Vector3f kd;
    float roughness;
};

void MatteMaterial::ComputeScatteringFunctions(Intersection &intersection)
{
    if (roughness == 0)
    {
        std::shared_ptr<BxDF> bxdf = std::make_shared<Lambertain>(kd);
        intersection.bsdf = new BSDF(intersection, bxdf);
    }
}

MatteMaterial::~MatteMaterial()
{
}

#endif