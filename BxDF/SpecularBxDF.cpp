#include "SpecularBxDF.hpp"


Vector3f SpecularReflection::fr(const Vector3f &w0, const Vector3f &wi)
{
    return Vector3f(0,0,0);
}

Vector3f SpecularReflection::sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue)
{
    if (cosTheta(w0) == 0)
        return Vector3f(0, 0, 0);
    wi = (2 * cosTheta(w0) * Vector3f(0, 1, 1) - w0).normalized();
    pdf = 1.0;

    float fr = fresnel->Evaluate(wi);
    return Vector3f(fr,fr,fr) / abs(cosTheta(wi));
}

SpecularReflection::~SpecularReflection()
{
}

class SpecularTransmission : public BxDF
{
private:
    /* data */
public:
    SpecularTransmission() = default;
    SpecularTransmission(Fresnel *_fresnel, float _etaA, float _etaB) : BxDF(BxDFType(SPECULAR | TRANSMISSION)), fresnel(_fresnel), etaA(_etaA), etaB(_etaB){};
    ~SpecularTransmission();

    Vector3f fr(const Vector3f &w0, const Vector3f &wi) override;
    Vector3f sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue) override;

    Fresnel *fresnel;
    float etaA, etaB;
};

Vector3f SpecularTransmission::fr(const Vector3f &w0, const Vector3f &wi)
{
    return Vector3f(0,0,0);
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
        return Vector3f(0,0,0);

    float cosThetaT = sqrt(1 - sinThetaT * sinThetaT);
    cosThetaT = cosThetaI > 0 ? -cosThetaT : cosThetaT;

    wi = wt_vert + cosThetaT * Vector3f(0, 1, 0);
    pdf = 1.0;

    float value = (1 - fresnel->Evaluate(wi)) * etaItmp * etaTtmp / (etaTtmp * etaTtmp) / abs(cosTheta(wi));
    return Vector3f(value,value,value);
}

SpecularTransmission::~SpecularTransmission()
{
}
