#include "MicrofacetDistribution.hpp"

MicrofacetDistribution::MicrofacetDistribution(/* args */)
{
}

MicrofacetDistribution::~MicrofacetDistribution()
{
}

//
float BeckmannDistribution::D(const Vector3f &wh)
{
    float tan2theta = tan2Theta(wh);
    if (std::isinf(tan2theta))
        return 0;
    float cos4theta = cos2Theta(wh) * cos2Theta(wh);
    return exp(-tan2theta / (alpha * alpha)) / (PI * alpha * alpha * cos4theta);
}

float BeckmannDistribution::lambda(const Vector3f &w)
{
    float absTanTheta = abs(tanTheta(w));
    if (std::isinf(absTanTheta))
        return 0;
    float a = 1 / (alpha * absTanTheta);
    if (a > 1.6)
        return 0;
    return (1 - 1.259f * a + 0.396f * a * a) / (3.535f * a + 2.181f * a * a);
}

float BeckmannDistribution::G(const Vector3f &w0, const Vector3f &wi)
{
    return 1 / (1 + lambda(w0) + lambda(wi));
}

float BeckmannDistribution::G1(const Vector3f &w0)
{
    return 1 / (1 + lambda(w0));
}

float BeckmannDistribution::PDF(const Vector3f &w0, const Vector3f &wh)
{
    return D(wh) * G1(w0) * std::max(0.0f, w0.dot(wh)) / abs(cosTheta(w0));
}

Vector3f BeckmannDistribution::Sample_wh(const Vector2f &randVal, const Vector3f &w0)
{
    float phi = 2 * PI * randVal[0];
    float tan2Theta = 0;
    if (!std::isinf(log(1 - randVal[1])))
    {
        tan2Theta = float(-alpha * alpha * log(1 - randVal[1]));
    }
    float cosTheta = std::sqrt(1 / (1 + tan2Theta));
    float sinTheta = std::sqrt(1 - cosTheta * cosTheta);
    Vector3f wh = SphericalDirection(sinTheta, cosTheta, phi);
    if (w0.dot(wh) < 0)
        wh = -wh;
    return wh;
}

BeckmannDistribution::~BeckmannDistribution()
{
}