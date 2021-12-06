#include "SpecularMaterial.hpp"

void SpecularMaterial::ComputeScatteringFunctions(SurfaceInteraction &interaction)
{
    Fresnel *fresnel = new FresnelDielectric(etaI, etaT);
    std::shared_ptr<SpecularReflection> bxdf = std::make_shared<SpecularReflection>(fresnel, R);
    // std::shared_ptr<SpecularTransmission> bxdf = std::make_shared<SpecularTransmission>(fresnel, R, etaI, etaT);
    interaction.bsdf = new BSDF(interaction, bxdf);
}

SpecularMaterial::~SpecularMaterial()
{
}