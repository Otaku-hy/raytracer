#ifndef Lambertain_H
#define Lambertain_H

#include "BxDF.hpp"

class Lambertain : public BxDF
{
private:
    /* data */
public:
    Lambertain() : BxDF(BxDFType(REFLECT | DIFFUSE)){};
    ~Lambertain();

    Vector3f sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue) override;
    float PDF(const Vector3f &w0, const Vector3f &wi) override;
};

Vector3f Lambertain::sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue)
{
    wi = CosineSampleHemisphere(randValue);
    pdf = PDF(w0, wi);

    return Vector3f(1 / PI);
}

float Lambertain::PDF(const Vector3f &w0, const Vector3f &wi)
{
    return CosineHemispherePdf(cosTheta(wi));
}

Lambertain::~Lambertain()
{
}

#endif