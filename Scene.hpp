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
    Scene(Camera _camera, AreaLight _light, std::vector<Object> &_objects);
    ~Scene();
    bool scene_intersection(Ray ray, Intersection &intersection);

    Camera* camera;
    std::vector<AreaLight> lights;
    std::vector<Object> objects;
};

Scene::Scene(Camera _camera, AreaLight _light, std::vector<Object> &_objects)
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
        if (objects[i].ray_intersection(ray, tmp_t) && tmp_t < intersection_t)
        {
            intersection_t = tmp_t;
            Vector3f intersectPos = ray.origin + intersection_t * ray.dir;
            Vector3f normal;
            if (objects[i].type == sphere)
            {
                normal = (intersectPos - objects[i].center).normalized();
            }
            if (objects[i].type == plane)
            {
                normal = objects[i].norm;
            }

            intersection.pos = intersectPos;
            intersection.norm = normal;
            intersection.material = objects[i].material;
        }
    }

    return intersection_t < 500.0;
}

#endif