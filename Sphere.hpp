#ifndef Sphere_H
#define Sphere_H
#include "Object.hpp"

class Sphere : public Object
{
private:
    /* data */
public:
    Sphere(Vector3f _center, float _radius, Material *_material);
    ~Sphere();

    bool ray_intersection(Ray ray, float &t1);
    void computeIntersection(Intersection &intersection, float t, Ray ray);
    float getArea();
    bool hasEmit();

    float radius;
    float area;
    Vector3f center;
    Material *material;
};

Sphere::Sphere(Vector3f _center, float _radius, Material *_material)
{
    center = _center;
    radius = _radius;
    material = _material;
    area = 4 * PI * radius * radius;
}

Sphere::~Sphere()
{
}

bool Sphere::ray_intersection(Ray ray, float &t1)
{
    float dir_2 = ray.dir.dot(ray.dir);
    Vector3f RtoC = ray.origin - center;
    float delta = ray.dir.dot(RtoC) * ray.dir.dot(RtoC) - dir_2 * (RtoC.dot(RtoC) - pow(radius, 2));

    if (delta < 0)
        return false;

    t1 = (-ray.dir.dot(RtoC) - sqrt(delta)) / dir_2;
    float t2 = (-ray.dir.dot(RtoC) + sqrt(delta)) / dir_2;

    if (t1 < 0)
        t1 = t2;
    if (t1 < 0)
        return false;

    return true;
}

void Sphere::computeIntersection(Intersection &intersection, float t, Ray ray)
{
    intersection.pos = ray.origin + ray.dir * t;

    Vector3f norm = (intersection.pos - center).normalized();
    intersection.norm = norm;

    intersection.material = material;

    intersection.happen = true;
}

float Sphere::getArea()
{
    return area;
}

bool Sphere::hasEmit()
{
    return material->hasEmission();
}

#endif