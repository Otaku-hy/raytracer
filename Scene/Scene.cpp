#include "Scene.hpp"

bool Scene::Intersect(const Ray &ray, SurfaceInteraction &interaction) const
{
    return BVH->Intersect(ray, interaction);
}
bool Scene::IntersectP(Ray &ray) const
{
    return BVH->IntersectP(ray);
}

Scene::~Scene()
{
}