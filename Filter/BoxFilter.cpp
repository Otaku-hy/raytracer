#include "BoxFilter.hpp"

float BoxFilter::Evaluate(const Vector2f &p)
{
    return 1.0;
}

BoxFilter::~BoxFilter()
{
}

float TriangleFilter::Evaluate(const Vector2f &p)
{
    return std::max(0.0f, abs(p[0])) * std::max(0.0f, abs(p[1]));
}

TriangleFilter::~TriangleFilter()
{
}