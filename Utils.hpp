#ifndef Utils_H
#define Utils_H
#include "lib/Eigen/Eigen"
#include <cstdlib>
#include <iostream>

using namespace Eigen;

float randomFloat(int SPP)
{
    int n = rand() % SPP;

    return n / float(SPP);
}

float randomNeg(int SPP)
{
    int n = rand() % SPP;

    float rand = n / float(SPP);

    rand = (rand - 0.5) * 2.0;

    return rand;
}

void gamma_correct(Vector3f &color)
{
    color.x() = std::pow(color.x(), 1 / 2.2f);
    color.y() = std::pow(color.y(), 1 / 2.2f);
    color.z() = std::pow(color.z(), 1 / 2.2f);
}

void test(int image_width, int image_height, Vector3f screen[460][240])
{
    for (int i = 0; i < image_width; i++)
    {
        for (int j = 0; j < image_height; j++)
        {
            std::cout << screen[i][j].x() << screen[i][j].y() << screen[i][j].z() << std::endl;
        }
    }
}

Vector3f product(Vector3f a, Vector3f b)
{
    return Vector3f(a.x() * b.x(), a.y() * b.y(), a.z() * b.z());
}

Vector3f toWorld(const Vector3f &a, const Vector3f &N)
{
    Vector3f B, C;
    if (std::fabs(N.x()) > std::fabs(N.y()))
    {
        C = Vector3f(N.z(), 0.0f, -N.x()).normalized();
    }
    else
    {
        C = Vector3f(0.0f, N.z(), -N.y()).normalized();
    }
    B = C.cross(N);
    
    return a.x() * B + a.y() * C + a.z() * N;
}

float distance(Vector3f a, Vector3f b)
{
    Vector3f dis = a - b;
    float d2 = dis.x() * dis.x() + dis.y() * dis.y() + dis.z() * dis.z();

    return std::sqrt(d2);
}

Vector3f offset(Vector3f pos, Vector3f norm, Vector3f dir)
{
    if (norm.dot(dir) > 0)
    {
        return pos + 0.0015 * norm;
    }
    else
    {
        return pos - 0.0015 * norm;
    }
}

#endif