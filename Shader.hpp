#ifndef Shader_H
#define Shader_H

#include "Scene.hpp"
#include "Utils.hpp"
#include <cmath>

using namespace Eigen;

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

        Vector3f BRDF = intersection.material->albedo;

        Vector3f light = _ambient + _diffuse + _specular;

        color += Vector3f(light.x() * BRDF.x(), light.y() * BRDF.y(), light.z() * BRDF.z());
    }

    return color;
}

Vector3f rendering(Scene scene, Intersection intersection, int depth)
{
    Vector3f ldir(0, 0, 0);
    Vector3f lindir(0, 0, 0);

    Vector3f randomDir = intersection.material->sample(intersection.norm);
    Ray objRay(intersection.pos, randomDir);

    Intersection objIntersection(Vector3f(0, 0, 0), Vector3f(0, 0, 0), NULL);

    Vector3f lightDir = (scene.lights[0].pos - intersection.pos).normalized();

    ldir = product(scene.lights[0].color, intersection.material->eval(lightDir, intersection.norm)) * lightDir.dot(intersection.norm);

    if (depth < 4 && scene.scene_intersection(objRay, objIntersection))
    {
        lindir = product(rendering(scene, objIntersection, depth + 1), intersection.material->eval(objRay.dir, intersection.norm)) * std::max(0.0f,objRay.dir.dot(objIntersection.norm)) / intersection.material->pdf();
    }

    return ldir + lindir;
}

#endif