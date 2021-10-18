#ifndef BxDF_H
#define BxDF_H

enum BxDFType
{
    DIFFUSE,
    SPECULAR,
    GLOSSY;
};

class BxDF
{
private:
    /* data */
public:
    BxDF() = default;
    BxDF(BxDFType _type) : type(_type);
    ~BxDF();

    BxDFType type;
};

BxDF::~BxDF()
{
}

#endif