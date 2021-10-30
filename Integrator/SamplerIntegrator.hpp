#ifndef SamplerIntegrator_H
#define SamplerIntegrator_H

#include "Integrator.hpp"

#include "../Camera/Camera.hpp"
#include "../Sample/Sampler.hpp"

class SamplerIntegrator : public Integrator
{
private:
    /* data */
public:
    SamplerIntegrator(std::shared_ptr<Camera> _camera,
                      std::shared_ptr<Sampler> _sampler) : camera(_camera), sampler(_sampler){};
    ~SamplerIntegrator();

    void Render(const Scene &scene) override;

    std::shared_ptr<Camera> camera;
    std::shared_ptr<Sampler> sampler;
};

void SamplerIntegrator::Render(const Scene &scene)
{
    for (int i = 0; i < camera->film->fullResolution[0]; i++)
    {
        for (int j = 0; j < camera->film->fullResolution[1]; j++)
        {

            for (int k = 0; k < sampler->sampleNum; k++)
            {
                Ray ray;
                cameraSample sample;
                Intersection intersection;
                Vector3f radiance(0.0f, 0.0f, 0.0f);

                sampler->startSampler(Vector2f(i, j));
                Vector2f rasterBias = sampler->getSample2D(0, k);
                sample.pFilm = Vector2f(i, j) + rasterBias;

                float sampleWeight = camera->GenerateRay(ray, sample);
                if (scene.Intersect(ray, intersection) == true)
                {
                    AreaLight *light = intersection.primitive->getAreaLight();
                    if (light)
                    {
                        radiance = light->L();
                    }
                    else
                    {
                        radiance = absVec(intersection.norm);
                    }
                }
                else
                {
                    radiance = Vector3f(0.0, 0.0, 0.0);
                }

                camera->film->addContribution(sample.pFilm, radiance, sampleWeight);
            }
        }
    }

    camera->film->imageColor();
}

SamplerIntegrator::~SamplerIntegrator()
{
}

#endif
