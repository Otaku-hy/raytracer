#ifndef Utils_H
#define Utils_H
#include "lib/Eigen/Eigen"
#include <cstdlib>
#include <iostream>

using namespace Eigen;

const float PI = 3.1415926;

const int mortonBit = 10;
const int mortonScale = (1 << mortonBit);

// random Functions

int randomInt(int seed)
{
    return rand() % seed;
}

float randomFloat(int SPP)
{
    int n = rand() % SPP;

    return n / float(SPP);
}

float randomPos(int SPP)
{
    int n = rand() % SPP;

    float rand = n / float(SPP);

    rand = (rand - 0.5) * 2.0;

    return rand;
}
//

float radians(float theta)
{
    return theta * 2 * PI / 360.0;
}

Vector3f valueProduct(Vector3f a, Vector3f b)
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

// mortonCode functions

uint32_t leftshift3(uint32_t x)
{
    if (x == (1 << mortonBit))
        x--;
    x = (x | x << 16) & 0b00000011000000000000000011111111;
    x = (x | x << 8) & 0b00000011000000001111000000001111;
    x = (x | x << 4) & 0b00000011000011000011000011000011;
    x = (x | x << 2) & 0b00001001001001001001001001001001;
    return x;
}

uint32_t encodeMorton(Vector3f v)
{
    return (leftshift3(v.z()) << 2) | (leftshift3(v.y()) << 1) | (leftshift3(v.x()));
}
//

float clamp(float num, float low, float high)
{
    if (num < low)
        return low;
    if (num > high)
        return high;
    return num;
}

Vector3f Clamp(const Vector3f &t1, const Vector3f &t2)
{
    return Vector3f(std::max(t2[0], t1[0]), std::max(t2[1], t1[1]), std::max(t2[2], t1[2]));
}

template <typename T>
T lerp(float t, const T &s1, const T &s2)
{
    return s1 * (1 - t) + s2 * t;
}

template <typename T>
void Shuffle(T *sample, int cnt, int nDimension)
{
    for (int i = 0; i < cnt; i++)
    {
        int other = i + randomInt(cnt - i);
        std::swap(sample[nDimension * cnt + i], sample[nDimension * cnt + other]);
    }
}

Vector2f max(const Vector2f &a, const Vector2f &b)
{
    return Vector2f(std::max(a[0], b[0]), std::max(a[1], b[1]));
}

Vector2f min(const Vector2f &a, const Vector2f &b)
{
    return Vector2f(std::min(a[0], b[0]), std::min(a[1], b[1]));
}

Vector2f Ceil(Vector2f v)
{
    return Vector2f(ceil(v[0]), ceil(v[1]));
}

Vector2f Floor(Vector2f v)
{
    return Vector2f(floor(v[0]), floor(v[1]));
}

#endif