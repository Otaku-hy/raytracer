#ifndef Sampler_H
#define Sampler_H

#include "pbrt.hpp"

using namespace Eigen;

class Sampler
{
private:
    /* data */
public:
    Sampler();
    Sampler(size_t _sampleNum) : sampleNum(_sampleNum){};

    virtual ~Sampler();
    virtual Vector2f getRandom2D() = 0;
    virtual float getRandom1D() = 0;
    virtual void startSampler(Vector2f seed,const std::string& sampler_name) = 0;

    virtual std::vector<float> &getSampler1D(const std::string &sampler_name) = 0;
    virtual std::vector<Vector2f> &getSampler2D(const std::string &sampler_name) = 0;

    virtual float getSample1D(const std::string &sampler_name, int sampleIndex) = 0;
    virtual Vector2f getSample2D(const std::string &sampler_name, int sampleIndex) = 0;

    size_t sampleNum;
    size_t currentSample;
};

#endif