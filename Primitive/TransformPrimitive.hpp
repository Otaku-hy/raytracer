#ifndef TransformPrimitive_H
#define TransformPrimitive_H

#include "Primitive.hpp"
#include "../Shape/Shapes.hpp"
#include "../Matrix4_4/Matrix4_4.hpp"
#include "../Acceleration/Bounds.hpp"
#include "../Material/Material.hpp"
#include "../Interaction/SurfaceInteraction.hpp"

class TransformPrimitive : public Primitive
{
private:
    /* data */
public:
    TransformPrimitive() = default;
    TransformPrimitive(std::shared_ptr<Matrix4_4> _WtoP,
                       std::shared_ptr<Matrix4_4> _PtoW,
                       std::shared_ptr<Primitive> _primitive) : WtoP(_WtoP), PtoW(_PtoW), primitive(_primitive){};
    
    ~TransformPrimitive() override;
    bool Intersect(const Ray &ray, SurfaceInteraction &interaction) override;
    bool IntersectP(Ray &ray) override;

    AreaLight *getAreaLight() override;
    Material *getMaterial() override;
    Bound3D worldBound() override;

    std::shared_ptr<Matrix4_4> WtoP;
    std::shared_ptr<Matrix4_4> PtoW;
    std::shared_ptr<Primitive> primitive;
};

#endif
