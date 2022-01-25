#ifndef GPrimitive_H
#define GPrimitive_H

#include "Primitive.hpp"
#include "Shapes.hpp"
#include "Matrix4_4.hpp"
#include "Bounds.hpp"
#include "Material.hpp"
#include "SurfaceInteraction.hpp"

class GeometryPrimitive : public Primitive
{
private:
    /* data */
public:
    GeometryPrimitive() = default;
    GeometryPrimitive(std::shared_ptr<Shapes> _shape,
                       std::shared_ptr<Material> _material, std::shared_ptr<AreaLight> _light) : shape(_shape), material(_material), light(_light){};

    ~GeometryPrimitive() override;
    bool Intersect(const Ray &ray, SurfaceInteraction &interaction) override;
    bool IntersectP(Ray &ray) override;

    Material *getMaterial() override;
    AreaLight *getAreaLight() override;
    Bound3D worldBound() override;

    std::shared_ptr<Shapes> shape;
    std::shared_ptr<Material> material;
    std::shared_ptr<AreaLight> light;
};

#endif