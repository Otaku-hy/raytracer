#ifndef MitchellFilter_H
#define MitchellFilter_H

#include "Filter.hpp"

class MitchellFilter : public Filter
{
private:
    /* data */
public:
    MitchellFilter() = default;
    MitchellFilter(Vector2f _radius, float _B, float _C) : Filter(_radius), B(_B), C(_C){};
    ~MitchellFilter();

    float Evaluate(const Vector2f &p) override;

    float Mitchell(float value);

    float B, C;
};

float MitchellFilter::Evaluate(const Vector2f &p)
{
    return Mitchell(2 * p[0] / radius[0]) * Mitchell(2 * p[1] / radius[1]);
}

float MitchellFilter::Mitchell(float value)
{
    value = abs(value);

    if (value > 1)
    {
        return 1 / 6.0f * ((-B - 6 * C) * pow(value, 3.0) + (6 * B + 30 * C) * pow(value, 2.0) + (-12 * B - 48 * C) * value + (8 * B + 24 * C));
    }
    else
    {
        return 1 / 6.0f * ((12 - 9 * B - 6 * C) * pow(value, 3.0) + (-18 + 12 * B + 6 * C) * pow(value, 2.0) + (6 - 2 * B));
    }
}

MitchellFilter::~MitchellFilter()
{
}

#endif