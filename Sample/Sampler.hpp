#ifndef Sampler_H
#define Sampler_H

#include "../pbrt.hpp"

using namespace Eigen;

class Sampler
{
private:
    /* data */
public:
    Sampler();
    Sampler(size_t _sampleNum, size_t _sampleDimension) : sampleNum(_sampleNum), sampleDimension(_sampleNum){};
    
    virtual ~Sampler();
    virtual Vector2f get2D() = 0;
    virtual float get1D() = 0;
    virtual void startSampler(Vector2f seed) = 0;
    virtual float getSample1D(const int& dimensionIndex,const int& sampleIndex) = 0;
    virtual Vector2f getSample2D(const int& dimensionIndex,const int& sampleIndex) = 0;

    size_t sampleNum;
    size_t sampleDimension;
    size_t currentSample;
};

#endif