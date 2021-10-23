#ifndef AreaLight_H
#define AreaLight_H

#include <memory>

#include "Light.hpp"

#include "../Shape/Shapes.hpp"
#include "../Shape/Triangle.hpp"

class AreaLight : public Light
{
private:
    /* data */
public:
    AreaLight() = default;
    AreaLight(std::shared_ptr<Shapes> _shape, int _nSamples, Vector3f _Le) : Light(_nSamples, _Le), shape(_shape){};
    ~AreaLight();

    Vector3f sample_Li(const Vector2f &randVal, float &pdf, Vector3f &wi, const Intersection &ref) override;
    float Pdf_Li(const Vector3f &wi, const Intersection &ref) override;

    std::shared_ptr<Shapes> shape;
};

Vector3f AreaLight::sample_Li(const Vector2f &randVal, float &pdf, Vector3f &wi, const Intersection &ref)
{
    Vector3f posLi = shape->sampleShape(randVal);
    wi = (posLi - ref.pos).normalized();
    pdf = Pdf_Li(wi, ref);

    return L();
}

float AreaLight::Pdf_Li(const Vector3f &wi, const Intersection &ref)
{
    Ray ray(ref.pos, wi);
    float tHit;
    Intersection intersection_Li(5000);
    if (shape->intersect(ray, tHit, intersection_Li))
    {
        return distance(ref.pos, intersection_Li.pos) / (shape->surfaceArea() * abs(wi.dot(intersection_Li.norm)));
    }
    else
    {
        return 0;
    }
}

AreaLight::~AreaLight()
{
}

#endif