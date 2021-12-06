#ifndef Fresnel_H
#define Fresnel_H

#include "../lib/Eigen/Eigen"
#include <iostream>
#include "../Utils/SphericalCoordFuncs.hpp"

using namespace Eigen;

class Fresnel
{
private:
    /* data */
public:
    Fresnel();
    ~Fresnel();

    virtual Vector3f Evaluate(float costhetaI) = 0;
};

class FresnelDielectric : public Fresnel
{
private:
    /* data */
public:
    FresnelDielectric() = default;
    FresnelDielectric(float _etaI, float _etaT) : etaI(_etaI), etaT(_etaT){};
    ~FresnelDielectric();

    Vector3f Evaluate(float costhetaI) override;

    float etaI, etaT;
};

class FresnelConductor : public Fresnel
{
private:
public:
    FresnelConductor() = default;
    FresnelConductor(const Vector3f &_etaI, const Vector3f &_etaT, const Vector3f &_k);
    ~FresnelConductor();

    Vector3f Evaluate(float costhetaI) override;

    Vector3f etaI, etaT, k;
};

#endif