#ifndef TransformFunction_H
#define TransformFunction_H

#include "TransformMat.hpp"

#include "../lib/Eigen/Eigen"

using namespace Eigen;

Transform worldToShading(const Vector3f &norm)
{
    Vector3f X;
    if (norm[0] >= norm[1])
    {
        X = Vector3f(-norm[2], 0, norm[0]);
    }
    else
    {
        X = Vector3f(0, -norm[2], norm[1]);
    }
    X = X.normalized();

    Vector3f Z = X.cross(norm).normalized();

    Matrix4f worldToShading = Matrix4f::Identity();
    worldToShading.row(0) = Vector4f(X[0], X[1], X[2], 0);
    worldToShading.row(1) = Vector4f(Y[0], Y[1], Y[2], 0);
    worldToShading.row(2) = Vector4f(Z[0], Z[1], Z[2], 0);

    return TransformMat(worldToShading);
}

#endif