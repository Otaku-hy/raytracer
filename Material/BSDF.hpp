#ifndef BSDF_H
#define BSDF_H

#include "pbrt.hpp"
#include "BxDF.hpp"
#include "Matrix4_4.hpp"
#include "SurfaceInteraction.hpp"

class BSDF
{
private:
    /* data */
public:
    BSDF(const SurfaceInteraction &interaction, std::shared_ptr<BxDF> _bxdf);
    BSDF(const SurfaceInteraction &interaction, std::vector<std::shared_ptr<BxDF>> _bxdfs);
    ~BSDF();

    int nBxDFs;
    Vector3f sn, gn; //shading normal; geometry normal
    Matrix4_4 worldTolocal;
    Matrix4_4 localToworld;
    std::vector<std::shared_ptr<BxDF>> bxdfs;

    void Add(std::shared_ptr<BxDF> bxdf);
    int NumMatchedBxDF(BxDFType type);
    Vector3f fr(const Vector3f &wW0, const Vector3f &wWi, BxDFType type);
    Vector3f sample_fr(const Vector3f &wW0, Vector3f &wWi, float &pdf, const Vector2f &randValue, BxDFType &type);
    float PDF(const Vector3f &wW0, const Vector3f &wWi, BxDFType type);
};

#endif