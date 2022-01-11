#ifndef Light_H
#define Light_H

#include "../pbrt.hpp"
#include "../Matrix4_4/Matrix4_4.hpp"
#include "../Interaction/Interaction.hpp"
#include "Visibility.hpp"

using namespace Eigen;

class Light
{
public:
    Light();
    Light(int _nSamples, Vector3f _Le) : nSamples(_nSamples), Lemit(_Le){};

    virtual ~Light();
    virtual Vector3f sample_Li(const Vector2f &randVal, float &pdf, Vector3f &wi, const Interaction &ref, VisibilityTester *visibility) = 0;
    virtual float Pdf_Li(const Vector3f &wi, const Interaction &ref) = 0; // pdf in per unit solid angle

    Vector3f Le(const Interaction &itLight, const Vector3f &wi);

    int nSamples = 1;
    Vector3f Lemit;
    Matrix4_4 lightToWorld;

private:
};

#endif