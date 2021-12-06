#include "Microfacet.hpp"

OrenNayar::OrenNayar(Vector3f _kd, float _sigma) : BxDF(BxDFType(REFLECT | DIFFUSE)), kd(_kd), sigma(_sigma)
{
    float rdSigma2 = radians(sigma) * radians(sigma);
    A = 1 - rdSigma2 / (2 * (rdSigma2 + 0.33));
    B = 0.45 * rdSigma2 / (rdSigma2 + 0.09);
}

Vector3f OrenNayar::fr(const Vector3f &w0, const Vector3f &wi)
{
    int minTheta = cosTheta(wi) > cosTheta(w0) ? 0 : 1;
    float sinAlpha = (minTheta == 0 ? sinTheta(w0) : sinTheta(wi));
    float tanBeta = (minTheta == 0 ? tanTheta(wi) : tanTheta(w0));

    float cosDeltaPhi = 0;
    if (sinTheta(wi) > 1e-4 && sinTheta(w0) > 1e-4)
    {
        float sinPhiI = sinPhi(wi), cosPhiI = cosPhi(wi);
        float sinPhi0 = sinPhi(w0), cosPhi0 = cosPhi(w0);
        cosDeltaPhi = std::max(0.0f, cosPhiI * cosPhi0 + sinPhiI * sinPhi0);
    }

    return kd * (A + B * cosDeltaPhi * sinAlpha * tanBeta) / PI;
}

Vector3f OrenNayar::sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue)
{
    wi = CosineSampleHemisphere(randValue);
    pdf = PDF(w0, wi);

    return fr(w0, wi);
}

float OrenNayar::PDF(const Vector3f &w0, const Vector3f &wi)
{
    if (!SameHemisphere(w0, wi, Vector3f(0, 1, 0)))
    {
        return 0;
    }
    return CosineHemispherePdf(cosTheta(wi));
}

OrenNayar::~OrenNayar()
{
}

MicrofacetReflect::MicrofacetReflect(const Vector3f &_R, MicrofacetDistribution *_distribution, Fresnel *_fresnel) : BxDF(BxDFType(REFLECT | GLOSSY)), R(_R), fresnel(_fresnel), distribution(_distribution)
{
}

Vector3f MicrofacetReflect::sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue)
{
    Vector3f wh = distribution->Sample_wh(randValue, w0);
    wi = (2 * wh.dot(w0) * wh - w0).normalized();
    pdf = distribution->PDF(w0, wi, wh);

    return fr(w0, wi);
}

float MicrofacetReflect::PDF(const Vector3f &w0, const Vector3f &wi)
{
    Vector3f wh = (w0 + wi).normalized();
    return distribution->PDF(w0, wi, wh);
}

Vector3f MicrofacetReflect::fr(const Vector3f &w0, const Vector3f &wi)
{
    float costhetaI = abs(cosTheta(wi));
    float costheta0 = abs(cosTheta(w0));
    Vector3f wh = wi + w0;
    if (costheta0 == 0 || costhetaI == 0)
    {
        return Vector3f(0, 0, 0);
    }
    if (wh.isZero())
    {
        return Vector3f(0, 0, 0);
    }
    wh = wh.normalized();

    Vector3f fr = fresnel->Evaluate(wi.dot(wh));
    return R * fr * distribution->D(wh) * distribution->G(wi, w0) / (4 * costhetaI * costheta0);
}

MicrofacetReflect::~MicrofacetReflect()
{
}