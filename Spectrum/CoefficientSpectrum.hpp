#ifndef CoefficientSpectrum_H
#define CoefficientSpectrum_H

#include "../Utils/Utils.hpp"
#include "../lib/Eigen/Eigen"

using namespace Eigen;

template <int nSpectrumSamples>
class CoefficientSpectrum
{
private:
    /* data */
public:
    CoefficientSpectrum() = default;
    CoefficientSpectrum(float v = 0.0f)
    {
        for (int i = 0; i < nSpectrumSamples; i++)
        {
            c[i] = v;
        }
    };
    ~CoefficientSpectrum() = default;

    CoefficientSpectrum operator*(float v) const
    {
        CoefficientSpectrum ret = *this;
        for (int i = 0; i < nSpectrumSamples; i++)
        {
            ret[i] *= v;
        }
        return ret;
    }

    CoefficientSpectrum &operator+=(CoefficientSpectrum &s2)
    {
        for (int i = 0; i < nSpectrumSamples; i++)
        {
            c[i] += s2.c[i];
        }
        return *this;
    };

    CoefficientSpectrum operator+(CoefficientSpectrum &s2) const
    {
        CoefficientSpectrum ret = *this;
        for (int i = 0; i < nSpectrumSamples; i++)
        {
            ret[i] += s2.c[i];
        }
        return ret;
    };

    float operator[](size_t index)
    {
        return c[index];
    }

    CoefficientSpectrum clamp(float low, float high) const
    {
        CoefficientSpectrum ret;
        for (int i = 0; i < nSpectrumSamples; i++)
        {
            ret[i] = clamp(c[i], low, high);
        }
        return ret;
    }

    float c[nSpectrumSamples];
};


template <typename T>
T lerp(float t, const T &s1, const T &s2)
{
    return (1 - t) * s1 + t * s2;
}

#endif