#include "Microfacet.hpp"

OrenNayar::OrenNayar(Vector3f _kd, float _sigma) : kd(_kd), sigma(_sigma)
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
    return CosineHemispherePdf(cosTheta(wi));
}

OrenNayar::~OrenNayar()
{
}