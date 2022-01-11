#ifndef SubsurfaceMaterial_H
#define SubsurfaceMaterial_H

#include "pbrt.hpp"
#include "Material.hpp"
#include "BxDF.hpp"
#include "BSDF.hpp"
#include "BSSRDF.hpp"
#include "BssrdfAdaptor.hpp"
#include "SurfaceInteraction.hpp"

class SubsurfaceMaterial : public Material
{
private:
    /* data */
public:
    SubsurfaceMaterial(float _etaA, float _etaB, float _sigma_s, float _sigma_a, float _A, float _Radius);
    
    ~SubsurfaceMaterial() override;
    void ComputeScatteringFunctions(SurfaceInteraction &interaction) override;

    float etaA,etaB;
    float sigma_s,sigma_a,A;
    float Radius;
};

#endif