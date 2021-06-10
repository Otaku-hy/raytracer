#ifndef Triangle_H
#define Triangle_H
#include "Object.hpp"
#include <vector>

class Triangle : public Object
{
private:
    /* data */
public:
    Vector3f v0, v1, v2;
    Vector2f t0, t1, t1;
    Vector3f n0, n1, n2;
    Vector3f e1, e2;

    float area;
    Material *material;

    Triangle() = default;
    Triangle(Vector3f _v0, Vector3f _v1, Vector3f _v2, Material *_material) : v0(_v0), v1(_v1), v2(_v2), material(_material)
    {
        e1 = v1 - v0;
        e2 = v2 - v0;

        area = e1.cross(e2).norm() / 2.0;
    }
    ~Triangle();

    float getArea();
    bool hasEmit();
    bool ray_intersection(Ray ray, float &t1);
    void computeIntersection();
};

Triangle::~Triangle()
{
}

float Triangle::getArea()
{
    return area;
}

bool Triangle::hasEmit()
{
    return material->hasEmission();
}

bool Triangle::ray_intersection(Ray ray, float &t1)
{
    Matrix3f A0;
    A0 << e1.x(), e2.x(), -ray.dir.x(),
        e1.y(), e2.y(), -ray.dir.y(),
        e1.z(), e2.z(), -ray.dir.z();

    Matrix3f A1;
    A1 << e2.x(), -ray.dir.x(), ray.origin.x(),
        e2.y(), -ray.dir.y(), ray.origin.y(),
        e2.z(), -ray.dir.z(), ray.origin.z();

    Matrix3f A2;
    A2 << e1.x(), -ray.dir.x(), ray.origin.x(),
        e1.y(), -ray.dir.y(), ray.origin.y(),
        e1.z(), -ray.dir.z(), ray.origin.z();

    Matrix3f A3;
    A3 << e1.x(), e2.x(), ray.origin.x(),
        e1.y(), e2.y(), ray.origin.y(),
        e1.z(), e2.z(), ray.origin.z(),

        t1 = A3.determinant() / A0.determinant();

    if (t1 < 0)
        return false;

    return true;
}

void Triangle::computeIntersection()
{
}

#endif