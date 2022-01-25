#ifndef Shapes_H
#define Shapes_H

#include "pbrt.hpp"

using namespace Eigen;

class Shapes
{
private:
    /* data */
protected:
    std::shared_ptr<Matrix4_4> OtoP;
    std::shared_ptr<Matrix4_4> PtoO;
public:
    Shapes();
    Shapes(std::shared_ptr<Matrix4_4> _OtoP,
           std::shared_ptr<Matrix4_4> _PtoO) : OtoP(_OtoP), PtoO(_PtoO){};
 
    virtual ~Shapes();
    virtual bool Intersect(const Ray &ray, float &t1, SurfaceInteraction &interaction) = 0;
    virtual bool IntersectP(Ray &ray) = 0;

    virtual float surfaceArea() = 0;
    virtual Bound3D genBoundingBox() = 0;

    virtual Interaction SampleShape(Vector2f randVal, const Interaction &ref) = 0;
    virtual float ShapePdf(const Vector3f &wi, const Interaction &ref) = 0;
};

#endif