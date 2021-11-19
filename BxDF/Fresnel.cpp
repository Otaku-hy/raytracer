#include "Fresnel.hpp"

float FrDielectric(float cosThetaI, float etaI, float etaT)
{
    if (cosThetaI == 0)
        return 0;
    bool entering = cosThetaI > 0 ? true : false;
    if (!entering)
    {
        std::swap(etaI, etaT);
        cosThetaI = abs(cosThetaI);
    }
    float sinThetaI = sqrt(1 - cosThetaI * cosThetaI);
    float sinThetaT = etaI / etaT * sinThetaI;
    if (sinThetaT > 1)
    {
        return 1;
    }
    float cosThetaT = sqrt(1 - sinThetaT * sinThetaT);

    float rp = (etaT * cosThetaI - etaI * cosThetaT) / (etaT * cosThetaI + etaI * cosThetaT);
    float rv = (etaI * cosThetaI - etaT * cosThetaT) / (etaI * cosThetaI + etaT * cosThetaT);

    return (rp * rp + rv * rv) * 0.5;
    // return 1;
}

Fresnel::Fresnel(/* args */)
{
}

Fresnel::~Fresnel()
{
}

float FresnelDielectric::Evaluate(float cosThetaI)
{
    return FrDielectric(cosThetaI, etaI, etaT);
}

FresnelDielectric::~FresnelDielectric()
{
}