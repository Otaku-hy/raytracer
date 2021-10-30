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

Fresnel::Fresnel(/* args */)
{
}

Fresnel::~Fresnel()
{
}

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

float FresnelDielectric::Evaluate(const Vector3f &w0)
{
    float cosThetaI = clamp(cosTheta(w0), -1, 1);

    float etaItmp = cosThetaI >= 0 ? etaI : etaT;
    float etaTtmp = cosThetaI >= 0 ? etaT : etaI;

    cosThetaI = abs(cosThetaI);

    float sinThetaI = sqrt(1 - cosThetaI * cosThetaI);
    float sinThetaT = etaItmp / etaTtmp * sinThetaI;

    if (sinThetaI >= 1)
        return 1;

    float cosThetaT = sqrt(1 - sinThetaT * sinThetaT);

    float rPallel = (etaTtmp * cosThetaI - etaItmp * cosThetaT) / (etaTtmp * cosThetaI - etaItmp * cosThetaT);
    float rVert = (etaItmp * cosThetaI - etaTtmp * cosThetaT) / (etaItmp * cosThetaI - etaTtmp * cosThetaT);

    return 0.5 * (rPallel * rPallel + rVert * rVert);
}

FresnelDielectric::~FresnelDielectric()
{
}

#endif