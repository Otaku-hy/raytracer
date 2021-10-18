#ifndef TransformMat_H
#define TransformMat_H

#include "../Utils.hpp"
#include "../lib/Eigen/Eigen"

using namespace Eigen;

enum vecType
{
    Norm,
    Pos
};

class TransformMat
{
private:
    /* data */
public:
    TransformMat() = default;
    TransformMat(Matrix4f _mat) : mat(_mat){};
    ~TransformMat();

    void operator=(Matrix4f _mat);
    Vector3f operator()(Vector3f &v, vecType type);

    void setRotate(Vector3f axis, float theta);
    Vector3f trans(const Vector3f &v, vecType type);
    void inverse();

    Matrix4f mat = Matrix4f::Identity();
};

void TransformMat::setRotate(Vector3f axis, float theta)
{
    Vector3f a = axis.normalized();
    Matrix4f rotate = Matrix4f::Identity();

    float sinTheta = std::sin(radians(theta));
    float cosTheta = std::cos(radians(theta));

    rotate(0, 0) = a.x() * a.x() + (1 - a.x() * a.x()) * cosTheta;
    rotate(0, 1) = a.x() * a.y() * (1 - cosTheta) - a.z() * sinTheta;
    rotate(0, 2) = a.x() * a.z() * (1 - cosTheta) + a.y() * sinTheta;

    rotate(1, 0) = a.x() * a.y() * (1 - cosTheta) + a.z() * sinTheta;
    rotate(1, 1) = a.y() * a.y() + (1 - a.y() * a.y()) * cosTheta;
    rotate(1, 2) = a.y() * a.z() * (1 - cosTheta) - a.x() * sinTheta;

    rotate(2, 0) = a.x() * a.z() * (1 - cosTheta) - a.y() * sinTheta;
    rotate(2, 1) = a.y() * a.z() * (1 - cosTheta) + a.x() * sinTheta;
    rotate(2, 2) = a.z() * a.z() + (1 - a.z() * a.z()) * cosTheta;

    mat = rotate;
}

Vector3f TransformMat::operator()(Vector3f &v, vecType type)
{
    return trans(v,type);
}

Vector3f TransformMat::trans(const Vector3f &v, vecType type)
{
    Vector4f tmpV;
    if (type == Norm)
    {
        tmpV = Vector4f(v[0], v[1], v[2], 0.0);
        tmpV = mat * tmpV;
        tmpV.normalize();
    }
    else if (type == Pos)
    {
        tmpV = Vector4f(v[0], v[1], v[2], 1.0);
        tmpV = mat * tmpV;
        tmpV /= tmpV.w();
    }

    return Vector3f(tmpV[0], tmpV[1], tmpV[2]);
}

void TransformMat::inverse()
{
    Matrix4f tmp = mat;
    mat = tmp.inverse();
}

void TransformMat::operator=(Matrix4f _mat)
{
    mat = _mat;
}

TransformMat ::~TransformMat()
{
}

#endif
