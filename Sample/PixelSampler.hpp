#ifndef PixelSampler_H
#define PixelSampler_H

#include "Sampler.hpp"

class PixelSampler : public Sampler
{
private:
    /* data */
public:
    PixelSampler() = default;
    PixelSampler(size_t _sampleNum, size_t _sample1DDimension, size_t _sample2DDimension) : sample1DDimension(_sample1DDimension), sample2DDimension(_sample2DDimension), Sampler(_sampleNum, _sample1DDimension + 2 * _sample2DDimension)
    {
        for (int i = 0; i < sample1DDimension; i++)
        {
            samples1D.push_back(std::vector<float>(sampleNum));
        }
        for (int i = 0; i < sample2DDimension; i++)
        {
            samples2D.push_back(std::vector<Vector2f>(sampleNum));
        }
    };
    ~PixelSampler();

    Vector2f get2D() override;
    float get1D() override;

    void startSampler(Vector2f seed) override;

    float getSample1D(const int &dimensionIndex, const int &sampleIndex) override;
    Vector2f getSample2D(const int &dimensionIndex, const int &sampleIndex) override;

    Vector2i currentPixel;
    size_t sample1DDimension;
    size_t sample2DDimension;

    std::vector<std::vector<float>> samples1D;
    std::vector<std::vector<Vector2f>> samples2D;
};

#endif
