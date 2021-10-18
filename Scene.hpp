#ifndef Scene_H
#define Scene_H
#include "lib/Eigen/Eigen"
#include <vector>
#include "Object.hpp"
#include "Light.hpp"
#include "Camera.hpp"
using namespace Eigen;

class Scene
{
private:
    /* data */
public:
    Scene(Camera _camera, AreaLight _light, std::vector<Object *> _objects);
    ~Scene();
    bool scene_intersection(Ray ray, Intersection &intersection);
    void sampleLight(Vector3f &pos, float &pdf);
    Camera *camera;
    std::vector<AreaLight> lights;
    std::vector<Object *> objects;
};

Scene::Scene(Camera _camera, AreaLight _light, std::vector<Object *> _objects)
{
    camera = &_camera;
    lights.push_back(_light);
    objects = _objects;
}

Scene::~Scene()
{
}

bool Scene::scene_intersection(Ray ray, Intersection &intersection)
{
    float intersection_t = 500.0;

    for (int i = 0; i < objects.size(); i++)
    {
        float tmp_t = 550;
        if (objects[i]->ray_intersection(ray, tmp_t) && tmp_t < intersection_t)
        {
            intersection_t = tmp_t;
            objects[i]->computeIntersection(intersection, intersection_t, ray);
        }
    }

    if (intersection_t < 500.0)
        return true;

    else
    {
        intersection.happen = false;
        return false;
    }
}

void Scene::sampleLight(Vector3f &pos, float &pdf)
{
    float area_sum = 0;
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->hasEmit() == true)
        {
            area_sum += objects[i]->getArea();
        }
    }

    float randomSum = randomFloat(100) * area_sum;
    area_sum = 0;

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->hasEmit() == true)
        {
            area_sum += objects[i]->getArea();
            if (area_sum > randomSum)
            {
                objects[i]->sample(pos, pdf);
            }
        }
    }
}

#endif