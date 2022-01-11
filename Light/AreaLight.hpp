#ifndef AreaLight_H
#define AreaLight_H

#include "../pbrt.hpp"
#include "Light.hpp"
#include "../Shape/Shapes.hpp"

class AreaLight : public Light
{
private:
    /* data */
public:
    AreaLight() = default;
    AreaLight(std::shared_ptr<Shapes> _shape, int _nSamples, Vector3f _Le) : Light(_nSamples, _Le), shape(_shape){};
    
    ~AreaLight() override;
    Vector3f sample_Li(const Vector2f &randVal, float &pdf, Vector3f &wi, const Interaction &ref, VisibilityTester *visibility) override;
    float Pdf_Li(const Vector3f &wi, const Interaction &ref) override;

    std::shared_ptr<Shapes> shape;
};

#endif