#include "SamplerIntegrator.hpp"

void SamplerIntegrator::Render(const Scene &scene)
{
    omp_set_num_threads(12);
    #pragma omp parallel for
    for (int i = 0; i < camera->film->fullResolution[0]; i++)
    {
        for (int j = 0; j < camera->film->fullResolution[1]; j++)
        {

            for (int k = 0; k < sampler->sampleNum; k++)
            {
                Ray ray;
                cameraSample sample;
                sampler->startSampler(Vector2f(i, j), "raySample");
                Vector2f rasterBias = sampler->getSample2D("raySample", k);
                sample.pFilm = Vector2f(i, j) + rasterBias;
                float sampleWeight = camera->GenerateRay(ray, sample);

                // Vector3f radiance = Li(ray, scene);
                Vector3f radiance(0,0,0);

                //  camera->film->addContribution(sample.pFilm, radiance, sampleWeight);
            }
        }
    }

    camera->film->imageColor();
}

Vector3f SamplerIntegrator::Li(Ray &ray, const Scene &scene)
{
    return Vector3f(0, 0, 0);
}

SamplerIntegrator::~SamplerIntegrator()
{
}