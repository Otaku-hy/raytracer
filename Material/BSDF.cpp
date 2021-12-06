#include "BSDF.hpp"

BSDF::BSDF(const SurfaceInteraction &interaction, std::shared_ptr<BxDF> _bxdf) : sn(interaction.norm), gn(Vector3f(0, 1, 0))
{
    worldTolocal = worldToShading(sn);
    localToworld = worldTolocal.inversed();
    bxdfs.push_back(_bxdf);
    nBxDFs = 1;
}

BSDF::BSDF(const SurfaceInteraction &interaction, std::vector<std::shared_ptr<BxDF>> _bxdfs) : sn(interaction.norm), gn(Vector3f(0, 1, 0)), bxdfs(_bxdfs)
{
    worldTolocal = worldToShading(sn);
    localToworld = worldTolocal.inversed();
    nBxDFs = bxdfs.size();
}

void BSDF::Add(std::shared_ptr<BxDF> bxdf)
{
    bxdfs.push_back(bxdf);
    nBxDFs++;
}

int BSDF::NumMatchedBxDF(BxDFType type)
{
    int cnt = 0;
    for (int i = 0; i < nBxDFs; i++)
    {
        if (bxdfs[i]->MatchType(type))
        {
            cnt++;
        }
    }
    return cnt;
}

Vector3f BSDF::fr(const Vector3f &wW0, const Vector3f &wWi, BxDFType type)
{
    bool reflect = wWi.dot(sn) * wW0.dot(sn) > 0 ? true : false;
    Vector3f wL0 = Vector4to3(worldTolocal * Vector3to4(wW0, NORM));
    Vector3f wLi = Vector4to3(worldTolocal * Vector3to4(wWi, NORM));
    Vector3f f(0, 0, 0);
    for (int i = 0; i < nBxDFs; i++)
    {
        if (reflect)
        {
            if (bxdfs[i]->MatchType(type))
            {
                f += bxdfs[i]->fr(wL0, wLi);
            }
        }
        else
        {
            if (bxdfs[i]->MatchType(type) && bxdfs[i]->MatchType(BxDFType(TRANSMISSION)))
            {
                f += bxdfs[i]->fr(wL0, wLi);
            }
        }
    }

    return f;
}

Vector3f BSDF::sample_fr(const Vector3f &wW0, Vector3f &wWi, float &pdf, const Vector2f &randValue, BxDFType &type)
{
    Vector3f fr(0, 0, 0);
    int matchedCnt = NumMatchedBxDF(type);
    if (matchedCnt == 0)
    {
        pdf = 0;
        return fr;
    }
    int randCnt = floor(randValue[0] * matchedCnt);
    int cnt = 0;
    if (randCnt == 0)
        randCnt++;

    std::shared_ptr<BxDF> bxdf;
    for (int i = 0; i < nBxDFs; i++)
    {
        if (bxdfs[i]->MatchType(type) && ++cnt == randCnt)
        {
            bxdf = bxdfs[i];
            break;
        }
    }

    type = bxdf->type;
    Vector3f wL0 = Vector4to3(worldTolocal * Vector3to4(wW0, NORM));
    Vector3f wLi;

    fr = bxdf->sample_fr(wL0, wLi, pdf, randValue);
    if (pdf == 0)
        return Vector3f(0, 0, 0);

    wWi = Vector4to3(localToworld * Vector3to4(wLi, NORM));

    if (!(type & SPECULAR) && matchedCnt > 1)
    {
        for (int i = 0; i < nBxDFs; i++)
        {
            if (bxdfs[i]->MatchType(type) && bxdfs[i] != bxdf)
            {
                pdf += bxdfs[i]->PDF(wL0, wLi);
                fr += bxdfs[i]->fr(wL0, wLi);
            }
        }
        pdf /= matchedCnt;
    }

    return fr;
}

float BSDF::PDF(const Vector3f &wW0, const Vector3f &wWi, BxDFType type)
{
    bool reflect = wWi.dot(sn) * wW0.dot(sn) > 0 ? true : false;
    Vector3f wL0 = Vector4to3(worldTolocal * Vector3to4(wW0, NORM));
    Vector3f wLi = Vector4to3(worldTolocal * Vector3to4(wWi, NORM));
    float pdf = 0;
    for (int i = 0; i < nBxDFs; i++)
    {
        if (reflect)
        {
            if (bxdfs[i]->MatchType(type))
            {
                pdf += bxdfs[i]->PDF(wLi, wL0);
            }
        }
        else
        {
            if (bxdfs[i]->MatchType(type) && bxdfs[i]->MatchType(BxDFType(TRANSMISSION)))
            {
                pdf += bxdfs[i]->PDF(wL0, wLi);
            }
        }
    }
    return pdf;
}

BSDF::~BSDF()
{
}