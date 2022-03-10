#ifndef StratifiedSampler_H
#define StratifiedSampler_H

#include "PixelSampler.hpp"

class StratifiedSampler : public PixelSampler
{
private:
    /* data */
public:
    StratifiedSampler() = default;
    StratifiedSampler(int _xPixelSamples, int _yPixelSamples, bool _jitterSamples) : xPixelSamples(_xPixelSamples), yPixelSamples(_yPixelSamples), PixelSampler(_xPixelSamples * _yPixelSamples), jitterSamples(_jitterSamples){};
    
    ~StratifiedSampler() override;
    void startSampler(Vector2f seed,const std::string& sampler_name) override;

    void stratifiedSample1D(float *sample, size_t nSize, bool jitter);
    void stratifiedSample2D(Vector2f *sample, size_t nx, size_t ny, bool jitter);

    int xPixelSamples, yPixelSamples;
    bool jitterSamples;
};

#endif