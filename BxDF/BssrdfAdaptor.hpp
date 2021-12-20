#ifndef BssrdfAdaptor_H
#define BssrdfAdaptor_H

#include "pbrt.hpp"
#include "BxDF.hpp"

class BssrdfAdaptor : public BxDF
{
private:
    /* data */
public:
    BssrdfAdaptor(float _etaA, float _etaB) : BxDF(BxDFType(DIFFUSE | REFLECT | TEST)), etaA(_etaA), etaB(_etaB){};
    ~BssrdfAdaptor();

    float etaA, etaB;

    Vector3f fr(const Vector3f &w0, const Vector3f &wi) override;
    Vector3f sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue) override;
    float PDF(const Vector3f &w0, const Vector3f &wi) override;
};

#endif