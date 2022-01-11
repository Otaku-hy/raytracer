#include "SpecularBxDF.hpp"

Vector3f SpecularReflection::fr(const Vector3f &w0, const Vector3f &wi)
{
    return Vector3f(0, 0, 0);
}

Vector3f SpecularReflection::sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue)
{
    wi = (2 * cosTheta(w0) * Vector3f(0, 1, 0) - w0).normalized();
    pdf = 1.0;

    Vector3f fr = fresnel->Evaluate(cosTheta(wi));
    return R * fr / std::abs(cosTheta(wi));
}

float SpecularReflection::PDF(const Vector3f &w0, const Vector3f &wi)
{
    return 0;
}

SpecularReflection::~SpecularReflection()
{
    delete fresnel;
}

SpecularTransmission::SpecularTransmission(Fresnel *_fresnel, const Vector3f &_R, float _etaA, float _etaB) : BxDF(BxDFType(SPECULAR | TRANSMISSION)), fresnel(_fresnel), R(_R), etaA(_etaA), etaB(_etaB)
{
}

Vector3f SpecularTransmission::fr(const Vector3f &w0, const Vector3f &wi)
{
    return Vector3f(0, 0, 0);
}

float SpecularTransmission::PDF(const Vector3f &w0, const Vector3f &wi)
{
    return 0;
}

Vector3f SpecularTransmission::sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue)
{
    //compute direction
    float etaT = SameHemisphere(w0, Vector3f(0, 1, 0)) ? etaA : etaB;
    float etaI = SameHemisphere(w0, Vector3f(0, 1, 0)) ? etaB : etaA;

    float sinthetaI = etaT * sinTheta(w0) / etaI;
    if (sinthetaI > 1.0)
    {
        pdf = 0;
        return Vector3f(0, 0, 0);
    }

    float costhetaI = std::sqrt(1 - sinthetaI * sinthetaI);
    Vector3f wV = sinthetaI * (Vector3f(-w0[0], 0, -w0[2]).normalized());
    Vector3f wP = costhetaI * (Vector3f(0, -w0[1], 0).normalized());
    wi = (wV + wP).normalized();

    //compute value
    pdf = 1;
    Vector3f fr = Vector3f(1, 1, 1) - fresnel->Evaluate(cosTheta(wi));

    return R * fr * etaT * etaT / (etaI * etaI * std::abs(costhetaI));
}

SpecularTransmission::~SpecularTransmission()
{
    delete fresnel;
}
