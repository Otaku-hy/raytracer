#include "Microfacet.hpp"

OrenNayar::OrenNayar(Vector3f _kd, float _sigma) : BxDF(BxDFType(REFLECT | DIFFUSE)), kd(_kd), sigma(_sigma)
{
    float rdSigma2 = radians(sigma) * radians(sigma);
    A = 1 - rdSigma2 / (2 * (rdSigma2 + 0.33f));
    B = 0.45 * rdSigma2 / (rdSigma2 + 0.09f);
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
    float jacobi = 1 / (4 * std::abs(w0.dot(wh)));
    return distribution->PDF(w0, wi, wh) * jacobi;
}

Vector3f MicrofacetReflect::fr(const Vector3f &w0, const Vector3f &wi)
{
    float costhetaI = std::abs(cosTheta(wi));
    float costheta0 = std::abs(cosTheta(w0));
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
    delete fresnel;
    delete distribution;
}

MicrofacetTransmission::MicrofacetTransmission(const Vector3f &_R, MicrofacetDistribution *_distribution, Fresnel *_fresnel) : BxDF(BxDFType(TRANSMISSION | GLOSSY)), R(_R), distribution(_distribution), fresnel(_fresnel)
{
}

Vector3f MicrofacetTransmission::fr(const Vector3f &w0, const Vector3f &wi)
{
    bool outing = w0.dot(Vector3f(0, 1, 0)) > 0 ? true : false;
    float etaT = outing ? fresnel->getEtaI()[0] : fresnel->getEtaT()[0];
    float etaI = outing ? fresnel->getEtaT()[0] : fresnel->getEtaI()[0];

    Vector3f wh = -(etaI * wi + etaT * w0).normalized();
    wh = wh.dot(Vector3f(0, 1, 0)) > 0 ? wh : -wh;

    if (SameHemisphere(w0, wi, wh))
    {
        return Vector3f(0, 0, 0);
    }

    float cosIh = wh.dot(wi);
    float cosOh = wh.dot(w0);

    float jacobi = etaT * etaT / (etaI * cosIh + etaT * cosOh) / (etaI * cosIh + etaT * cosOh);

    Vector3f tmpWi = wh.dot(wi) > 0 ? wi : -wi;
    Vector3f tmpWo = wh.dot(w0) > 0 ? w0 : -w0;

    Vector3f ft = Vector3f(1, 1, 1) - fresnel->Evaluate(wh.dot(wi));

    return std::abs(cosIh * cosOh / cosTheta(wi) / cosTheta(w0)) * ft * distribution->D(wh) * distribution->G(tmpWo, tmpWi) * jacobi;
}

Vector3f MicrofacetTransmission::sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue)
{
    bool outing = w0.dot(Vector3f(0, 1, 0)) > 0 ? true : false;
    float etaT = outing ? fresnel->getEtaI()[0] : fresnel->getEtaT()[0];
    float etaI = outing ? fresnel->getEtaT()[0] : fresnel->getEtaI()[0];

    Vector3f wh = distribution->Sample_wh(randValue, w0);
    wh = wh.dot(Vector3f(0, 1, 0)) > 0 ? wh : -wh;

    if (!Refract(w0, etaT, etaI, wh, wi))
    {
        return Vector3f(0, 0, 0);
    }

    Vector3f ft = Vector3f(1, 1, 1) - fresnel->Evaluate(wh.dot(wi));

    float cosIh = wh.dot(wi);
    float cosOh = wh.dot(w0);

    Vector3f tmpWi = wh.dot(wi) > 0 ? wi : -wi;
    Vector3f tmpWo = wh.dot(w0) > 0 ? w0 : -w0;

    float jacobi = etaT * etaT / (etaI * cosIh + etaT * cosOh) / (etaI * cosIh + etaT * cosOh);

    pdf = distribution->PDF(tmpWo, tmpWi, wh) * std::abs(cosOh) * jacobi;

    return std::abs(cosIh * cosOh / (cosTheta(wi) * cosTheta(w0))) * ft * distribution->D(wh) * distribution->G(tmpWo, tmpWi) * jacobi;
}

float MicrofacetTransmission::PDF(const Vector3f &w0, const Vector3f &wi)
{
    bool outing = w0.dot(Vector3f(0, 1, 0)) > 0 ? true : false;
    float etaT = outing ? fresnel->getEtaI()[0] : fresnel->getEtaT()[0];
    float etaI = outing ? fresnel->getEtaT()[0] : fresnel->getEtaI()[0];

    Vector3f wh = -(etaI * wi + etaT * w0).normalized();
    wh = wh.dot(Vector3f(0, 1, 0)) > 0 ? wh : -wh;

    if (SameHemisphere(w0, wi, wh))
    {
        return 0;
    }

    float cosIh = wh.dot(wi);
    float cosOh = wh.dot(w0);

    float jacobi = etaT * etaT * std::abs(cosOh) / (etaI * cosIh + etaT * cosOh) / (etaI * cosIh + etaT * cosOh);

    Vector3f tmpWi = wh.dot(wi) > 0 ? wi : -wi;
    Vector3f tmpWo = wh.dot(w0) > 0 ? w0 : -w0;

    return distribution->PDF(tmpWi, tmpWo, wh) * jacobi;
}

MicrofacetTransmission::~MicrofacetTransmission()
{
    delete fresnel;
    delete distribution;
}
