#include "MitchellFilter.hpp"

float MitchellFilter::Evaluate(const Vector2f &p)
{
    return Mitchell(2 * p[0] / radius[0]) * Mitchell(2 * p[1] / radius[1]);
}

float MitchellFilter::Mitchell(float value)
{
    value = std::abs(value);

    if (value > 1)
    {
        return 1 / 6.0f * ((-B - 6 * C) * std::pow(value, 3.0) + (6 * B + 30 * C) * std::pow(value, 2.0) + (-12 * B - 48 * C) * value + (8 * B + 24 * C));
    }
    else
    {
        return 1 / 6.0f * ((12 - 9 * B - 6 * C) * std::pow(value, 3.0) + (-18 + 12 * B + 6 * C) * std::pow(value, 2.0) + (6 - 2 * B));
    }
}

MitchellFilter::~MitchellFilter()
{
}
