#ifndef StratifiedSampler_H
#define StratifiedSampler_H

#include "PixelSampler.hpp"

class StratifiedSampler : public PixelSampler
{
private:
    /* data */
public:
    StratifiedSampler() = default;
    StratifiedSampler(int _xPixelSamples, int _yPixelSamples, size_t _sample1DDimension, size_t _sample2DDimension, bool _jitterSamples) : xPixelSamples(_xPixelSamples), yPixelSamples(_yPixelSamples), PixelSampler(_xPixelSamples * _yPixelSamples, _sample1DDimension, _sample2DDimension), jitterSamples(_jitterSamples){};
    ~StratifiedSampler();

    void startSampler(Vector2f seed) override;

    void stratifiedSample1D(float *sample, size_t nSize, bool jitter);
    void stratifiedSample2D(Vector2f *sample, size_t nx, size_t ny, bool jitter);

    int xPixelSamples, yPixelSamples;
    bool jitterSamples;
};

#endif