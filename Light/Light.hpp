#ifndef Light_H
#define Light_H

#include "../lib/Eigen/Eigen"
#include "../Intersection.hpp"
#include "../Matrix4_4/Matrix4_4.hpp"

using namespace Eigen;

class Light
{
public:
    Light() = default;
    Light(int _nSamples, Vector3f _Le) : nSamples(_nSamples), Le(_Le){};
    ~Light();

    virtual Vector3f sample_Li(const Vector2f &randVal, float &pdf, Vector3f &wi, const Intersection &ref) = 0;
    virtual float Pdf_Li(const Vector3f &wi, const Intersection &ref)= 0; // pdf in per unit solid angle

    // bool VisibilityTest();
    Vector3f L();

    int nSamples = 1;
    Vector3f Le;
    Matrix4_4 lightToWorld;

private:
};

// bool Light::VisibilityTest()
// {
// }

Vector3f Light::L()
{
    return Le;
}

Light::~Light()
{
}

#endif