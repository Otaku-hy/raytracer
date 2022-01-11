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
    
    ~BoxFilter() override;
    float Evaluate(const Vector2f &p) override;
};

class TriangleFilter : public Filter
{
private:
    /* data */
public:
    TriangleFilter() = default;
    TriangleFilter(Vector2f _radius) : Filter(_radius){};
    
    ~TriangleFilter() override;
    float Evaluate(const Vector2f &p) override;
};

#endif