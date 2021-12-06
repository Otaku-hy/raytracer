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

float BeckmannDistribution::lambda(const Vector3f &w) //smith G
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
    float lambda0, lambdaI;
    lambda0 = lambda(w0);
    lambdaI = lambda(wi);

    return 1 / (1 + lambda0 + lambdaI);
}

float BeckmannDistribution::G1(const Vector3f &w0, const Vector3f &wh)
{
    return 1 / (1 + lambda(w0));
}

float BeckmannDistribution::PDF(const Vector3f &w0, const Vector3f &wi, const Vector3f &wh)
{
    if (w0.dot(wh) < 0)
        return 0;
    return D(wh) * G(w0, wh) * w0.dot(wh) / (abs(cosTheta(w0)) * 4 * w0.dot(wh));
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

float GGXDistribution::D(const Vector3f &wh)
{
    if (wh.dot(Vector3f(0, 1, 0)) < 0)
        return 0;

    float tan2ThetaH = tan2Theta(wh);
    if (std::isinf(tan2ThetaH))
        return 0;

    float cos4ThetaH = cos2Theta(wh) * cos2Theta(wh);
    float alphaG2 = alphaG * alphaG;

    return alphaG2 / (PI * cos4ThetaH * (alphaG2 + tan2ThetaH) * (alphaG2 + tan2ThetaH));
}

float GGXDistribution::lambda(const Vector3f &w)
{
    return 0;
}
/* in GGX model, we do not use lambda function to represent the percentage of inviisilible microfacet
around the inifinitsimal area, but use the approximation that G = G1(w0) * G1(wi)
*/

float GGXDistribution::G(const Vector3f &w0, const Vector3f &wi)
{
    Vector3f wh = (w0 + wi).normalized();
    float g0 = G1(w0, wh);
    float gi = G1(wi, wh);

    return g0 * gi;
}

float GGXDistribution::G1(const Vector3f &w0, const Vector3f &wh)
{
    if (w0.dot(wh) * w0.dot(Vector3f(0, 1, 0)) < 0)
    {
        return 0;
    }
    float tan2ThetaV = tan2Theta(w0);
    if (std::isinf(tan2ThetaV))
    {
        return 0;
    }

    return 2.0 / (1 + sqrt(1 + alphaG * alphaG * tan2ThetaV));
}

float GGXDistribution::PDF(const Vector3f &w0, const Vector3f &wi, const Vector3f &wh)
{
    float p = 1 / 4 * w0.dot(wh);
    if (p < 0)
        return 0;
    return D(wh) * G(w0, wi) * w0.dot(wh) / abs(cosTheta(w0)) * p;
}

Vector3f GGXDistribution::Sample_wh(const Vector2f &randVal, const Vector3f &w0)
{
    float thetaHv = std::atan(alphaG * sqrt(randVal[0]) / sqrt(1 - randVal[0]));
    float phiHv = 2 * PI * randVal[1];

    Vector3f wh = Vector3f(std::sin(thetaHv) * cos(phiHv), std::cos(thetaHv), std::sin(thetaHv) * sin(phiHv));
    wh = wh.normalized();

    if (wh.dot(w0) < 0)
        wh = -wh;

    return wh;
}

GGXDistribution::~GGXDistribution()
{
}