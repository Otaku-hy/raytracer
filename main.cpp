#include <iostream>
#include <cstdlib>
#include "lib/Eigen/Core"
#include "Ray.hpp"
#include "Utils.hpp"
#include "Object.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "test.cpp"

using namespace Eigen;

void cast_ray(Scene scene)
{
    float aspect_ratio = scene.camera->width / float(scene.camera->height);
    float fov = 45.0 / 360.0 * PI * 2;

    float height = 2 * tan(fov / 2.0);
    float width = height * aspect_ratio;

    for (int i = 0; i < scene.camera->width; i++)
    {
        for (int j = 0; j < scene.camera->height; j++)
        {
            for (int k = 0; k < scene.camera->SPP; k++)
            {
                float coord_x = i + 0.5;
                float coord_y = j + 0.5;
                coord_x = (coord_x - scene.camera->width / 2.0) * width / float(scene.camera->width);
                coord_y = (coord_y - scene.camera->height / 2.0) * height / float(scene.camera->height);

                Vector3f rayDir = Vector3f(coord_x, coord_y, -1.0).normalized();
                rayDir = scene.camera->translate * rayDir;
                Ray ray(Vector3f(0, 0, 0), rayDir);

                float interpolar = j / float(scene.camera->height);
                Vector3f start(1.0, 1.0, 1.0);
                Vector3f end(0.5, 0.7, 1.0);

                Vector3f background = start + interpolar * (end - start);

                Intersection intersection;

                if (scene.scene_intersection(ray, intersection))
                {
                    screen[i][j] += rendering(scene, intersection, 0);
                }
                else
                {
                    screen[i][j] += background;
                }
            }

            screen[i][j] /= float(scene.camera->SPP);
        }
    }
}

int main()
{
    // Image
    Material *white_diffuse = new Material(Vector3f(1, 1, 1), DIFFUSE, Vector3f(0, 0, 0));
    Material *red_diffuse = new Material(Vector3f(1, 0, 0), DIFFUSE, Vector3f(0, 0, 0));
    Material *skyblue_diffuse = new Material(Vector3f(0.5, 0.7, 1), DIFFUSE, Vector3f(0, 0, 0));

    Sphere sphere1(Vector3f(0.0, -0.07, -5.0), 0.7, white_diffuse);
    Sphere shpere3(Vector3f(0.0, -100.0, -5), 99.2, white_diffuse);
    Sphere sphere2(Vector3f(2.5, 0.0, -5.0), 0.8, red_diffuse);
    Sphere sphere4(Vector3f(-2.0, 0.1, -3.0), 0.9, skyblue_diffuse);

    std::vector<Object> objects;

    objects.push_back(sphere1);
    objects.push_back(sphere2);
    objects.push_back(shpere3);
    objects.push_back(sphere4);

    AreaLight light(Vector3f(2, 4, -3), Vector3f(1, 1, 1), 10.0);

    Camera camera(Vector3f(0, 0, 0), Vector3f(-0.2, 0, -1), Vector3f(0, 1.0, 0), 480, 260, 64);

    Scene scene(camera, light, objects);

    cast_ray(scene);

    camera.image_color();

    return 0;
}