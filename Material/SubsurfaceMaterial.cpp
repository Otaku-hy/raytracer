#include "SubsurfaceMaterial.hpp"

SubsurfaceMaterial::SubsurfaceMaterial(float _etaA, float _etaB, float _sigma_s, float _sigma_a, float _A, float _Radius) : etaA(_etaA), etaB(_etaB), sigma_s(_sigma_s), sigma_a(_sigma_a), A(_A), Radius(_Radius)
{
}

void SubsurfaceMaterial::ComputeScatteringFunctions(SurfaceInteraction &interaction)
{
    interaction.bsdf = NULL;
    interaction.bssrdf = new BSSRDF(interaction, etaA, etaB, sigma_s, sigma_a, A, Radius);
    // std::shared_ptr<BxDF> bxdf = std::make_shared<BssrdfAdaptor>(etaA, etaB);
    // interaction.bsdf = new BSDF(interaction, bxdf);
}

SubsurfaceMaterial::~SubsurfaceMaterial()
{
}
