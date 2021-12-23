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
    float absTanTheta = std::abs(tanTheta(w));
    if (std::isinf(absTanTheta))
        return 0;
    float a = 1 / (alpha * absTanTheta);
    if (a > 1.6)
        return 0;
    return (1 - 1.259f * a + 0.396f * a * a) / (3.535f * a + 2.181f * a * a);
}

float BeckmannDistribution::G(const Vector3f &w0, const Vector3f &wi)
{
    Vector3f wh = (w0 + wi).normalized();
    if (wh.dot(w0) < 0 || wh.dot(wi) < 0)
    {
        return 0;
    }

    return 1 / (1 + lambda(w0) + lambda(wi));
}

float BeckmannDistribution::G1(const Vector3f &w0, const Vector3f &wh)
{
    if (wh.dot(w0) < 0)
        return 0;

    return 1 / (1 + lambda(w0));
}

float BeckmannDistribution::PDF(const Vector3f &w0, const Vector3f &wi, const Vector3f &wh)
{
    return D(wh) * G1(w0, wh) * w0.dot(wh) / std::abs(cosTheta(w0));
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
    float tan2ThetaW = tan2Theta(w);
    if (std::isinf(tan2ThetaW))
    {
        return 0;
    }

    return (std::sqrt(1 + alphaG * alphaG * tan2ThetaW) - 1) / 2.0;
}

float GGXDistribution::G(const Vector3f &w0, const Vector3f &wi)
{
    Vector3f wh = (w0 + wi).normalized();
    if (wh.dot(wi) < 0 || wh.dot(w0) < 0)
    {
        return 0;
    }

    float sinDphi = sinTheta(w0) * cosTheta(wi) - cosTheta(w0) * sinTheta(wi);
    float dphi = std::asin(sinDphi);
    if (dphi < 0)
        dphi = -dphi;
    float lambdaPhi = 4.41 * dphi / (4.41 * dphi + 1);

    float lambdaO = lambda(w0);
    float lambdaI = lambda(wi);
    float maxLambda = lambdaO > lambdaI ? lambdaO : lambdaI;
    float minLambda = lambdaO > lambdaI ? lambdaI : lambdaO;

    return 1 / (1 + maxLambda + lambdaPhi * w0.dot(wi) * minLambda);
}

float GGXDistribution::G1(const Vector3f &w0, const Vector3f &wh)
{
    if (w0.dot(wh) < 0)
    {
        return 0;
    }

    return 1 / (1 + lambda(w0));
}

float GGXDistribution::PDF(const Vector3f &w0, const Vector3f &wi, const Vector3f &wh)
{
    return D(wh) * G1(w0, wh) * w0.dot(wh) / std::abs(cosTheta(w0));
}

Vector3f GGXDistribution::Sample_wh(const Vector2f &randVal, const Vector3f &w0)
{
    // float thetaHv = std::atan(alphaG * sqrt(randVal[0]) / sqrt(1 - randVal[0]));
    // float phiHv = 2 * PI * randVal[1];

    // Vector3f whT = Vector3f(std::sin(thetaHv) * cos(phiHv), std::cos(thetaHv), std::sin(thetaHv) * sin(phiHv));
    // whT = whT.normalized();

    // if (whT.dot(w0) < 0)
    //     whT = -whT;

    // return wh;

    Vector2f slopeRand = VNDFSampler::SampleInSlopeSpace(randVal, w0);

    float phi = 2 * PI * randVal[1];

    Matrix2f rotate;
    rotate << std::cos(phi), -std::sin(phi),
        std::sin(phi), std::cos(phi);

    slopeRand = rotate * slopeRand;
    slopeRand = alphaG * slopeRand;

    float scale = std::sqrt(slopeRand[0] * slopeRand[0] + slopeRand[1] * slopeRand[1] + 1);

    Vector3f wh = Vector3f(-slopeRand[0], 1, -slopeRand[1]) / scale;
    if (wh.dot(w0) < 0)
    {
        wh = -wh;
    }

    return wh;
}

GGXDistribution::~GGXDistribution()
{
}