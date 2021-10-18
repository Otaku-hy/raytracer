#ifndef Shapes_H
#define Shapes_H

#include <memory>

#include "../Ray.hpp"
#include "../lib/Eigen/Eigen"
#include "../Intersection.hpp"
#include "../Acceleration/Bounds.hpp"
#include "../TransformMat/TransformMat.hpp"

using namespace Eigen;

class Shapes
{
private:
    /* data */
public:
    Shapes() = default;
    Shapes(std::shared_ptr<TransformMat> _OtoP,
           std::shared_ptr<TransformMat> _PtoO) : OtoP(_OtoP), PtoO(_PtoO){};
    ~Shapes();

    virtual bool intersect(Ray &ray, float &t1, Intersection &intersection) = 0;
    virtual float surfaceArea() = 0;
    virtual Bound3D genBoundingBox() = 0;

    std::shared_ptr<TransformMat> OtoP;
    std::shared_ptr<TransformMat> PtoO;
};

Shapes::~Shapes()
{
}

#endif