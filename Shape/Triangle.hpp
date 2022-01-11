#ifndef Triangle_H
#define Triangle_H

#include "Shapes.hpp"
#include "Ray.hpp"
#include "../Acceleration/Bounds.hpp"
#include "../Matrix4_4/Matrix4_4.hpp"
#include "../Interaction/Interaction.hpp"
#include "../Interaction/SurfaceInteraction.hpp"

#include "../Mesh/TriangleMesh.hpp"

class Triangle : public Shapes
{
private:
    /* data */
public:
    Triangle() = default;
    Triangle(std::shared_ptr<TriangleMesh> _mesh, int _fcount, std::shared_ptr<Matrix4_4> _PtoO, std::shared_ptr<Matrix4_4> _OtoP);
    
    ~Triangle() override;
    bool Intersect(const Ray &ray, float &t1, SurfaceInteraction &interaction) override;
    bool IntersectP(Ray &ray) override;

    float surfaceArea() override;
    Bound3D genBoundingBox() override;
    
    Interaction SampleShape(Vector2f randVal,const Interaction &ref) override;
    float ShapePdf(const Vector3f &wi, const Interaction &ref) override;

    Vector3f getPos(size_t nVert); //num vertex
    Vector3f getNorm(size_t nVert);
    Vector2f getUv(size_t nVert);

    void interpolar(SurfaceInteraction &interaction, Vector3f baryCoord);

    std::shared_ptr<TriangleMesh> mesh;
    int fcnt; //face count
};

#endif