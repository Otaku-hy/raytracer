#include "StratifiedSampler.hpp"

void StratifiedSampler::startSampler(Vector2f seed)
{
    currentPixel = Vector2i(seed[0], seed[1]);
    currentSample = 0;

    for (int i = 0; i < sample1DDimension; i++)
    {
        stratifiedSample1D(&samples1D[i][0], xPixelSamples * yPixelSamples, jitterSamples);
        Shuffle(&samples1D[0][0],xPixelSamples * yPixelSamples,i);
    }
    for (int i = 0; i < sample2DDimension; i++)
    {
        stratifiedSample2D(&samples2D[i][0], xPixelSamples, yPixelSamples, jitterSamples);
        Shuffle(&samples2D[0][0],xPixelSamples * yPixelSamples,i);
    }
}

void StratifiedSampler::stratifiedSample1D(float *sample, size_t nSize, bool jitter)
{
    for (int i = 0; i < nSize; i++)
    {
        float delta = jitter ? get1D() : 0.5;
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
            Vector2f delta = jitter ? get2D() : Vector2f(0.5, 0.5);

            sample->x() = (i + delta[0]) / float(nx);
            sample->y() = (j + delta[1]) / float(ny);

            sample++;
        }
    }
}

StratifiedSampler::~StratifiedSampler()
{
}
