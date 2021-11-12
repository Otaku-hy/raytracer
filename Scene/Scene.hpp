#ifndef Scene_H
#define Scene_H

#include "../pbrt.hpp"
#include "Ray.hpp"
#include "../Acceleration/BVHAccel.hpp"

class Scene
{
private:
    /* data */
public:
    Scene(std::shared_ptr<BVHAccel> _BVH, std::vector<std::shared_ptr<Light>> _lights) : BVH(_BVH), lights(_lights){};
    ~Scene();

    bool Intersect(const Ray &ray, SurfaceInteraction &interaction) const;
    bool IntersectP(Ray &ray) const;

    std::vector<std::shared_ptr<Light>> lights;
    std::shared_ptr<BVHAccel> BVH;
};

#endif