#ifndef Fresnel_H
#define Fresnel_H

#include "../lib/Eigen/Eigen"
#include "../Utils/SphericalCoordFuncs.hpp"

using namespace Eigen;

class Fresnel
{
private:
    /* data */
public:
    Fresnel();
    ~Fresnel();

    virtual float Evaluate(const Vector3f &w0) = 0;
};

class FresnelDielectric : public Fresnel
{
private:
    /* data */
public:
    FresnelDielectric() = default;
    FresnelDielectric(float _etaI, float _etaT) : etaI(_etaI), etaT(_etaT){};
    ~FresnelDielectric();

    float Evaluate(const Vector3f &w0) override;

    float etaI, etaT;
};

#endif