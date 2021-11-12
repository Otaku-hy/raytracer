#ifndef Interaction_H
#define Interaction_H

#include "pbrt.hpp"
#include "Ray.hpp"

class Interaction
{
private:
    /* data */
public:
    Interaction(float _t1 = 5000) : t1(_t1){};
    ~Interaction();

    Ray SpawnRay(const Interaction &p2);
    Ray SpawnRay(const Vector3f &direction);
    bool IsSurfaceInteraction();

    float t1;
    bool happen = false;

    Vector3f pos, norm, w0;
    Vector2f uv;
};

#endif