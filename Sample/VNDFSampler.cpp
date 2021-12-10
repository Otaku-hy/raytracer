#include "VNDFSampler.hpp"

Vector2f VNDFSampler::SampleInSlopeSpace(const Vector2f &randValue, const Vector3f &wo)
{
    float tanThetaO = tanTheta(wo);
    if (std::isinf(tanThetaO))
    {
        return Vector2f(0, 0);
    }
    float G1 = 2.0 / (1 + std::sqrt(1 + tanThetaO * tanThetaO));

    float A = 2 * randValue[0] / G1 - 1;
    float B = tanThetaO;

    float xm, ym;

    float A2 = A * A;
    float B2 = B * B;
    float delta = B2 / (A2 - 1) / (A2 - 1) - (A2 - B2) / (A2 - 1);
    if (delta < 0)
        return Vector2f(0, 0);

    float xm1 = B / (A2 - 1) - std::sqrt(delta);
    float xm2 = B / (A2 - 1) + std::sqrt(delta);

    if (A < 0 || xm2 > (1.0 / tanThetaO))
        xm = xm1;
    else
        xm = xm2;

    float s;
    float u = randValue[1];
    if (u <= 0.5)
    {
        s = 1;
        u = 2 * (u - 0.5);
    }
    else
    {
        s = -1;
        u = 2 * (0.5 - u);
    }

    float z = s * (0.46341 * u - 0.73369 * u * u + 0.27385 * u * u * u) / (0.597999 - u + 0.309420 * u * u + 0.093073 * u * u * u);
    ym = z * std::sqrt(1 + xm * xm);

    return Vector2f(xm, ym);
}