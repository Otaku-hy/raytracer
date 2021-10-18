#ifndef TriangleMesh_H
#define TriangleMesh_H

#include <vector>

#include "../lib/Eigen/Eigen"

using namespace Eigen;

class TriangleMesh
{
private:
    /* data */
public:
    TriangleMesh() = default;
    TriangleMesh(size_t nTriangles, std::vector<Vector3f> &pos, std::vector<int> &posIndex) : nTriangles(nTriangles), pos(pos), posIndex(posIndex){};

    TriangleMesh(size_t nTriangles, std::vector<Vector3f> &pos, std::vector<Vector3f> &norm,
                 std::vector<int> &posIndex, std::vector<int> &normIndex) : nTriangles(nTriangles), pos(pos), norm(norm), posIndex(posIndex),
                                                                            normIndex(normIndex) { hasNorm = true; };

    TriangleMesh(size_t nTriangles, std::vector<Vector3f> &pos, std::vector<Vector3f> &norm,
                 std::vector<Vector2f> &uv, std::vector<int> &posIndex, std::vector<int> &normIndex,
                 std::vector<int> &uvIndex) : nTriangles(nTriangles), pos(pos), norm(norm), uv(uv), posIndex(posIndex),
                                              normIndex(normIndex), uvIndex(uvIndex) { hasNorm = hasUv = true; };

    ~TriangleMesh();

    bool hasNorm = false;
    bool hasUv = false;

    size_t nTriangles;

    std::vector<Vector3f> pos;
    std::vector<Vector3f> norm;
    std::vector<Vector2f> uv;

    std::vector<int> posIndex;
    std::vector<int> normIndex;
    std::vector<int> uvIndex;
};

TriangleMesh::~TriangleMesh()
{
}

#endif