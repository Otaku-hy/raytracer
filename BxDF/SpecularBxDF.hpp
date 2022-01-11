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
    
    ~SpecularReflection() override;
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
    SpecularTransmission(Fresnel *_fresnel, const Vector3f& _R, float _etaA, float _etaB);
    //since we don't know the ray direction in BxDF, so we use etaA,etaB to represent the refract ratio out/in the material
    
    ~SpecularTransmission() override;
    Vector3f fr(const Vector3f &w0, const Vector3f &wi) override;
    Vector3f sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue) override;
    float PDF(const Vector3f &w0, const Vector3f &wi) override;

    Fresnel *fresnel;
    float etaA, etaB;
    Vector3f R;
};

#endif