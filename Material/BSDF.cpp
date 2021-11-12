#include "BSDF.hpp"

BSDF::BSDF(const SurfaceInteraction &interaction, std::shared_ptr<BxDF> _bxdf) : sn(interaction.norm), gn(Vector3f(0, 1, 0)), bxdf(_bxdf)
{
    worldTolocal = worldToShading(sn);
    localToworld = worldTolocal.inversed();
}

Vector3f BSDF::fr(const Vector3f &wW0, const Vector3f &wWi)
{
    bool reflect = wWi.dot(sn) * wW0.dot(sn) > 0 ? true : false;
    Vector3f wL0 = Vector4to3(worldTolocal * Vector3to4(wW0, NORM));
    Vector3f wLi = Vector4to3(worldTolocal * Vector3to4(wWi, NORM));
    Vector3f f(0, 0, 0);
    if (reflect)
        f = bxdf->fr(wL0, wLi);

    return f;
}

Vector3f BSDF::sample_fr(const Vector3f &wW0, Vector3f &wWi, float &pdf, const Vector2f &randValue)
{
    Vector3f wL0 = Vector4to3(worldTolocal * Vector3to4(wW0, NORM));
    Vector3f wLi;
    Vector3f fr = bxdf->sample_fr(wL0, wLi, pdf, randValue);
    wWi = Vector4to3(localToworld * Vector3to4(wLi, NORM));
    return fr;
}

float BSDF::PDF(const Vector3f &wW0, const Vector3f &wWi)
{
    Vector3f wL0 = Vector4to3(worldTolocal * Vector3to4(wW0, NORM));
    Vector3f wLi = Vector4to3(worldTolocal * Vector3to4(wWi, NORM));
    return bxdf->PDF(wL0, wLi);
}

BSDF::~BSDF()
{
}