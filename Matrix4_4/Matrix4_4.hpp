#ifndef Matrix4_4_H
#define Matrix4_4_H

#include "../Utils.hpp"
#include "../lib/Eigen/Eigen"

using namespace Eigen;

class Matrix4_4
{
private:
    /* data */
public:
    Matrix4_4(Matrix4f _mat = Matrix4f::Identity()) : mat(_mat){};
    ~Matrix4_4();

    Matrix4_4 operator*(const Matrix4_4 &other);
    Vector4f operator*(const Vector4f &vec);
    void operator()(const Matrix4f &matrix);

    void inverse();
    Matrix4_4 inversed();
    void setRotate(Vector3f axis, float theta);

    Matrix4f mat;
};

Matrix4_4 Matrix4_4::operator*(const Matrix4_4 &other)
{
    return Matrix4_4(mat * other.mat);
}

Vector4f Matrix4_4::operator*(const Vector4f &vec)
{
    if (vec[3] == 0)
        return (mat * vec).normalized();
    else
    {
        Vector4f vecRet = mat * vec;
        vecRet /= vecRet[3];
        return vecRet;
    }
}

void Matrix4_4::operator()(const Matrix4f &matrix)
{
    mat = matrix;
}

void Matrix4_4::inverse()
{
    Matrix4f matRet = mat;
    mat = matRet.inverse();
}

Matrix4_4 Matrix4_4::inversed()
{
    return Matrix4_4(mat.inverse());
}

void Matrix4_4::setRotate(Vector3f axis, float theta)
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

Matrix4_4::~Matrix4_4()
{
}

#endif
