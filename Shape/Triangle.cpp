#include "Triangle.hpp"

Triangle::Triangle(std::shared_ptr<TriangleMesh> _mesh, int _fcnt, std::shared_ptr<Matrix4_4> _PtoO, std::shared_ptr<Matrix4_4> _OtoP) : mesh(_mesh), fcnt(_fcnt), Shapes(_OtoP, _PtoO)
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

void Triangle::interpolar(SurfaceInteraction &interaction, Vector3f baryCoord)
{
    if (mesh->hasNorm == true)
    {
        interaction.norm = baryCoord[0] * getNorm(0) + baryCoord[1] * getNorm(1) + baryCoord[2] * getNorm(2);
    }
    else
    {
        interaction.norm = (getPos(1) - getPos(0)).cross(getPos(2) - getPos(0)).normalized();
    }
    if (mesh->hasUv == true)
    {
        interaction.uv = baryCoord[0] * getUv(0) + baryCoord[1] * getUv(1) + baryCoord[2] * getUv(2);
    }
}

bool Triangle::IntersectP(Ray &ray)
{
    Vector3f e0 = getPos(0) - getPos(2);
    Vector3f e1 = getPos(1) - getPos(2);
    Vector3f Oa = ray.origin - Vector4to3(*OtoP * Vector3to4(getPos(2), POS));

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

    ray.tMax = tmpT;
    return true;
}

bool Triangle::Intersect(const Ray &ray, float &t1, SurfaceInteraction &interaction)
{
    Vector3f e0 = getPos(0) - getPos(2);
    Vector3f e1 = getPos(1) - getPos(2);
    Vector3f Oa = ray.origin - Vector4to3(*OtoP * Vector3to4(getPos(2), POS));

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

    if (tmpT < interaction.t1)
    {
        t1 = tmpT;
        interaction.t1 = t1;
        interaction.happen = true;
        interaction.pos = ray.origin + t1 * ray.dir;
        interpolar(interaction, bary);
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

    v0 = Vector4to3(*OtoP * Vector3to4(v0, POS));
    v1 = Vector4to3(*OtoP * Vector3to4(v1, POS));
    v2 = Vector4to3(*OtoP * Vector3to4(v2, POS));

    // std::cout << v0[0] << " " << v0[1] << " " << v0[2] << "\n"
    //      << v1[0] << " " << v1[1] << " " << v1[2] << "\n"
    //      << v2[0] << " " << v2[1] << " " << v2[2] << "\n"
    //      << std::endl;

    Bound3D b(v0);

    b = Union(Union(b, v1), v2);

    return b;
}

Interaction Triangle::SampleShape(Vector2f randVal, const Interaction &ref)
{
    float su0 = sqrt(randVal[0]);
    Vector3f barycoord(1 - su0, randVal[1] * su0, (1 - randVal[1]) * su0);
    Vector3f pos = getPos(0) * barycoord[0] + getPos(1) * barycoord[1] + getPos(2) * barycoord[2];

    Vector3f wi = (pos - ref.pos).normalized();
    Ray ray(ref.pos, wi);
    float tHit;

    SurfaceInteraction interaction_Li;
    Intersect(ray, tHit, interaction_Li);

    return interaction_Li;
}

float Triangle::ShapePdf(const Vector3f &wi, const Interaction &ref)
{
    Ray ray(ref.pos, wi);
    float tHit;
    SurfaceInteraction interaction_Li(5000);
    if (this->Intersect(ray, tHit, interaction_Li))
    {
        return distance(ref.pos, interaction_Li.pos) * distance(ref.pos, interaction_Li.pos) / (surfaceArea() * abs(-wi.dot(interaction_Li.norm)));
    }
    else
    {
        return 0;
    }
}

Triangle::~Triangle()
{
}