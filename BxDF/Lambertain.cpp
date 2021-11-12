#include "Lambertain.hpp"

Vector3f Lambertain::sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue)
{
    wi = CosineSampleHemisphere(randValue);
    pdf = PDF(w0, wi);

    return kd / PI;
}

Vector3f Lambertain::fr(const Vector3f &w0, const Vector3f &wi)
{
    return kd / PI;
}

float Lambertain::PDF(const Vector3f &w0, const Vector3f &wi)
{
    return CosineHemispherePdf(cosTheta(wi));
}

Lambertain::~Lambertain()
{
}