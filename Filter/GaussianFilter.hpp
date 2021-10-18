#ifndef GaussianFilter_H
#define GaussianFilter_H

#include "Filter.hpp"

class GaussianFilter : public Filter
{
private:
    /* data */
public:
    GaussianFilter() = default;
    GaussianFilter(Vector2f _radius, float _alpha) : Filter(_radius), alpha(_alpha)
    {
        expX = std::exp(-alpha * radius[0] * radius[0]);
        expY = std::exp(-alpha * radius[1] * radius[1]);
    };
    ~GaussianFilter();

    float Evaluate(const Vector2f &p) override;

    float Gaussian(const float &x, const float &expX);

    float alpha, expX, expY;
};

float GaussianFilter::Evaluate(const Vector2f &p)
{
    return Gaussian(p[0], expX) * Gaussian(p[1], expY);
}

float GaussianFilter::Gaussian(const float &x, const float &expX)
{
    return std::max(0.0f, float(exp(-alpha * x * x) - expX));
}

GaussianFilter::~GaussianFilter()
{
}

#endif