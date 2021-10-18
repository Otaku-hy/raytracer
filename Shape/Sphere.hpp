#ifndef Sphere_H
#define Sphere_H

#include <cmath>
#include <memory>

#include "Shapes.hpp"

#include "../Utils.hpp"

class Sphere : public Shapes
{
private:
    /* data */
public:
    Sphere(Vector3f center, float radius);
    ~Sphere();

    bool intersect(Ray &ray, float &t1, Intersection &intersection) override;
    float surfaceArea() override;
    Bound3D genBoundingBox() override;

    Vector3f center;
    float r;
};

Sphere::Sphere(Vector3f center, float radius) : center(center), r(radius)
{
    Matrix4f mat = Matrix4f::Identity();
    mat(0,3) = center[0];
    mat(1,3) = center[1];
    mat(2,3) = center[2];
    
    OtoP = std::make_shared<TransformMat>(mat);
    PtoO = std::make_shared<TransformMat>(mat.inverse());
}

bool Sphere::intersect(Ray &ray, float &t1, Intersection &intersection)
{
    Vector3f origin = PtoO->trans(ray.origin,Pos);
    Vector3f dir = PtoO->trans(ray.dir,Norm);

    float a = dir.x() * dir.x() + dir.y() * dir.y() + dir.z() * dir.z();
    float b = 2 * (dir.x() * origin.x() + dir.y() * origin.y() + dir.z() * origin.z());
    float c = origin.x() * origin.x() + origin.y() * origin.y() + origin.z() * origin.z() - r * r;

    float delta = b * b - 4 * a * c;

    if (delta < 0)
        return false;

    float t1Tmp = (-b - std::sqrt(delta)) / (2 * a);
    float t2Tmp = (-b + std::sqrt(delta)) / (2 * a);

    if (t1Tmp < 0)
        t1Tmp = t2Tmp;
    if (t1Tmp < 0 || t1Tmp > ray.tMax)
        return false;

    t1 = t1Tmp;

    if (t1 < intersection.t1)
    {
        intersection.t1 = t1;
        intersection.happen = true;
        intersection.pos = origin + t1 * dir;
        intersection.pos = OtoP->trans(intersection.pos,Pos);
        intersection.norm = (intersection.pos - center).normalized();

        return true;
    }
    else
    {
        return false;
    }
}

float Sphere::surfaceArea()
{
    return 4 * PI * r * r;
}

Bound3D Sphere::genBoundingBox()
{
    return Bound3D(Vector3f(center.x() - r, center.y() - r, center.z() - r), Vector3f(center.x() + r, center.y() + r, center.z() + r));
}

Sphere::~Sphere()
{
}

#endif