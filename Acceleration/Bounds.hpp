#ifndef Bounds_H
#define Bounds_H

#include "pbrt.hpp"
#include "Ray.hpp"

using namespace Eigen;

struct Edges
{
    float a, b, c;
};

class Bound3D
{
private:
    /* data */
public:
    Bound3D() = default;
    Bound3D(Vector3f p);
    Bound3D(Vector3f _pMin, Vector3f _pMax);
    Bound3D(Vector3f _pMin, Edges _edges);
    Bound3D(const Bound3D &other);

    bool isInside(Vector3f p);
    Vector3f getCorner(size_t i);
    Bound3D intersectB(const Bound3D &other);
    bool IntersectP(Ray ray);

    size_t maxExtent();
    float surfaceArea();
    float volume();

    Vector3f offset(const Vector3f &p);

    ~Bound3D();

    Vector3f pMin = Vector3f(FLT_MAX, FLT_MAX, FLT_MAX), pMax = Vector3f(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    Edges edges;
};

Bound3D Union(const Bound3D &b, const Vector3f &p);
Bound3D Union(const Bound3D &b1, const Bound3D &b2);
Bound3D Union(const Vector3f &vec1, const Vector3f &vec2);

#endif