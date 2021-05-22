#ifndef Object_H
#define Object_H

#include "lib/Eigen/Eigen"
#include "Ray.hpp"
#include "Material.hpp"

using namespace Eigen;

enum ObjectType
{
    plane,
    sphere
};

class Intersection
{
private:
    /* data */
public:
    Intersection(Vector3f _pos, Vector3f _norm, Material *_material);
    ~Intersection();

    Vector3f pos;
    Vector3f norm;
    Material *material;
};

Intersection::Intersection(Vector3f _pos, Vector3f _norm, Material *_material)
{
    pos = _pos;
    norm = _norm;
    material = _material;
}

Intersection::~Intersection()
{
}

class Object
{
private:
    /* data */
public:
    Object(/* args */);
    ~Object();

    ObjectType type;
};

Object::Object(/* args */)
{
}

Object::~Object()
{
}

class Plane : public Object
{
private:
    /* data */
public:
    Plane(Vector3f _pos, Vector3f _norm, Material *_material, ObjectType _type);
    ~Plane();

    bool ray_intersection(Ray ray, float &t1);

    Vector3f pos;
    Vector3f norm;
    Material *material;
};

Plane::Plane(Vector3f _pos, Vector3f _norm, Material *_material, ObjectType _type)
{
    pos = _pos;
    norm = _norm;
    material = _material;
    type = _type;
}

Plane::~Plane()
{
}

bool Plane::ray_intersection(Ray ray, float &t1)
{
    t1 = (pos.y() - ray.origin.y()) / ray.dir.y();
}

class Sphere : public Object
{
private:
    /* data */
public:
    Sphere(Vector3f _center, float _radius, Material *_material, ObjectType _type);
    ~Sphere();

    Vector3f center;
    float radius;
    Material *material;

    bool ray_intersection(Ray ray, float &t1);
};

Sphere::Sphere(Vector3f _center, float _radius, Material *_material, ObjectType _type)
{
    center = _center;
    radius = _radius;
    material = _material;
    type = _type;
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

#endif