#ifndef PixelSampler_H
#define PixelSampler_H

#include "Sampler.hpp"

class PixelSampler : public Sampler
{
private:
protected:
    std::map<std::string, std::vector<float>> samplers1D_;
    std::map<std::string, std::vector<Vector2f>> samplers2D_;

public:
    PixelSampler() = default;
    PixelSampler(size_t sample_num_per_pixel) : Sampler(sample_num_per_pixel),sample_num_per_pixel_(sample_num_per_pixel){};

    ~PixelSampler() override;
    Vector2f getRandom2D() override;
    float getRandom1D() override;

    void startSampler(Vector2f seed, const std::string &sampler_name) override;

    void AddSampler1D(const std::string &sampler_name);
    void AddSampler2D(const std::string &sampler_name);

    virtual std::vector<float> &getSampler1D(const std::string &sampler_name) override;
    virtual std::vector<Vector2f> &getSampler2D(const std::string &sampler_name) override;

    virtual float getSample1D(const std::string &sampler_name, int sampleIndex) override;
    virtual Vector2f getSample2D(const std::string &sampler_name, int sampleIndex) override;

    Vector2i currentPixel;
    size_t sample_num_per_pixel_;
};

#endif
