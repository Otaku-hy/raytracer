#ifndef SurfaceInteraction_H
#define SurfaceInteraction_H

#include "../pbrt.hpp"
#include "Interaction.hpp"
#include "../Light/AreaLight.hpp"
#include "../Primitive/Primitive.hpp"
#include "../Material/BSDF.hpp"

class SurfaceInteraction : public Interaction
{
private:
    /* data */
public:
    SurfaceInteraction(float _t1 = 5000, BSDF *_bsdf = NULL, Primitive *_primitive = NULL) : Interaction(_t1), bsdf(_bsdf), primitive(_primitive){};
    ~SurfaceInteraction();

    Vector3f Le(Vector3f wi);

    BSDF *bsdf;
    Primitive *primitive;
};

#endif