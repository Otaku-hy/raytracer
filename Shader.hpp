#ifndef Shader_H
#define Shader_H

#include "Scene.hpp"
#include "Utils.hpp"
#include <cmath>

using namespace Eigen;

Vector3f rendering(Scene scene, Intersection intersection, int depth)
{
    Vector3f ldir(0, 0, 0);
    Vector3f lindir(0, 0, 0);

    Vector3f lightPos = scene.lights[0].SampleLight();
    Vector3f lightDir = (lightPos - intersection.pos).normalized();
    Vector3f randomDir = intersection.material->sample(intersection.norm);
    Vector3f offsetPos = offset(intersection.pos, intersection.norm, randomDir);
    Vector3f lightOffset = offset(intersection.pos, intersection.norm, lightDir);

    Ray objRay(offsetPos, randomDir);
    Intersection objIntersection(Vector3f(0, 0, 0), Vector3f(0, 0, 0), NULL);
    Intersection lightIntersectiom(Vector3f(0, 0, 0), Vector3f(0, 0, 0), NULL);
    Ray lightRay(lightOffset, lightDir);

    if (!scene.scene_intersection(lightRay, lightIntersectiom))
    {
        ldir = product(scene.lights[0].color, intersection.material->eval(lightDir, intersection.norm)) * lightDir.dot(intersection.norm) * -lightDir.dot(scene.lights[0].norm) / distance(lightPos, offsetPos) / scene.lights[0].lightPdf();
    }

    if (depth < 16 && scene.scene_intersection(objRay, objIntersection))
    {
        lindir = 0.75 * product(rendering(scene, objIntersection, depth + 1), intersection.material->eval(objRay.dir, intersection.norm)) * objRay.dir.dot(intersection.norm) / intersection.material->pdf();
    }

    return ldir + lindir;
}

#endif