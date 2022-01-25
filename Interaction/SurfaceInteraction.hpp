#ifndef SurfaceInteraction_H
#define SurfaceInteraction_H

#include "pbrt.hpp"
#include "Interaction.hpp"
#include "AreaLight.hpp"
#include "Primitive.hpp"
#include "BSDF.hpp"
#include "BSSRDF.hpp"

class SurfaceInteraction : public Interaction
{
private:
    /* data */
public:
    SurfaceInteraction(float _t1 = 5000, BSDF *_bsdf = NULL, Primitive *_primitive = NULL,BSSRDF *_bssrdf= NULL) : Interaction(_t1), bsdf(_bsdf), primitive(_primitive) , bssrdf(_bssrdf){};
    
    ~SurfaceInteraction() override;

    Vector3f Le(Vector3f wi);

    BSDF *bsdf;
    BSSRDF* bssrdf;
    Primitive *primitive;
};

#endif