#ifndef Fresnel_Help
#define Fresnel_Help

#include "Eigen/Eigen"
#include "Utils.hpp"

inline float FrDielectric(float cosThetaI, float etaI, float etaT)
{
    if (cosThetaI == 0)
        return 0;
    bool entering = cosThetaI > 0 ? true : false;
    if (!entering)
    {
        std::swap(etaI, etaT);
        cosThetaI = std::abs(cosThetaI);
    }
    float sin2ThetaI = 1 - cosThetaI * cosThetaI;
    float sin2ThetaT = etaI * etaI / (etaT * etaT) * sin2ThetaI;
    if (sin2ThetaT > 1)
    {
        return 1;
    }
    float cosThetaT = std::sqrt(1 - sin2ThetaT);

    float rp = (etaT * cosThetaI - etaI * cosThetaT) / (etaT * cosThetaI + etaI * cosThetaT);
    float rv = (etaI * cosThetaI - etaT * cosThetaT) / (etaI * cosThetaI + etaT * cosThetaT);

    return (rp * rp + rv * rv) * 0.5;
}

inline Vector3f frConductor(float cosThetaI, const Vector3f &etaI, const Vector3f &etaT, const Vector3f &k)
{
    Vector3f eta = etaT / etaI;
    Vector3f etak = k / etaI;

    cosThetaI = clamp(cosThetaI, -1, 1);
    float cos2ThetaI = cosThetaI * cosThetaI;
    float sin2ThetaI = std::max(0.0f, 1 - cosThetaI * cosThetaI);
    float sinThetaI = std::sqrt(sin2ThetaI);

    Vector3f t0 = eta * eta - etak * etak + (-sin2ThetaI);
    Vector3f a2plusb2 = sqrt(t0 * t0 + 4 * (eta * eta * etak * etak));
    Vector3f a = sqrt(0.5 * (a2plusb2 + t0));

    Vector3f t1 = a2plusb2 + cos2ThetaI;
    Vector3f t2 = 2 * a * cosThetaI;

    Vector3f t3 = cos2ThetaI * a2plusb2 + sin2ThetaI * sin2ThetaI;
    Vector3f t4 = t2 * sin2ThetaI;

    Vector3f rV = (t1 - t2) / (t1 + t2);
    Vector3f rP = rV * ((t3 - t4) / (t3 + t4));

    return (rV * rV + rP * rP) * 0.5;
}

#endif