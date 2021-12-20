#ifndef MatrixFunctions_H
#define MatrixFunctions_H

#include "../lib/Eigen/Eigen"
#include "../Matrix4_4/Matrix4_4.hpp"

using namespace Eigen;

enum VecType
{
    NORM,
    POS,
};

inline Matrix4_4 worldToShading(const Vector3f &norm)
{
    Vector3f X;
  
    if (norm[0] != 0 && norm[2] != 0)
    {
        X = Vector3f(-norm[2], 0, norm[0]);
    }
    else if (norm[1] != 0 && norm[2] != 0)
    {
        X = Vector3f(0, -norm[2], norm[1]);
    }
    else if (norm[0] != 0 && norm[1] != 0)
    {
        X = Vector3f(-norm[1], norm[0], 0);
    }
    else
    {
        X = Vector3f(norm[1], norm[2], norm[0]);
    }
    // X = Vector3f(-norm[2], 0, norm[0]);

    X = X.normalized();

    Vector3f Z = X.cross(norm).normalized();
    Vector3f Y = Z.cross(X).normalized();

    Matrix4f worldToShading = Matrix4f::Identity();
    worldToShading.row(0) = Vector4f(X[0], X[1], X[2], 0);
    worldToShading.row(1) = Vector4f(Y[0], Y[1], Y[2], 0);
    worldToShading.row(2) = Vector4f(Z[0], Z[1], Z[2], 0);

    return Matrix4_4(worldToShading);
}

inline Vector4f Vector3to4(Vector3f vec, VecType type)
{
    if (type == POS)
    {
        return Vector4f(vec[0], vec[1], vec[2], 1.0);
    }
    if (type == NORM)
    {
        return Vector4f(vec[0], vec[1], vec[2], 0.0);
    }
    return Vector4f(0, 0, 0, 0);
}

inline Vector3f Vector4to3(Vector4f vec)
{
    return Vector3f(vec[0], vec[1], vec[2]);
}

#endif