#ifndef Microfacet_H
#define Microfacet_H

#include "pbrt.hpp"
#include "BxDF.hpp"

class OrenNayar : public BxDF
{
private:
    /* data */
public:
    OrenNayar(Vector3f _kd, float sigma = 20.0);
    ~OrenNayar();

    Vector3f fr(const Vector3f &w0, const Vector3f &wi) override;
    Vector3f sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue) override;
    float PDF(const Vector3f &w0, const Vector3f &wi) override;

    float sigma; //alos the roughness   the input form is degree
    float A, B;

    Vector3f kd;
};

#endif