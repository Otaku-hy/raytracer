#ifndef Triangle_H
#define Triangle_H

#include <vector>
#include <string>
#include <iostream>

#include "Shapes.hpp"

#include "../Mesh/TriangleMesh.hpp"
#include "../Acceleration/Bounds.hpp"

class Triangle : public Shapes
{
private:
    /* data */
public:
    Triangle() = default;
    Triangle(std::shared_ptr<TriangleMesh> _mesh, int _fcount, std::shared_ptr<TransformMat> _PtoO, std::shared_ptr<TransformMat> _OtoP);
    ~Triangle();

    bool intersect(Ray &ray, float &t1, Intersection &intersection) override;
    float surfaceArea() override;
    Bound3D genBoundingBox() override;

    Vector3f getPos(size_t nVert); //num vertex
    Vector3f getNorm(size_t nVert);
    Vector2f getUv(size_t nVert);

    void interpolar(Intersection &intersection, Vector3f baryCoord);

    std::shared_ptr<TriangleMesh> mesh;
    int fcnt; //face count
};

Triangle::Triangle(std::shared_ptr<TriangleMesh> _mesh, int _fcnt, std::shared_ptr<TransformMat> _PtoO, std::shared_ptr<TransformMat> _OtoP) : mesh(_mesh), fcnt(_fcnt), Shapes(_OtoP, _PtoO)
{
}

Vector3f Triangle::getPos(size_t nVert)
{
    return mesh->pos[mesh->posIndex[fcnt * 3 + nVert] - 1];
}

Vector3f Triangle::getNorm(size_t nVert)
{
    return mesh->norm[mesh->normIndex[fcnt * 3 + nVert] - 1];
}

Vector2f Triangle::getUv(size_t nVert)
{
    return mesh->uv[mesh->uvIndex[fcnt * 3 + nVert] - 1];
}

float Triangle::surfaceArea()
{
    Vector3f a = getPos(0);
    Vector3f b = getPos(1);
    Vector3f c = getPos(2);

    return (b - a).cross(c - a).norm() * 0.5;
}

void Triangle::interpolar(Intersection &intersection, Vector3f baryCoord)
{
    if (mesh->hasNorm == true)
    {
        intersection.norm = baryCoord[0] * getNorm(0) + baryCoord[1] * getNorm(1) + baryCoord[2] * getNorm(2);
    }
    else
    {
        intersection.norm = (getPos(1) - getPos(0)).cross(getPos(2) - getPos(0)).normalized();
    }
    if (mesh->hasUv == true)
    {
        intersection.uv = baryCoord[0] * getUv(0) + baryCoord[1] * getUv(1) + baryCoord[2] * getUv(2);
    }
}

bool Triangle::intersect(Ray &ray, float &t1, Intersection &intersection)
{
    Vector3f e0 = getPos(0) - getPos(2);
    Vector3f e1 = getPos(1) - getPos(2);
    Vector3f Oa = ray.origin - OtoP->trans(getPos(2), Pos);

    float detA = e0[0] * e1[1] * ray.dir[2] + e0[2] * e1[0] * ray.dir[1] + e0[1] * e1[2] * ray.dir[0] - e0[2] * e1[1] * ray.dir[0] - e0[1] * e1[0] * ray.dir[2] - e0[0] * e1[2] * ray.dir[1];
    float detU = Oa[0] * e1[1] * ray.dir[2] + Oa[2] * e1[0] * ray.dir[1] + Oa[1] * e1[2] * ray.dir[0] - Oa[2] * e1[1] * ray.dir[0] - Oa[1] * e1[0] * ray.dir[2] - Oa[0] * e1[2] * ray.dir[1];
    float detV = e0[0] * Oa[1] * ray.dir[2] + e0[2] * Oa[0] * ray.dir[1] + e0[1] * Oa[2] * ray.dir[0] - e0[2] * Oa[1] * ray.dir[0] - e0[1] * Oa[0] * ray.dir[2] - e0[0] * Oa[2] * ray.dir[1];
    float detT = -(e0[0] * e1[1] * Oa[2] + e0[2] * e1[0] * Oa[1] + e0[1] * e1[2] * Oa[0] - e0[2] * e1[1] * Oa[0] - e0[1] * e1[0] * Oa[2] - e0[0] * e1[2] * Oa[1]);

    if (detA == 0)
    {
        return false;
    }

    Vector3f bary(detU / detA, detV / detA, 1 - (detU + detV) / detA);
    float tmpT = detT / detA;

    if (tmpT < 0 || tmpT > ray.tMax || bary.x() < 0 || bary.y() < 0 || bary.z() < 0)
        return false;

    if (tmpT < intersection.t1)
    {
        t1 = tmpT;
        intersection.t1 = t1;
        intersection.happen = true;
        intersection.pos = ray.origin + t1 * ray.dir;
        interpolar(intersection, bary);
        return true;
    }
    else
    {
        return false;
    }
}

Bound3D Triangle::genBoundingBox()
{
    Vector3f v0 = getPos(0);
    Vector3f v1 = getPos(1);
    Vector3f v2 = getPos(2);

    v0 = OtoP->trans(v0, Pos);
    v1 = OtoP->trans(v1, Pos);
    v2 = OtoP->trans(v2, Pos);

    // std::cout << v0[0] << " " << v0[1] << " " << v0[2] << "\n"
    //      << v1[0] << " " << v1[1] << " " << v1[2] << "\n"
    //      << v2[0] << " " << v2[1] << " " << v2[2] << "\n"
    //      << std::endl;

    Bound3D b(v0);

    b = Union(Union(b, v1), v2);

    return b;
}

Triangle::~Triangle()
{
}

#endif