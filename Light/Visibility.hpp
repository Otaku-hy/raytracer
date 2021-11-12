#ifndef Visibility_H
#define Visibility_H

#include "../pbrt.hpp"
#include "../Scene/Scene.hpp"
#include "../Interaction/Interaction.hpp"

class VisibilityTester
{
private:
    /* data */
public:
    VisibilityTester() = default;
    VisibilityTester(const Interaction &_p1, const Interaction &_p2);
    ~VisibilityTester();

    bool Occluded(const Scene &scene);

    Interaction p1, p2;
};

#endif
