#ifndef Intersection_H
#define Intersection_H

#include "../pbrt.hpp"

class Intersection
{
private:
    /* data */
public:
    Intersection(float tMax = 5000) : t1(tMax){};
    ~Intersection();

    Ray SpawnRay(const Intersection &p2);

    float t1;
    bool happen = false;

    Vector3f pos, norm, w0;
    Vector2f uv;

    BSDF *bsdf = NULL;
    Primitive *primitive = NULL;
};

Ray Intersection::SpawnRay(const Intersection &p2)
{
    Vector3f offset = this->norm * EPISILON + this->pos;
    Vector3f dir = (p2.pos - this->pos).normalized();
    Ray ray(offset, dir);
    return ray;
}

Intersection::~Intersection()
{
}

#endif