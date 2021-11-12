#include "BxDF.hpp"

bool BxDF::CheckType(BxDFType _type)
{
    if (type == _type)
    {
        return true;
    }
    return false;
}

BxDF::~BxDF()
{
}