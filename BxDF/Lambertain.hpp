#ifndef Lambertain_H
#define Lambertain_H

#include "BxDF.hpp"

class Lambertain : public BxDF
{
private:
    /* data */
public:
    Lambertain(const Vector3f &_kd = Vector3f(0, 0, 0)) : BxDF(BxDFType(REFLECT | DIFFUSE)), kd(_kd){};
    
    ~Lambertain() override;
    Vector3f fr(const Vector3f &w0, const Vector3f &wi) override;
    Vector3f sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue) override;
    float PDF(const Vector3f &w0, const Vector3f &wi) override;

    Vector3f kd;
};

#endif