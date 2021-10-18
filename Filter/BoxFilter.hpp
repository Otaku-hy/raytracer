#ifndef BoxFilter_H
#define BoxFilter_H

#include "Filter.hpp"

class BoxFilter : public Filter
{
private:
    /* data */
public:
    BoxFilter() = default;
    BoxFilter(Vector2f _radius) : Filter(_radius){};
    ~BoxFilter();

    float Evaluate(const Vector2f &p) override;
};

float BoxFilter::Evaluate(const Vector2f &p)
{
    return 1.0;
}

class TriangleFilter : public Filter
{
private:
    /* data */
public:
    TriangleFilter() = default;
    TriangleFilter(Vector2f _radius) : Filter(_radius){};
    ~TriangleFilter();

    float Evaluate(const Vector2f &p) override;
};

float TriangleFilter::Evaluate(const Vector2f &p)
{
    return std::max(0.0f, abs(p[0])) * std::max(0.0f, abs(p[1]));
}

TriangleFilter::~TriangleFilter()
{
}

#endif