#ifndef GPrimitive_H
#define GPrimitive_H

#include <memory>

#include "Primitive.hpp"

class GeometryPrimitive : public Primitive
{
private:
    /* data */
public:
    GeometryPrimitive() = default;
    GeometryPrimitive(std::shared_ptr<Shapes> _shape,
                      std::shared_ptr<Material> _material,
                      std::shared_ptr<AreaLight> _light) : shape(_shape), material(_material), light(_light){};

    ~GeometryPrimitive();

    bool intersect(Ray &ray, Intersection &intersection) override;
    Material *getMaterial() override;
    AreaLight *getAreaLight() override;
    Bound3D worldBound() override;

    std::shared_ptr<Shapes> shape;
    std::shared_ptr<Material> material;
    std::shared_ptr<AreaLight> light;
};

bool GeometryPrimitive::intersect(Ray &ray, Intersection &intersection)
{
    float tHit;
    if (!shape->intersect(ray, tHit, intersection))
        return false;
    intersection.primitive = this;
    return true;
}

Material *GeometryPrimitive::getMaterial()
{
    return material.get();
}

AreaLight *GeometryPrimitive::getAreaLight()
{
    return light.get();
}

Bound3D GeometryPrimitive::worldBound()
{
    return shape->genBoundingBox();
}

GeometryPrimitive::~GeometryPrimitive()
{
}

#endif