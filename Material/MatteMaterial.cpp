#include "MatteMaterial.hpp"

void MatteMaterial::ComputeScatteringFunctions(SurfaceInteraction &interaction)
{
    if (roughness == 0)
    {
        std::shared_ptr<BxDF> bxdf = std::make_shared<Lambertain>(kd);
        interaction.bsdf = new BSDF(interaction, bxdf);
    }
    else
    {
        std::shared_ptr<BxDF> bxdf = std::make_shared<OrenNayar>(kd, roughness);
        interaction.bsdf = new BSDF(interaction, bxdf);
    }
}

MatteMaterial::~MatteMaterial()
{
}