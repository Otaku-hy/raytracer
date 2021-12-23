#ifndef Utils_H
#define Utils_H

#include <cstdlib>
#include <iostream>

#include "../lib/Eigen/Eigen"

using namespace Eigen;

const float PI = 3.1415926;
const float EPISILON = 1e-2;

const int mortonBit = 10;
const int mortonScale = (1 << mortonBit);

// random Functions

inline int randomInt(int seed)
{
    return rand() % seed;
}

inline float randomFloat(int SPP)
{
    int n = rand() % SPP;

    return n / float(SPP);
}

//

inline float radians(float theta)
{
    return theta * 2 * PI / 360.0;
}

inline Vector3f toWorld(const Vector3f &a, const Vector3f &N)
{
    Vector3f B, C;
    if (std::abs(N.x()) > std::abs(N.y()))
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

inline float distance(Vector3f a, Vector3f b)
{
    Vector3f dis = a - b;
    float d2 = dis.x() * dis.x() + dis.y() * dis.y() + dis.z() * dis.z();

    return std::sqrt(d2);
}

// mortonCode functions

inline uint32_t leftshift3(uint32_t x)
{
    if (x == (1 << mortonBit))
        x--;
    x = (x | x << 16) & 0b00000011000000000000000011111111;
    x = (x | x << 8) & 0b00000011000000001111000000001111;
    x = (x | x << 4) & 0b00000011000011000011000011000011;
    x = (x | x << 2) & 0b00001001001001001001001001001001;
    return x;
}

inline uint32_t encodeMorton(Vector3f v)
{
    return (leftshift3(v.z()) << 2) | (leftshift3(v.y()) << 1) | (leftshift3(v.x()));
}
//

inline float clamp(float num, float low, float high)
{
    if (num < low)
        return low;
    if (num > high)
        return high;
    return num;
}

inline Vector3f Clamp(const Vector3f &t1, const Vector3f &t2)
{
    return Vector3f(std::max(t2[0], t1[0]), std::max(t2[1], t1[1]), std::max(t2[2], t1[2]));
}

template <typename T>
inline T lerp(float t, const T &s1, const T &s2)
{
    return s1 * (1 - t) + s2 * t;
}

template <typename T>
inline void Shuffle(T *sample, int cnt, int nDimension)
{
    for (int i = 0; i < cnt; i++)
    {
        int other = i + randomInt(cnt - i);
        std::swap(sample[nDimension * cnt + i], sample[nDimension * cnt + other]);
    }
}

inline Vector2f max(const Vector2f &a, const Vector2f &b)
{
    return Vector2f(std::max(a[0], b[0]), std::max(a[1], b[1]));
}

inline Vector2f min(const Vector2f &a, const Vector2f &b)
{
    return Vector2f(std::min(a[0], b[0]), std::min(a[1], b[1]));
}

inline Vector2f Ceil(Vector2f v)
{
    return Vector2f(ceil(v[0]), ceil(v[1]));
}

inline Vector2f Floor(Vector2f v)
{
    return Vector2f(floor(v[0]), floor(v[1]));
}

inline Vector3f absVec(const Vector3f &v)
{
    return Vector3f(std::abs(v[0]), std::abs(v[1]), std::abs(v[2]));
}

inline Vector3f operator*(const Vector3f &v1, const Vector3f &v2)
{
    return Vector3f(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

inline Vector3f operator/(const Vector3f &v1, const Vector3f &v2)
{
    float x = v2[0] <= 1e-4 ? 0 : v1[0] / v2[0];
    float y = v2[1] <= 1e-4 ? 0 : v1[1] / v2[1];
    float z = v2[2] <= 1e-4 ? 0 : v1[2] / v2[2];
    return Vector3f(x, y, z);
}

inline Vector3f operator+(const Vector3f &v1, const float &v)
{
    return Vector3f(v1[0] + v, v1[1] + v, v1[2] + v);
}

inline Vector3f operator-(const Vector3f &v1, const float &v)
{
    return Vector3f(v1[0] - v, v1[1] - v, v1[2] - v);
}

inline Vector3f sqrt(const Vector3f &v1)
{
    return Vector3f(std::sqrt(v1[0]), std::sqrt(v1[1]), std::sqrt(v1[2]));
}

inline bool Refract(const Vector3f &wi, float etaI, float etaT, const Vector3f &norm, Vector3f &wo)
{
    float cosThetaI = norm.dot(wi);
    float sin2ThetaI = 1 - cosThetaI * cosThetaI;

    float sin2ThetaT = etaI * etaI / (etaT * etaT) * sin2ThetaI;
    // std::cout << sin2ThetaI << " "<<sinThetaT << etaI <<" " << etaT<<std::endl;
    if (sin2ThetaT > 1)
        return false;

    float cosThetaT = std::sqrt(1 - sin2ThetaT);

    float coeff = etaI / etaT * cosThetaI;
    coeff -= wi.dot(Vector3f(0, 1, 0)) >= 0 ? cosThetaT : -cosThetaT;

    wo = coeff * norm - etaI / etaT * wi;
    wo = wo.normalized();

    return true;
}

#endif