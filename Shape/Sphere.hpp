#ifndef Sphere_H
#define Sphere_H

#include "Shapes.hpp"
#include "Ray.hpp"
#include "../Acceleration/Bounds.hpp"
#include "../Matrix4_4/Matrix4_4.hpp"
#include "../Interaction/SurfaceInteraction.hpp"

class Sphere : public Shapes
{
private:
    /* data */
public:
    Sphere(Vector3f center, float radius);
    ~Sphere();

    bool Intersect(const Ray &ray, float &t1, SurfaceInteraction &interaction) override;
    bool IntersectP(Ray &ray) override;
    
    float surfaceArea() override;
    Bound3D genBoundingBox() override;

    Vector3f center;
    float r;
};

#endif