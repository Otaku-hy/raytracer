#ifndef Material_H
#define Material_H

#include "../pbrt.hpp"

class Material
{
private:
    /* data */
public:
    Material();
    
    virtual ~Material();
    virtual void ComputeScatteringFunctions(SurfaceInteraction& interaction) = 0;
};

#endif