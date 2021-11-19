#ifndef PlasticMaterial_H
#define PlasticMaterial_H

#include "pbrt.hpp"
#include "Material.hpp"
#include "Microfacet.hpp"
#include "SurfaceInteraction.hpp"
#include "Lambertain.hpp"

class PlasticMaterial : public Material
{
private:
    /* data */
public:
    PlasticMaterial(const Vector3f &_R, const float &_etaI, const float &_etaT, const float _sigma);
    ~PlasticMaterial();

    void ComputeScatteringFunctions(SurfaceInteraction &interaction) override;

    Vector3f R;
    float etaI, etaT, sigma;
};

#endif