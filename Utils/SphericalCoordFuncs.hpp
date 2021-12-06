/*In this class, we assume that all the w0(i.e. the direction of the radiance) 
are translate to the shading coordinate,that is the original point of the system is
the shading point(0,0,0). Then the normal is (0,1,0), so, as the function below, 
we don't need the norm parameter appears in the parameter list of the function */

#ifndef SphericalCoordinateFunctions_H
#define SphericalCoordinateFunctions_H

#include "Utils.hpp"

inline float cosTheta(const Vector3f &w)
{
    return clamp(w[1], -1, 1);
}

inline float cos2Theta(const Vector3f &w)
{
    float value = cosTheta(w);
    return value * value;
}

inline float sinTheta(const Vector3f &w)
{
    return sqrt(1 - cos2Theta(w));
}

inline float tanTheta(const Vector3f &w)
{
    return sinTheta(w) / cosTheta(w);
}

inline float tan2Theta(const Vector3f &w)
{
    return tanTheta(w) * tanTheta(w);
}

inline float cosPhi(const Vector3f &w)
{
    float r = sinTheta(w);
    if (r <= 1e-4)
        return 0;
    else
    {
        return clamp(w[0] / r, -1, 1);
    }
}

inline float sinPhi(const Vector3f &w)
{
    return sqrt(1 - pow(cosPhi(w), 2));
}

inline Vector3f SphericalDirection(float sinTheta, float cosTheta, float phi)
{
    Vector3f xyDir = Vector3f(1, 0, 0) * cos(phi) + Vector3f(0, 0, 1) * sin(phi);
    xyDir *= sinTheta;

    return xyDir + cosTheta * Vector3f(0, 1, 0);
}

inline bool SameHemisphere(const Vector3f &w, const Vector3f &norm)
{
    if (w.dot(norm) >= 0)
        return true;

    else
        return false;
}

inline bool SameHemisphere(const Vector3f &w0, const Vector3f &wi, const Vector3f &norm)
{
    if (w0.dot(norm) >= 0 && wi.dot(norm) >= 0)
    {
        return true;
    }
    return false;
}

#endif