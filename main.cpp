#include <iostream>
#include <cstdlib>
#include "lib/Eigen/Core"
#include "Ray.hpp"
#include "Object.hpp"
#include "Scene.hpp"
#include "Shader.hpp"

using namespace Eigen;

const int image_width = 460;
const int image_height = 240;
const int SPP = 16;

Vector3f screen[image_width][image_height];

float randomFloat()
{
    int n = rand() % SPP;

    return n / float(SPP);
}

void test()
{
    for (int i = 0; i < image_width; i++)
    {
        for (int j = 0; j < image_height; j++)
        {
            std::cout << screen[i][j].x() << screen[i][j].y() << screen[i][j].z() << std::endl;
        }
    }
}

void image_color()
{
    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j)
    {
        for (int i = 0; i < image_width; ++i)
        {
            int ir = static_cast<int>(255.999 * screen[i][image_height - 1 - j].x());
            int ig = static_cast<int>(255.999 * screen[i][image_height - 1 - j].y());
            int ib = static_cast<int>(255.999 * screen[i][image_height - 1 - j].z());

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}

void cast_ray(Scene scene)
{
    float aspect_ratio = image_width / float(image_height);
    float fov = 45.0 / 360.0 * PI * 2;

    float height = 2 * tan(fov / 2.0);
    float width = height * aspect_ratio;

    for (int i = 0; i < image_width; i++)
    {
        for (int j = 0; j < image_height; j++)
        {
            for (int k = 0; k < SPP; k++)
            {
                float coord_x = i + randomFloat();
                float coord_y = j + randomFloat();
                coord_x = (coord_x - image_width / 2.0) * width / float(image_width);
                coord_y = (coord_y - image_height / 2.0) * height / float(image_height);

                Vector3f rayDir = Vector3f(coord_x, coord_y, -1.0).normalized();
                Ray ray(Vector3f(0, 0, 0), rayDir);

                Vector3f background(0.1, 0.1, 0.1);
                gamma_correct(background);

                Intersection intersection(Vector3f(0, 0, 0), Vector3f(0, 0, 0),NULL);

                if (scene.scene_intersection(ray, intersection))
                {
                    screen[i][j] += phong(scene, intersection);
                }
                else
                {
                    screen[i][j] += background;
                }
            }

            screen[i][j] /= SPP;
        }
    }
}

int main()
{
    // Image
    Material white_diffuse(Vector3f(0,0,0));

    Sphere sphere1(Vector3f(0, 0, -5), 0.7,&white_diffuse);
    std::vector<Sphere> spheres;
    spheres.push_back(sphere1);

    PointLight light(Vector3f(0, 5, -2), Vector3f(1, 1, 1));

    Scene scene(light, spheres);

    cast_ray(scene);

    image_color();

    // test();

    return 0;
}