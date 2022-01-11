#ifndef OBJ_Loader_H
#define OBJ_Loader_H

#include <string>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <iostream>

#include "TriangleMesh.hpp"

#include "../lib/Eigen/Eigen"

using namespace Eigen;

class Loader
{
private:
    std::vector<Vector3f> pos;
    std::vector<Vector3f> norm;
    std::vector<Vector2f> uv;

    std::vector<int> posIndex;
    std::vector<int> normIndex;
    std::vector<int> uvIndex;

    std::string fileName;
    bool hasNorm = false, hasUv = false;
    int tCount = 0;

public:
    Loader() = default;
    Loader(const std::string &_fileName);
    ~Loader();

    void CreateTriangleMesh(std::shared_ptr<TriangleMesh> &mesh);
};

#endif
