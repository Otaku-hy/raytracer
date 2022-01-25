#ifndef MatteMaterial_H
#define MatteMaterial_H

#include "pbrt.hpp"
#include "BSDF.hpp"
#include "Material.hpp"
#include "BxDF.hpp"
#include "Lambertain.hpp"
#include "Microfacet.hpp"

class MatteMaterial : public Material
{
private:
    /* data */
public:
    MatteMaterial() = default;
    MatteMaterial(const Vector3f &_kd, const float &_roughness) : kd(_kd), roughness(_roughness){};
    
    ~MatteMaterial() override;
    void ComputeScatteringFunctions(SurfaceInteraction &interaction) override;

    Vector3f kd;
    float roughness;
};

#endif