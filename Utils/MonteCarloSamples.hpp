#ifndef MonteCarloSample_H
#define MonteCarloSample_H

#include "Utils.hpp"

#include "../lib/Eigen/Eigen"

using namespace Eigen;

#define minClampContrib 0.1

Vector3f UniformSampleHemisphere(const Vector2f &randValue)
{
    float phi = 2 * PI * randValue[1];
    float z = randValue[0];
    float r = std::sqrt(std::max(0.0, 1.0 - z * z));
    return Vector3f(cos(phi) * r, z, sin(phi) * r);
}

float UniformHemispherePdf()
{
    return 1 / (2 * PI);
}
/* UniformSampleHemisphere Functions*/

Vector3f UniformSampleSphere(const Vector2f &randValue)
{
    float phi = 2 * PI * randValue[1];
    float z = 1 - 2 * randValue[0];
    float r = std::sqrt(std::max(0.0, 1.0 - z * z));
    return Vector3f(cos(phi) * r, z, sin(phi) * r);
}

float UniformSpherePdf()
{
    return 1 / (4 * PI);
}
/* UniformSampleSphere Functions*/

Vector2f UniformSampleDisk(const Vector2f &randValue)
{
    float r = sqrt(randValue[0]);
    float theta = 2 * PI * randValue[1];
    return Vector2f(r * cos(theta), r * sin(theta));
}

float UniformDiskPdf()
{
    return 1 / PI;
}
/* UniformSampleDisk Functions*/

Vector3f CosineSampleHemisphere(const Vector2f &randValue)
{
    float phi = 2 * PI * randValue[1];
    float r = sqrt(randValue[0]);
    float z = sqrt(std::max(0.0f, 1 - randValue[0]));
    return Vector3f(r * cos(phi), z, r * sin(phi));
}

float CosineHemispherePdf(float cosTheta)
{
    return cosTheta / PI;
}
// CosineSampleHemisphere Functions

Vector3f UniformSampleCone(const Vector3f &randValue, float cosThetaMax)
{
    float phi = 2 * PI * randValue[1];
    float z = 1 - randValue[0] + randValue[0] * cosThetaMax;
    float r = sqrt(std::max(0.0f, 1 - z * z));
    return Vector3f(r * cos(phi), z, r * sin(phi));
}

float UnifomrConePdf(float cosThetaMax)
{
    return 1 / (2 * PI * (1 - cosThetaMax));
}
/* UniformSampleCone Functions */

float RussianRoulette(float contrib)
{
    return std::min(1.0, contrib / minClampContrib);
}

float BalanceHeuristic(int nf, float fPdf, int ng, float gPdf)
{
    return nf * fPdf / (nf * fPdf + ng * gPdf);
}

float PowerHeuristic(int nf, float fPdf, int ng, float gPdf)
{
    return (nf * fPdf) * (nf * fPdf) / ((nf * fPdf + ng * gPdf) * (nf * fPdf + ng * gPdf));
}

// multiple importance sampling
#endif