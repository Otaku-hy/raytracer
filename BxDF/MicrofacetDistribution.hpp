#ifndef MicrofacetDistribution_H
#define MicrofacetDistribution_H

#include "pbrt.hpp"

class MicrofacetDistribution
{
private:
    /* data */
public:
    MicrofacetDistribution();
    ~MicrofacetDistribution();

    virtual float D(const Vector3f &wh) = 0;
    virtual float lambda(const Vector3f &w) = 0;
    virtual float G(const Vector3f &w0, const Vector3f &wi) = 0;
    virtual float G1(const Vector3f &w0) = 0;

    virtual float PDF(const Vector3f &w0, const Vector3f &wh) = 0;
    virtual Vector3f Sample_wh(const Vector2f &randVal,const Vector3f& w0) = 0;
};

class BeckmannDistribution : public MicrofacetDistribution
{
private:
    /* data */
public:
    BeckmannDistribution(float sigma) { alpha = sqrt(2) * sigma; };
    ~BeckmannDistribution();

    float D(const Vector3f &wh) override;
    float lambda(const Vector3f &w) override;
    float G(const Vector3f &w0, const Vector3f &wi) override;
    float G1(const Vector3f &w0) override;

    float PDF(const Vector3f &w0, const Vector3f &wh) override;
    Vector3f Sample_wh(const Vector2f &randVal,const Vector3f& w0) override;

    float alpha;
};

#endif