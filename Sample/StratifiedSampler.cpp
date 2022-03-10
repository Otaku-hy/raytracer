#include "StratifiedSampler.hpp"

void StratifiedSampler::startSampler(Vector2f seed, const std::string &sampler_name)
{
    currentPixel = Vector2i(seed[0], seed[1]);
    currentSample = 0;

    if (samplers1D_.find(sampler_name) != samplers1D_.end())
    {
        auto& sampler = getSampler1D(sampler_name);
        stratifiedSample1D(&sampler[0], xPixelSamples * yPixelSamples, jitterSamples);
        Shuffle(&sampler[0],xPixelSamples * yPixelSamples);
    }
    if (samplers2D_.find(sampler_name) != samplers2D_.end())
    {
        auto& sampler = getSampler2D(sampler_name);
        stratifiedSample2D(&sampler[0], xPixelSamples, yPixelSamples, jitterSamples);
        Shuffle(&sampler[0],xPixelSamples * yPixelSamples);
    }
}

void StratifiedSampler::stratifiedSample1D(float *sample, size_t nSize, bool jitter)
{
    for (int i = 0; i < nSize; i++)
    {
        float delta = jitter ? getRandom1D() : 0.5;
        *sample = (i + delta) / float(nSize);
        sample++;
    }
}

void StratifiedSampler::stratifiedSample2D(Vector2f *sample, size_t nx, size_t ny, bool jitter)
{
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            Vector2f delta = jitter ? getRandom2D() : Vector2f(0.5, 0.5);

            sample->x() = (i + delta[0]) / float(nx);
            sample->y() = (j + delta[1]) / float(ny);

            sample++;
        }
    }
}

StratifiedSampler::~StratifiedSampler()
{
}
