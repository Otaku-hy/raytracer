#include "Visibility.hpp"

VisibilityTester::VisibilityTester(const Interaction &_p1, const Interaction &_p2)
{
    p1 = _p1;
    p2 = _p2;
};

bool VisibilityTester::Occluded(const Scene &scene)
{
    Ray ray = p1.SpawnRay(p2);
    return scene.IntersectP(ray);
}

VisibilityTester::~VisibilityTester()
{
}