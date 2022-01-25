#ifndef Visibility_H
#define Visibility_H

#include "pbrt.hpp"
#include "Scene.hpp"
#include "Interaction.hpp"

class VisibilityTester
{
private:
    Interaction p1, p2;

public:
    VisibilityTester() = default;
    VisibilityTester(const Interaction &_p1, const Interaction &_p2);
    ~VisibilityTester();

    bool Occluded(const Scene &scene);

};

#endif
