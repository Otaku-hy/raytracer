#ifndef SpecularMaterial_H
#define SpecularMaterial_H

#include "pbrt.hpp"
#include "Material.hpp"
#include "SpecularBxDF.hpp"
#include "BxDF.hpp"
#include "BSDF.hpp"
#include "SurfaceInteraction.hpp"

class SpecularMaterial : public Material
{
private:
    /* data */
public:
    SpecularMaterial(const Vector3f &_R, const float &_etaI, const float &_etaT) : R(_R), etaI(_etaI), etaT(_etaT){};
    ~SpecularMaterial();

    void ComputeScatteringFunctions(SurfaceInteraction &interaction) override;

    Vector3f R;
    float etaI, etaT;
};

#endif