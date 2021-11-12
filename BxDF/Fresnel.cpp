#include "Fresnel.hpp"

Fresnel::Fresnel(/* args */)
{
}

Fresnel::~Fresnel()
{
}


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