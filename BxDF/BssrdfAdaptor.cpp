#include "BssrdfAdaptor.hpp"

Vector3f BssrdfAdaptor::fr(const Vector3f &w0, const Vector3f &wi)
{
    float ft = 1 - FrDielectric(wi.dot(Vector3f(0, 1, 0)), etaA, etaB);
    // std::cout << "ft: " << ft << std::endl;

    return Vector3f(ft, ft, ft);
}

Vector3f BssrdfAdaptor::sample_fr(const Vector3f &w0, Vector3f &wi, float &pdf, const Vector2f &randValue)
{
    wi = CosineSampleHemisphere(randValue);
    pdf = PDF(w0, wi);

    return fr(w0, wi);
}

float BssrdfAdaptor::PDF(const Vector3f &w0, const Vector3f &wi)
{
    if (!SameHemisphere(wi, Vector3f(0, 1, 0)))
    {
        // std::cout << "here" << std::endl;
        return 0;
    }
    return CosineHemispherePdf(cosTheta(wi));
}

BssrdfAdaptor::~BssrdfAdaptor()
{
}
