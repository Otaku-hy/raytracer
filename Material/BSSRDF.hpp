#ifndef BSSRDF_H
#define BSSRDF_H

#include "pbrt.hpp"
#include "SurfaceInteraction.hpp"
#include "Fresnel.hpp"
#include "Scene.hpp"
#include "BxDF.hpp"
#include "BssrdfAdaptor.hpp"
#include "BSDF.hpp"

class BSSRDF
{
private:
    /* data */
public:
    BSSRDF(const SurfaceInteraction &_ito, float _etaA, float _etaB, float _sigma_s, float _sigma_a, float _A, float _Radius);
    ~BSSRDF();

    Vector3f sn, gn; //shading normal; geometry normal
    Matrix4_4 worldTolocal;
    Matrix4_4 localToworld;
    float etaA, etaB;

    float sigma_s, sigma_a;
    float mfp, A, s;
    float Radius;

    const SurfaceInteraction &ito;

    Vector3f S(const SurfaceInteraction &iti, const Vector3f &wi);
    Vector3f Sample_S(const Scene &scene, const Vector3f &w0, SurfaceInteraction &iti, float &pdf, const Vector2f &randValue);
    float PDF(const SurfaceInteraction &iti, const Vector3f &wi);

    float R(float r);
};

#endif