#include "PixelSampler.hpp"

Vector2f PixelSampler::getRandom2D()
{
    return Vector2f(rand() % 100 / 100.0, rand() % 100 / 100.0);
}

float PixelSampler::getRandom1D()
{
    return rand() % 100 / 100.0;
}

void PixelSampler::AddSampler1D(const std::string &sampler_name)
{
    std::vector<float> samplers(sample_num_per_pixel_);
    samplers1D_.insert(std::pair<std::string, std::vector<float>>(sampler_name, samplers));
}

void PixelSampler::AddSampler2D(const std::string &sampler_name)
{
    std::vector<Vector2f> samplers(sample_num_per_pixel_);
    samplers2D_.insert(std::pair<std::string, std::vector<Vector2f>>(sampler_name, samplers));
}

void PixelSampler::startSampler(Vector2f seed, const std::string &sampler_name)
{
    currentPixel = Vector2i(seed[0], seed[1]);
    currentSample = 0;

    if (samplers1D_.find(sampler_name) != samplers1D_.end())
    {
        auto &sampler = getSampler1D(sampler_name);
        for (int i = 0; i < sample_num_per_pixel_; i++)
        {
            sampler[i] = getRandom1D();
        }
    }
    if (samplers2D_.find(sampler_name) != samplers2D_.end())
    {
        auto &sampler = getSampler2D(sampler_name);
        for (int i = 0; i < sample_num_per_pixel_; i++)
        {
            sampler[i] = getRandom2D();
        }
    }
}

std::vector<float> &PixelSampler::getSampler1D(const std::string &sampler_name)
{
    return samplers1D_.find(sampler_name)->second;
}

std::vector<Vector2f> &PixelSampler::getSampler2D(const std::string &sampler_name)
{
    return samplers2D_.find(sampler_name)->second;
}

float PixelSampler::getSample1D(const std::string &sampler_name, int sampleIndex)
{
    return getSampler1D(sampler_name)[sampleIndex];
}

Vector2f PixelSampler::getSample2D(const std::string &sampler_name, int sampleIndex)
{
    return getSampler2D(sampler_name)[sampleIndex];
}

PixelSampler::~PixelSampler()
{
}