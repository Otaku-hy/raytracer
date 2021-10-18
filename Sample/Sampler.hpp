#ifndef Sampler_H
#define Sampler_H

#include <vector>

#include "../lib/Eigen/Eigen"

using namespace Eigen;

class Sampler
{
private:
    /* data */
public:
    Sampler() = default;
    Sampler(size_t _sampleNum, size_t _sampleDimension) : sampleNum(_sampleNum), sampleDimension(_sampleNum){};
    ~Sampler();

    virtual Vector2f get2D() = 0;
    virtual float get1D() = 0;
    virtual void startSampler(Vector2f seed) = 0;

    size_t sampleNum;
    size_t sampleDimension;
    size_t currentSample;
};

Sampler::~Sampler()
{
}

#endif