#ifndef Metal_H
#define Metal_H

#include "pbrt.hpp"
#include "Material.hpp"
#include "Fresnel.hpp"
#include "Microfacet.hpp"
#include "SurfaceInteraction.hpp"

class Metal : public Material
{
private:
    /* data */
public:
    Metal() = default;
    Metal(const Vector3f &_R, const Vector3f &_etaI, const Vector3f &_etaT, const Vector3f &_k,const float& _sigma);
    ~Metal();

    void ComputeScatteringFunctions(SurfaceInteraction &interaction) override;

    Vector3f R, etaI, etaT, k;
    float sigma;
};

#endif