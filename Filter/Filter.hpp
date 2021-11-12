#ifndef Filter_H
#define Filter_H

#include "../lib/Eigen/Eigen"

using namespace Eigen;

class Filter
{
private:
    /* data */
public:
    Filter() = default;
    Filter(Vector2f _radius) : radius(_radius){};
    ~Filter();

    virtual float Evaluate(const Vector2f &p) = 0;

    Vector2f radius;
};

#endif