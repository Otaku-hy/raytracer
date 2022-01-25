#ifndef Matrix4_4_H
#define Matrix4_4_H

#include "Utils.hpp"

class Matrix4_4
{
private:
    /* data */
public:
    Matrix4_4(Matrix4f _mat = Matrix4f::Identity()) : mat(_mat){};
    ~Matrix4_4();

    Matrix4_4 operator*(const Matrix4_4 &other);
    Vector4f operator*(const Vector4f &vec);
    
    Matrix4_4 &operator=(const Matrix4f &matrix);

    void inverse();
    Matrix4_4 inversed();
    void setRotate(Vector3f axis, float theta);

    Matrix4f mat;
};

#endif
