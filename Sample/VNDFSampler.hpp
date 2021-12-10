#ifndef VNDFSampler_H
#define VNDFSampler_H

#include "pbrt.hpp"

class VNDFSampler
{
private:
    /* data */
public:
    static Vector2f SampleInSlopeSpace(const Vector2f& randValue,const Vector3f& wo);
};


#endif
