#ifndef BxDF_H
#define BxDF_H

#include "MonteCarloSamples.hpp"
#include "SphericalCoordFuncs.hpp"
#include "../lib/Eigen/Eigen"

using namespace Eigen;

enum BxDFType
{
    REFLECT = 1,
    TRANSMISSION = 1 << 1,
    DIFFUSE = 1 << 2,
    SPECULAR = 1 << 3,
    GLOSSY = 1 << 4,
};

class BxDF
{
private:
    /* data */
public:
    BxDF() = default;
    BxDF(BxDFType _type) : type(_type){};
    ~BxDF();

    // virtual Vector3f fr(const Vector3f& w0,const Vector3f &wi) = 0;
    virtual Vector3f sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue) = 0;
    virtual float PDF(const Vector3f &w0, const Vector3f &wi);

    bool CheckType(BxDFType type);

    BxDFType type;
};

bool BxDF::CheckType(BxDFType type)
{
    if (type == type)
    {
        return true;
    }
    return false;
}

BxDF::~BxDF()
{
}

#endif