#include "PlasticMaterial.hpp"

PlasticMaterial::PlasticMaterial(const Vector3f &_R, const float &_etaI, const float &_etaT, const float _sigma) : R(_R), etaI(_etaI), etaT(_etaT), sigma(_sigma)
{
}

void PlasticMaterial::ComputeScatteringFunctions(SurfaceInteraction &interaction)
{
    FresnelDielectric *fresnel = new FresnelDielectric(etaI, etaT);
    BeckmannDistribution *distribution = new BeckmannDistribution(sigma);

    std::shared_ptr<BxDF> bxdf = std::make_shared<MicrofacetTransmission>(R, distribution, fresnel);
    // std::shared_ptr<BxDF> bxdf2 = std::make_shared<Lambertain>(R / 3.5);
    std::vector<std::shared_ptr<BxDF>> bxdfs;
    bxdfs.push_back(bxdf);
    // bxdfs.push_back(bxdf2);

    interaction.bsdf = new BSDF(interaction, bxdfs);
}

PlasticMaterial::~PlasticMaterial()
{
}
