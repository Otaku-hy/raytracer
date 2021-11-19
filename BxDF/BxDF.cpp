#include "BxDF.hpp"

bool BxDF::MatchType(BxDFType _type)
{
    if (type & _type)
        return true;
    else
        return false;
}

BxDF::~BxDF()
{
}