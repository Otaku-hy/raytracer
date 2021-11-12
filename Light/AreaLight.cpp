#include "AreaLight.hpp"

Vector3f AreaLight::sample_Li(const Vector2f &randVal, float &pdf, Vector3f &wi, const Interaction &ref, VisibilityTester *visibility)
{
    Interaction itLi = shape->SampleShape(randVal, ref);
    *visibility = VisibilityTester(ref, itLi);
    wi = (itLi.pos - ref.pos).normalized();

    pdf = Pdf_Li(wi, ref);
    return Le(itLi, -wi);
}

float AreaLight::Pdf_Li(const Vector3f &wi, const Interaction &ref)
{
    return shape->ShapePdf(wi, ref);
}

AreaLight::~AreaLight()
{
}