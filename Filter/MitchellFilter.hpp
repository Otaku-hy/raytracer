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

#endif