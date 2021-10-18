#ifndef SampledSpectrum_H
#define SampledSpectrum_H

#include <vector>
#include <algorithm>

#include "CoefficientSpectrum.hpp"

const int nSpectralSamples = 60;
const int sampledLambdaStart = 400;
const int sampledLambdaEnd = 700;

class SampledSpectrum : public CoefficientSpectrum<nSpectralSamples>
{
private:
    /* data */
public:
    SampledSpectrum() = default;
    SampledSpectrum(float v = 0.0f) : CoefficientSpectrum(v){};
    ~SampledSpectrum();

    SampledSpectrum FromSampled(float *lambda, float *value, int n);
    float averageSpectrumSamples(float *lambda, float *value, int n, int lambda0, int lambda1);
};

SampledSpectrum SampledSpectrum::FromSampled(float *lambda, float *value, int n)
{
    SampledSpectrum ret(0);

    std::vector<Vector2f> v(n);
    for (int i = 0; i < n; i++)
    {
        v[i][0] = lambda[i];
        v[i][1] = value[i];
    }
    std::sort(&v[0], &v[n - 1] + 1, [](const Vector2f &v1, const Vector2f &v2)
              { return v1[0] < v2[0]; });
    for (int i = 0; i < n; i++)
    {
        lambda[i] = v[i][0];
        value[i] = v[i][1];
    }

    for (int i = 0; i < nSpectralSamples; i++)
    {
        float lambda0 = lerp(float(i) / nSpectralSamples, sampledLambdaStart, sampledLambdaEnd);
        float lambda1 = lerp(float(i + 1) / nSpectralSamples, sampledLambdaStart, sampledLambdaEnd);

        ret.c[i] = averageSpectrumSamples(lambda, value, n, lambda0, lambda1);
    }
}

float SampledSpectrum::averageSpectrumSamples(float *lambda, float *value, int n, int lambda0, int lambda1)
{
    if (lambda0 > lambda[n - 1])
        return value[n - 1];
    if (lambda1 < lambda[0])
        return value[0];
    if (n == 1)
        return value[0];

    float sum;

    if (lambda0 < lambda[0])
    {
        sum += (lambda[0] - lambda0) * value[0];
        lambda0 = lambda[0];
    }
    if (lambda1 > lambda[n - 1])
    {
        sum += (lambda1 - lambda[n - 1]) * value[n - 1];
        lambda1 = lambda[n - 1];
    }

    int i = 0;
    int j = n - 1;
    while (lambda0 >= lambda[i])
    {
        i++;
    }
    float valueT = lerp((lambda0 - lambda[i - 1]) / (lambda[i] - lambda[i - 1]), value[i - 1], value[i]);
    sum += 0.5 * (valueT + value[i]) * (lambda[i] - lambda0);
    while (lambda1 <= lambda[j])
    {
        j--;
    }
    float valueT = lerp((lambda0 - lambda[j]) / (lambda[j + 1] - lambda[j]), value[j], value[j + 1]);
    sum += 0.5 * (valueT + value[j]) * (lambda1 - lambda[j]);

    for (; i < j; i++)
    {
        sum += 0.5 * (value[i] + value[i + 1]) * (lambda[i + 1] - lambda[i]);
    }
}

SampledSpectrum::~SampledSpectrum()
{
}

#endif