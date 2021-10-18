/*In this class, we assume that all the w0(i.e. the direction of the radiance) 
are translate to the shading coordinate,that is the original point of the system is
the shading point(0,0,0). Then the normal is (0,1,0), so, as the function below, 
we don't need the norm parameter appears in the parameter list of the function */

#ifndef SphericalCoordinateFunctions_H
#define SphericalCoordinateFunctions_H

#include "../Utils.hpp"
#include "../lib/Eigen/Eigen"

using namespace Eigen;

float cosTheta(const Vector3f &w)
{
    return w[1];
}

float cos2Theta(const Vector3f &w)
{
    float value = cosTheta(w);
    return value * value;
}

float sinTheta(const Vector3f &w)
{
    return sqrt(1 - cos2Theta(w));
}

float cosPhi(const Vector3f &w)
{
    float r = sinTheta(w);
    if (r == 0)
        return 0;
    else
    {
        return clamp(w[0] / r, -1, 1);
    }
}

float sinPhi(const Vector3f &w)
{
    return sqrt(1 - pow(cosPhi(w), 2));
}

#endif