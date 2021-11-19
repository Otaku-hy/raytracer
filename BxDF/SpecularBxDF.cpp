#include "SpecularBxDF.hpp"

Vector3f SpecularReflection::fr(const Vector3f &w0, const Vector3f &wi)
{
    return Vector3f(0, 0, 0);
}

Vector3f SpecularReflection::sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue)
{
    wi = (2 * cosTheta(w0) * Vector3f(0, 1, 0) - w0).normalized();
    pdf = 1.0;

    float fr = fresnel->Evaluate(cosTheta(wi));
    return R * fr / abs(cosTheta(wi));
}

float SpecularReflection::PDF(const Vector3f &w0, const Vector3f &wi)
{
    return 0;
}

SpecularReflection::~SpecularReflection()
{
}

Vector3f SpecularTransmission::fr(const Vector3f &w0, const Vector3f &wi)
{
    return Vector3f(0, 0, 0);
}

Vector3f SpecularTransmission::sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue)
{
    float cosThetaI = clamp(cosTheta(w0), -1, 1);
    if (cosThetaI == 0)
        return Vector3f(0, 0, 0);

    float etaItmp = cosThetaI > 0 ? etaA : etaB;
    float etaTtmp = cosThetaI > 0 ? etaB : etaA;

    Vector3f wt_vert = -etaItmp / etaTtmp * (w0 - cosThetaI * Vector3f(0, 1, 0));
    float sinThetaI = sqrt(1 - cosThetaI * cosThetaI);
    float sinThetaT = etaItmp / etaTtmp * sinThetaI;

    if (sinThetaT >= 1)
        return Vector3f(0, 0, 0);

    float cosThetaT = sqrt(1 - sinThetaT * sinThetaT);
    cosThetaT = cosThetaI > 0 ? -cosThetaT : cosThetaT;

    wi = wt_vert + cosThetaT * Vector3f(0, 1, 0);
    pdf = 1.0;

    float value = (1 - fresnel->Evaluate(cosThetaI)) * etaItmp * etaTtmp / (etaTtmp * etaTtmp) / abs(cosTheta(wi));
    return Vector3f(value, value, value);
}

SpecularTransmission::~SpecularTransmission()
{
}
