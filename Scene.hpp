#ifndef Scene_H
#define Scene_H
#include "lib/Eigen/Eigen"
#include <vector>
#include "Object.hpp"
#include "Light.hpp"
using namespace Eigen;

class Scene
{
private:
    /* data */
public:
    Scene(PointLight _lights, std::vector<Sphere> &_spheres);
    ~Scene();
    bool scene_intersection(Ray ray, Intersection &intersection);

    std::vector<PointLight> lights;
    std::vector<Sphere> spheres;
};

Scene::Scene(PointLight _lights, std::vector<Sphere> &_spheres)
{
    lights.push_back(_lights);
    spheres = _spheres;
}

Scene::~Scene()
{
}

bool Scene::scene_intersection(Ray ray, Intersection &intersection)
{
    float intersection_t = 500.0;

    for (int i = 0; i < spheres.size(); i++)
    {
        float tmp_t = 550;
        if (spheres[i].ray_intersection(ray, tmp_t) && tmp_t < intersection_t)
        {
            intersection_t = tmp_t;
            Vector3f intersectPos = ray.origin + intersection_t * ray.dir;
            Vector3f normal = (intersectPos - spheres[i].center).normalized();

            intersection.pos = intersectPos;
            intersection.norm = normal;
            intersection.material = spheres[i].material;
        }
    }

    return intersection_t < 500.0;
}

#endif