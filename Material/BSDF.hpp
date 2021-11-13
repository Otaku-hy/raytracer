#ifndef BSDF_H
#define BSDF_H

#include "../pbrt.hpp"
#include "../BxDF/BxDF.hpp"
#include "../Matrix4_4/Matrix4_4.hpp"
#include "../Interaction/SurfaceInteraction.hpp"

class BSDF
{
private:
    /* data */
public:
    BSDF(const SurfaceInteraction& interaction, std::shared_ptr<BxDF> _bxdf);
    ~BSDF();

    Vector3f sn, gn; //shading normal; geometry normal
    Matrix4_4 worldTolocal;
    Matrix4_4 localToworld;
    std::shared_ptr<BxDF> bxdf;

    Vector3f fr(const Vector3f &wW0, const Vector3f &wWi);
    Vector3f sample_fr(const Vector3f &wW0, Vector3f &wWi, float &pdf, const Vector2f &randValue);
    float PDF(const Vector3f &wW0, const Vector3f &wWi);
};

#endif