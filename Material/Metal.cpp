#include "Metal.hpp"

Metal::Metal(const Vector3f &_R, const Vector3f &_etaI, const Vector3f &_etaT, const Vector3f &_k, const float &_sigma) : R(_R), etaI(_etaI), etaT(_etaT), k(_k), sigma(_sigma)
{
}

void Metal::ComputeScatteringFunctions(SurfaceInteraction &interaction)
{
    FresnelConductor *fresnel = new FresnelConductor(etaI, etaT, k);
    BeckmannDistribution *distribution = new BeckmannDistribution(sigma);
    // GGXDistribution *distribution = new GGXDistribution(sigma);

    std::shared_ptr<BxDF> bxdf = std::make_shared<MicrofacetReflect>(R, distribution, fresnel);
    std::vector<std::shared_ptr<BxDF>> bxdfs;
    bxdfs.push_back(bxdf);

    interaction.bsdf = new BSDF(interaction, bxdfs);
}

Metal::~Metal()
{
}
