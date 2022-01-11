#ifndef Microfacet_H
#define Microfacet_H

#include "pbrt.hpp"
#include "BxDF.hpp"
#include "Fresnel.hpp"
#include "MicrofacetDistribution.hpp"

class OrenNayar : public BxDF
{
private:
    /* data */
public:
    OrenNayar(Vector3f _kd, float sigma = 20.0);
    
    ~OrenNayar() override;
    Vector3f fr(const Vector3f &w0, const Vector3f &wi) override;
    Vector3f sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue) override;
    float PDF(const Vector3f &w0, const Vector3f &wi) override;

    float sigma; //alos the roughness   the input form is degree
    float A, B;

    Vector3f kd;
};

class MicrofacetReflect : public BxDF
{
private:
    /* data */
public:
    MicrofacetReflect(const Vector3f& _R,MicrofacetDistribution* _distribution,Fresnel* _fresnel);
    
    ~MicrofacetReflect() override;
    Vector3f fr(const Vector3f &w0, const Vector3f &wi) override;
    Vector3f sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue) override;
    float PDF(const Vector3f &w0, const Vector3f &wi) override;

    Vector3f R;
    Fresnel *fresnel;
    MicrofacetDistribution *distribution;
};

class MicrofacetTransmission : public BxDF
{
private:
    /* data */
public:
    MicrofacetTransmission(const Vector3f& _R,MicrofacetDistribution* _distribution,Fresnel* _fresnel);
    
    ~MicrofacetTransmission() override;
    Vector3f fr(const Vector3f &w0, const Vector3f &wi) override;
    Vector3f sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue) override;
    float PDF(const Vector3f &w0, const Vector3f &wi) override;

    Vector3f R;
    Fresnel *fresnel;
    MicrofacetDistribution *distribution;
};


#endif