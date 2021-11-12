#ifndef SpecularBxDF_H
#define SpecularBxDF_H

#include "BxDF.hpp"
#include "Fresnel.hpp"

class SpecularReflection : public BxDF
{
private:
    /* data */
public:
    SpecularReflection() = default;
    SpecularReflection(Fresnel *_fresnel) : BxDF(BxDFType(SPECULAR | REFLECT)), fresnel(_fresnel){};
    ~SpecularReflection();

    Vector3f fr(const Vector3f &w0, const Vector3f &wi) override;
    Vector3f sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue) override;

    Fresnel *fresnel;
};

#endif