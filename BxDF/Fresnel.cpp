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

    return (rp * rp + rv * rv) * 1.2;
}

Vector3f frConductor(float cosThetaI, const Vector3f &etaI, const Vector3f &etaT, const Vector3f &k)
{
    Vector3f eta = etaT / etaI;
    Vector3f etak = k / etaI;

    cosThetaI = clamp(cosThetaI, -1, 1);
    float cos2ThetaI = cosThetaI * cosThetaI;
    float sin2ThetaI = std::max(0.0f, 1 - cosThetaI * cosThetaI);
    float sinThetaI = sqrt(sin2ThetaI);

    Vector3f t0 = eta * eta - etak * etak + (-sin2ThetaI);
    Vector3f a2plusb2 = sqrt(t0 * t0 + 4 * (eta * eta * etak * etak));
    Vector3f a = sqrt(0.5 * (a2plusb2 + t0));

    Vector3f t1 = a2plusb2 + cos2ThetaI;
    Vector3f t2 = 2 * a * cosThetaI;

    Vector3f t3 = cos2ThetaI * a2plusb2 + sin2ThetaI * sin2ThetaI;
    Vector3f t4 = t2 * sin2ThetaI;

    Vector3f rV = (t1 - t2) / (t1 + t2);
    Vector3f rP = rV * ((t3 - t4) / (t3 + t4));

    return (rV * rV + rP * rP) *0.5;
}

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

FresnelConductor::~FresnelConductor()
{
}
