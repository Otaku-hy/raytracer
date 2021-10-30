#ifndef Visibility_H
#define Visibility_H

#include "../pbrt.hpp"
#include "../Scene/Scene.hpp"
#include "../SurfaceInteraction/Intersection.hpp"

class VisibilityTester
{
private:
    /* data */
public:
    VisibilityTester() = default;
    VisibilityTester(const Intersection &_p1, const Intersection &_p2) : p1(_p1), p2(_p2){};
    ~VisibilityTester();

    bool Occluded(const Scene &scene);

    Intersection p1, p2;
};

bool VisibilityTester::Occluded(const Scene &scene)
{
    Ray ray = p1.SpawnRay(p2);
    Intersection intersection(distance(ray.origin, p2.pos) - EPISILON);
    return scene.Intersect(ray, intersection);
}

VisibilityTester::~VisibilityTester()
{
}

#endif
