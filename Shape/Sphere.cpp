#include "Sphere.hpp"

Sphere::Sphere(Vector3f center, float radius) : center(center), r(radius)
{
    Matrix4f mat = Matrix4f::Identity();
    mat(0, 3) = center[0];
    mat(1, 3) = center[1];
    mat(2, 3) = center[2];

    OtoP = std::make_shared<Matrix4_4>(mat);
    PtoO = std::make_shared<Matrix4_4>(mat.inverse());
}

bool Sphere::Intersect(const Ray &ray, float &t1, SurfaceInteraction &interaction)
{
    Vector3f origin = Vector4to3(*PtoO * Vector3to4(ray.origin, POS));
    Vector3f dir = Vector4to3(*PtoO * Vector3to4(ray.dir, NORM));

    float a = dir.x() * dir.x() + dir.y() * dir.y() + dir.z() * dir.z();
    float b = 2 * (dir.x() * origin.x() + dir.y() * origin.y() + dir.z() * origin.z());
    float c = origin.x() * origin.x() + origin.y() * origin.y() + origin.z() * origin.z() - r * r;

    float delta = b * b - 4 * a * c;

    if (delta < 0)
        return false;

    float t1Tmp = (-b - std::sqrt(delta)) / (2 * a);
    float t2Tmp = (-b + std::sqrt(delta)) / (2 * a);

    if (t1Tmp < 0)
        t1Tmp = t2Tmp;
    if (t1Tmp < 0 || t1Tmp > ray.tMax)
        return false;

    t1 = t1Tmp;

    if (t1 < interaction.t1)
    {
        interaction.t1 = t1;
        interaction.happen = true;
        interaction.pos = origin + t1 * dir;
        interaction.pos = Vector4to3(*OtoP * Vector3to4(interaction.pos, POS));
        interaction.norm = (interaction.pos - center).normalized();

        return true;
    }
    else
    {
        return false;
    }
}

bool Sphere::IntersectP(Ray &ray)
{
    Vector3f origin = Vector4to3(*PtoO * Vector3to4(ray.origin, POS));
    Vector3f dir = Vector4to3(*PtoO * Vector3to4(ray.dir, NORM));

    float a = dir.x() * dir.x() + dir.y() * dir.y() + dir.z() * dir.z();
    float b = 2 * (dir.x() * origin.x() + dir.y() * origin.y() + dir.z() * origin.z());
    float c = origin.x() * origin.x() + origin.y() * origin.y() + origin.z() * origin.z() - r * r;

    float delta = b * b - 4 * a * c;

    if (delta < 0)
        return false;

    float t1Tmp = (-b - std::sqrt(delta)) / (2 * a);
    float t2Tmp = (-b + std::sqrt(delta)) / (2 * a);

    if (t1Tmp < 0)
        t1Tmp = t2Tmp;
    if (t1Tmp < 0 || t1Tmp > ray.tMax)
        return false;

    ray.tMax = t1Tmp;
    return true;
}

float Sphere::surfaceArea()
{
    return 4 * PI * r * r;
}

Bound3D Sphere::genBoundingBox()
{
    return Bound3D(Vector3f(center.x() - r, center.y() - r, center.z() - r), Vector3f(center.x() + r, center.y() + r, center.z() + r));
}

Sphere::~Sphere()
{
}
