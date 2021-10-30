#ifndef DirectLightIntegrator_H
#define DirectLightIntegrator_H

#include "SamplerIntegrator.hpp"

class DirectLightIntegrator : public SamplerIntegrator
{
private:
    /* data */
public:
    DirectLightIntegrator(std::shared_ptr<Camera> _camera,
                          std::shared_ptr<Sampler> _sampler, int _maxDepth) : SamplerIntegrator(_camera, _sampler), maxDepth(_maxDepth){};
    ~DirectLightIntegrator();

    void Render(const Scene &scene) override;

    Vector3f UniformSampleOneLight(Intersection &intersection, const Scene &scene);
    Vector3f EstimateDirect(Intersection &intersection, std::shared_ptr<Light> light, const Scene &scene);

    int maxDepth;
};

Vector3f DirectLightIntegrator::UniformSampleOneLight(Intersection &intersection, const Scene &scene)
{
    int nlight = scene.lights.size();
    int lightNum = std::min(int(nlight * sampler->get1D()), nlight - 1);
    std::shared_ptr<Light> light = scene.lights[lightNum];

    return nlight * EstimateDirect(intersection, light, scene);
}

Vector3f DirectLightIntegrator::EstimateDirect(Intersection &intersection, std::shared_ptr<Light> light, const Scene &scene)
{
    Vector3f Li(0, 0, 0);

    // sample light
    float lightPdf;
    Vector3f wi;
    VisibilityTester visibility;

    Vector3f L0 = light->sample_Li(sampler->get2D(), lightPdf, wi, intersection, &visibility);

    // if (visibility.p1[0] > 549 && visibility.p1[2] < 500 && visibility.p1[1] < 500 && visibility.Occluded(scene))
    // {
    //     std::cout << visibility.p1 << "\n"
    //               << visibility.p2 << "\n"
    //               << std::endl;
    // }

    if (lightPdf > 0)
    {
        float Pdf = intersection.bsdf->PDF(intersection.w0, wi);
        Vector3f fr = intersection.bsdf->fr(intersection.w0, wi);
        if (Pdf > 0 && !visibility.Occluded(scene))
        {
            float weight = PowerHeuristic(1, lightPdf, 1, Pdf);
            Li += fr * L0 * weight * abs(intersection.norm.dot(wi)) / lightPdf;
        }
    }

    // sample bxdf
    float bxdfPdf;
    Vector3f fr = intersection.bsdf->sample_fr(intersection.w0, wi, bxdfPdf, sampler->get2D());
    if (bxdfPdf > 0)
    {
        float lightPdf = light->Pdf_Li(wi, intersection);
        Vector3f L0 = light->Li(wi, intersection, &visibility);
        if (lightPdf > 0 && !visibility.Occluded(scene))
        {
            float weight = PowerHeuristic(1, bxdfPdf, 1, lightPdf);
            Li += fr * L0 * weight * abs(intersection.norm.dot(wi)) / bxdfPdf;
        }
    }

    return Li;
}

void DirectLightIntegrator::Render(const Scene &scene)
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
                if (scene.Intersect(ray, intersection))
                {
                    if (intersection.primitive->getAreaLight() != NULL)
                    {
                        radiance = Vector3f(1, 1, 1);
                    }
                    else
                    {
                        radiance = UniformSampleOneLight(intersection, scene);
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

DirectLightIntegrator::~DirectLightIntegrator()
{
}

#endif
