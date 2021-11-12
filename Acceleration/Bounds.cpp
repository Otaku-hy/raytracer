#include "Bounds.hpp"

Bound3D::Bound3D(Vector3f p)
{
    pMin = pMax = p;
}

Bound3D::Bound3D(Vector3f _pMin, Vector3f _pMax) : pMin(_pMin), pMax(_pMax)
{
    edges.a = pMax.x() - pMin.x();
    edges.b = pMax.y() - pMin.y();
    edges.c = pMax.z() - pMin.z();
};

Bound3D::Bound3D(Vector3f _pMin, Edges _edges) : pMin(_pMin), edges(_edges)
{
    pMax = pMin + Vector3f(edges.a, edges.b, edges.c);
};

Bound3D::~Bound3D()
{
}

bool Bound3D::isInside(Vector3f p)
{
    return (p.x() >= pMin.x() && p.x() <= pMax.x()) &&
           (p.y() >= pMin.y() && p.y() <= pMax.y()) &&
           (p.z() >= pMin.z() && p.z() <= pMax.z());
}

Vector3f Bound3D::getCorner(size_t i)
{
    return Vector3f((i % 2 == 0) ? pMin.x() : pMax.x(), (i < 4) ? pMin.y() : pMax.y(), (i & 2) ? pMax.z() : pMin.z());
}

Bound3D Bound3D::intersectB(const Bound3D &other)
{
    return (Vector3f(std::max(pMin.x(), other.pMin.x()), std::max(pMin.y(), other.pMin.y()), std::max(pMin.z(), other.pMin.z())),
            Vector3f(std::min(pMax.x(), other.pMax.x()), std::min(pMax.y(), other.pMax.y()), std::min(pMax.z(), other.pMax.z())));
}

size_t Bound3D::maxExtent()
{
    if (edges.a >= edges.b && edges.a >= edges.c)
        return 0;
    else if (edges.b >= edges.a && edges.b >= edges.c)
        return 1;
    else
        return 2;
}

float Bound3D::surfaceArea()
{
    return 2 * (edges.a * edges.b + edges.b * edges.c + edges.c * edges.a);
}

float Bound3D::volume()
{
    return edges.a * edges.b * edges.c;
}

Vector3f Bound3D::offset(const Vector3f &p)
{
    Vector3f o;
    o[0] = (p - pMin).x() / edges.a;
    o[1] = (p - pMin).y() / edges.b;
    o[2] = (p - pMin).z() / edges.c;
    return o;
}

bool Bound3D::IntersectP(Ray ray)
{
    float t0 = 0;
    float t1 = 5000;

    for (int i = 0; i < 3; i++)
    {
        float tmpTMin;
        float tmpTMax;
        if (ray.dir[i] == 0)
        {
            continue;
        }
        else if (ray.dir[i] > 0)
        {
            tmpTMin = (pMin[i] - ray.origin[i]) / ray.dir[i];
            tmpTMax = (pMax[i] - ray.origin[i]) / ray.dir[i];
        }
        else
        {
            tmpTMax = (pMin[i] - ray.origin[i]) / ray.dir[i];
            tmpTMin = (pMax[i] - ray.origin[i]) / ray.dir[i];
        }

        t0 = std::max(t0, tmpTMin);
        t1 = std::min(t1, tmpTMax);
    }

    if (t1 != 5000 && t0 <= t1)
    {
        return true;
    }
    return false;
}

Bound3D Union(const Bound3D &b1, const Bound3D &b2)
{
    return Bound3D(Vector3f(std::min(b1.pMin.x(), b2.pMin.x()), std::min(b1.pMin.y(), b2.pMin.y()), std::min(b1.pMin.z(), b2.pMin.z())),
                   Vector3f(std::max(b1.pMax.x(), b2.pMax.x()), std::max(b1.pMax.y(), b2.pMax.y()), std::max(b1.pMax.z(), b2.pMax.z())));
}

Bound3D Union(const Bound3D &b, Vector3f &p)
{
    return Bound3D(Vector3f(std::min(b.pMin.x(), p.x()), std::min(b.pMin.y(), p.y()), std::min(b.pMin.z(), p.z())),
                   Vector3f(std::max(b.pMax.x(), p.x()), std::max(b.pMax.y(), p.y()), std::max(b.pMax.z(), p.z())));
}
