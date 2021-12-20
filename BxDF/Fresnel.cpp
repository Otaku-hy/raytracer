#include "Fresnel.hpp"

Fresnel::Fresnel(/* args */)
{
}

Fresnel::~Fresnel()
{
}

Vector3f FresnelDielectric::Evaluate(float cosThetaI)
{
    float value = FrDielectric(cosThetaI, etaI, etaT);
    return Vector3f(value, value, value);
}

Vector3f FresnelDielectric::getEtaI()
{
    return Vector3f(etaI, etaI, etaI);
}

Vector3f FresnelDielectric::getEtaT()
{
    return Vector3f(etaT, etaT, etaT);
}

FresnelDielectric::~FresnelDielectric()
{
}

FresnelConductor::FresnelConductor(const Vector3f &_etaI, const Vector3f &_etaT, const Vector3f &_k) : etaI(_etaI), etaT(_etaT), k(_k)
{
}

Vector3f FresnelConductor::Evaluate(float costhetaI)
{
    return frConductor(costhetaI, etaI, etaT, k);
}

Vector3f FresnelConductor::getEtaI()
{
    return etaI;
}

Vector3f FresnelConductor::getEtaT()
{
    return etaT;
}

FresnelConductor::~FresnelConductor()
{
}
