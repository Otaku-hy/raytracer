/* Since the computing method between the pdf of specularBxDF and other pdfs are different, we will
not use multiple importance sampling method where the bsdf applys specular component is used. 
*/

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
    SpecularReflection(Fresnel *_fresnel, Vector3f _R) : BxDF(BxDFType(SPECULAR | REFLECT)), fresnel(_fresnel), R(_R){};
    ~SpecularReflection();

    Vector3f fr(const Vector3f &w0, const Vector3f &wi) override;
    Vector3f sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue) override;
    float PDF(const Vector3f &w0, const Vector3f &wi) override;

    Fresnel *fresnel;
    Vector3f R;
};

class SpecularTransmission : public BxDF
{
private:
    /* data */
public:
    SpecularTransmission() = default;
    SpecularTransmission(Fresnel *_fresnel, float _etaA, float _etaB) : BxDF(BxDFType(SPECULAR | TRANSMISSION)), fresnel(_fresnel), etaA(_etaA), etaB(_etaB){};
    ~SpecularTransmission();

    Vector3f fr(const Vector3f &w0, const Vector3f &wi) override;
    Vector3f sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue) override;

    Fresnel *fresnel;
    float etaA, etaB;
};

#endif