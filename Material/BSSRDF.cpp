#include "BSSRDF.hpp"

BSSRDF::BSSRDF(const SurfaceInteraction &_ito, float _etaA, float _etaB, float _sigma_s, float _sigma_a, float _A, float _Radius) : sn(_ito.norm), gn(Vector3f(0, 1, 0)), ito(_ito), etaA(_etaA), etaB(_etaB), sigma_a(_sigma_a), sigma_s(_sigma_s), A(_A), Radius(_Radius)
{
    worldTolocal = worldToShading(sn);
    localToworld = worldTolocal.inversed();
    mfp = 1.0 / (sigma_s + sigma_a);
    s = 1.85 - A + 7 * std::abs(A - 0.8) * std::abs(A - 0.8) * std::abs(A - 0.8);
}

float BSSRDF::R(float r)
{
    if (r == 0)
        return 0;
    // std::cout << r << " " << A * s * (exp(-s * r) + exp(-s * r / 3.0)) / (8 * PI * r) << std::endl;
    return A * s * (exp(-s * r / mfp) + exp(-s * r / (3.0 * mfp))) / (8 * PI * r) / (mfp * mfp);
}

Vector3f BSSRDF::S(const SurfaceInteraction &iti, const Vector3f &wi)
{
    float ft = 1 - FrDielectric(ito.w0.dot(ito.norm), etaA, etaB);
    // std::cout << ft << " ";
    return Vector3f(ft, ft, ft) * R(distance(ito.pos, iti.pos)) / PI;
}

Vector3f BSSRDF::Sample_S(const Scene &scene, const Vector3f &w0, SurfaceInteraction &iti, float &pdf, const Vector2f &randValue)
{
    float u = (randValue[0] + 0.05) * 20;
    int u0 = std::floor(u);
    if (u0 == 20)
        u0--;
    int u1 = std::ceil(u);
    if (u1 == 20)
        u1--;

    float r = cdfTable[u0] + (u - u0) * (cdfTable[u1] - cdfTable[u0]);
    float d = mfp / s;
    r = r / d;
    // std::cout << r <<" ";

    float phi = 2 * PI * randValue[1];

    Vector3f rPoff = r * Vector3f(cos(phi), 0, sin(phi));
    // rPoff = r * Vector4to3(localToworld * Vector3to4(rPoff, NORM));

    float h = std::sqrt(Radius * Radius - r * r);
    Vector3f rVoff = -Vector3f(0, 1, 0) * (Radius - h);
    // std::cout << r << " " << Radius - h << " ";
    Vector3f dr = (rVoff + rPoff).normalized();
    dr = Vector4to3(localToworld * Vector3to4(dr, NORM));
    if (dr.dot(ito.norm) > 0)
    {
        dr = -dr;
    }
    Ray ray = ito.SpawnRay(dr);

    if (!scene.Intersect(ray, iti))
    {
        std::cout << "!" << std::endl;
    }

    std::shared_ptr<BxDF> bxdf = std::make_shared<BssrdfAdaptor>(etaA, etaB);
    iti.bsdf = new BSDF(iti, bxdf);

    pdf = PDF(iti, Vector3f(0, 0, 0));
    // std::cout << S(iti, Vector3f(0, 0, 0))<<" "<<pdf <<std::endl;
    return S(iti, Vector3f(0, 0, 0));
}

float BSSRDF::PDF(const SurfaceInteraction &iti, const Vector3f &wi)
{
    float d = mfp / s;
    float r = distance(iti.pos, ito.pos);
    if (std::isinf(r))
    {
        return 0;
    }
    float pdf = (exp(-r / d) + exp(-r / (3 * d))) / (8 * PI * d * r);

    return pdf;
}

BSSRDF::~BSSRDF()
{
}