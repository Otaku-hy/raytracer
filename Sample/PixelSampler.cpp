#include "PixelSampler.hpp"

Vector2f PixelSampler::get2D()
{
    return Vector2f(rand() % 100 / 100.0, rand() % 100 / 100.0);
}

float PixelSampler::get1D()
{
    return rand() % 100 / 100.0;
}

void PixelSampler::startSampler(Vector2f seed)
{
    currentPixel = Vector2i(seed[0], seed[1]);
    currentSample = 0;

    for (int i = 0; i < sampleNum; i++)
    {
        for (int j = 0; j < sample2DDimension; j++)
        {
            samples2D[j][i] = get2D();
        }
        for (int j = 0; j < sample1DDimension; j++)
        {
            samples1D[j][i] = get1D();
        }
    }
}

float PixelSampler::getSample1D(const int &dimensionIndex, const int &sampleIndex)
{
    return samples1D[dimensionIndex][sampleIndex];
}

Vector2f PixelSampler::getSample2D(const int &dimensionIndex, const int &sampleIndex)
{
    return samples2D[dimensionIndex][sampleIndex];
}

PixelSampler::~PixelSampler()
{
}