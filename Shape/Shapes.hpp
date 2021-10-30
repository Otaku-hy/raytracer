#ifndef Shapes_H
#define Shapes_H

#include "../pbrt.hpp"
#include "../Ray.hpp"
#include "../Acceleration/Bounds.hpp"
#include "../Matrix4_4/Matrix4_4.hpp"
#include "../SurfaceInteraction/Intersection.hpp"

using namespace Eigen;

class Shapes
{
private:
    /* data */
public:
    Shapes() = default;
    Shapes(std::shared_ptr<Matrix4_4> _OtoP,
           std::shared_ptr<Matrix4_4> _PtoO) : OtoP(_OtoP), PtoO(_PtoO){};
    ~Shapes();

    virtual bool intersect(Ray &ray, float &t1, Intersection &intersection) = 0;
    virtual float surfaceArea() = 0;
    virtual Bound3D genBoundingBox() = 0;
    virtual Vector3f sampleShape(Vector2f randVal) = 0;
    virtual float ShapePdf() = 0;

    std::shared_ptr<Matrix4_4> OtoP;
    std::shared_ptr<Matrix4_4> PtoO;
};

Shapes::~Shapes()
{
}

#endif