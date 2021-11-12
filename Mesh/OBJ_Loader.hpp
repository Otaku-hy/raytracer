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
    /* data */
public:
    Loader() = default;
    Loader(std::string _fileName) : fileName(_fileName){};
    ~Loader();

    void loadFile();
    std::shared_ptr<TriangleMesh> createTriangleMesh();

    std::vector<Vector3f> pos;
    std::vector<Vector3f> norm;
    std::vector<Vector2f> uv;

    std::vector<int> posIndex;
    std::vector<int> normIndex;
    std::vector<int> uvIndex;

    std::string fileName;

    bool hasNorm = false, hasUv = false;

    int tCount = 0;
};

#endif
