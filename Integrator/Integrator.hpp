#ifndef Integrator_H
#define Integrator_H

#include "../pbrt.hpp"

class Integrator
{
private:
    /* data */
public:
    Integrator(/* args */);
    ~Integrator();

    virtual void Render(const Scene& scene) = 0;
};

#endif