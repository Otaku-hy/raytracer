#ifndef Shader_H
#define Shader_H

#include "Scene.hpp"
#include <cmath>

using namespace Eigen;

void gamma_correct(Vector3f &color)
{
    color.x() = std::pow(color.x(), 1 / 2.2f);
    color.y() = std::pow(color.y(), 1 / 2.2f);
    color.z() = std::pow(color.z(), 1 / 2.2f);
}

Vector3f phong(Scene scene, Intersection intersection)
{
    Vector3f color(0, 0, 0);

    for (int i = 0; i < scene.lights.size(); i++)
    {
        Vector3f lightDir = (scene.lights[i].pos - intersection.pos).normalized();
        Vector3f cameraDir = (Vector3f(0, 0, 0) - intersection.pos).normalized();
        Vector3f half = (lightDir + cameraDir).normalized();

        float diffuse = std::max(0.0f, lightDir.dot(intersection.norm)) * 0.7;
        Vector3f _diffuse = scene.lights[i].color * diffuse;

        float specular = std::pow(float(std::max(0.0f, half.dot(intersection.norm))), 32) * 0.3;
        Vector3f _specular = scene.lights[i].color * specular;

        Vector3f _ambient = scene.lights[i].color * 0.08;

        Vector3f BRDF(0.7, 0.5, 0.6);

        Vector3f light = _ambient + _diffuse + _specular;

        color += Vector3f(light.x() * BRDF.x(), light.y() * BRDF.y(), light.z() * BRDF.z());
    }

    gamma_correct(color);

    return color;
}

#endif