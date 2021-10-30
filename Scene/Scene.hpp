#ifndef Scene_H
#define Scene_H

#include "../Ray.hpp"
#include "../pbrt.hpp"
#include "../Acceleration/BVHAccel.hpp"

class Scene
{
private:
    /* data */
public:
    Scene(std::shared_ptr<BVHAccel> _BVH, std::vector<std::shared_ptr<Light>> _lights) : BVH(_BVH), lights(_lights){};
    ~Scene();

    bool Intersect(Ray &ray, Intersection &intersection) const;

    std::vector<std::shared_ptr<Light>> lights;
    std::shared_ptr<BVHAccel> BVH;
};

bool Scene::Intersect(Ray &ray, Intersection &intersection) const
{
    return BVH->intersect(ray, intersection);
}

Scene::~Scene()
{
}

#endif