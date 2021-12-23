#include "GaussianFilter.hpp"

float GaussianFilter::Evaluate(const Vector2f &p)
{
    return Gaussian(p[0], expX) * Gaussian(p[1], expY);
}

float GaussianFilter::Gaussian(const float &x, const float &expX)
{
    return std::max(0.0f, float(std::exp(-alpha * x * x) - expX));
}

GaussianFilter::~GaussianFilter()
{
}