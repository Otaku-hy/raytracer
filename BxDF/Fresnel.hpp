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

    virtual float Evaluate(float costhetaI) = 0;
};

class FresnelDielectric : public Fresnel
{
private:
    /* data */
public:
    FresnelDielectric() = default;
    FresnelDielectric(float _etaI, float _etaT) : etaI(_etaI), etaT(_etaT){};
    ~FresnelDielectric();

    float Evaluate(float costhetaI) override;

    float etaI, etaT;
};

#endif