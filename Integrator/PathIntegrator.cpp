#include "PathIntegrator.hpp"

Vector3f PathIntegrator::Li(Ray &ray, const Scene &scene)
{
    Vector3f beta = Vector3f(1, 1, 1), Li = Vector3f(0, 0, 0);

    DirectLightIntegrator directLightIntegrator(this->camera, this->sampler, this->maxDepth);

    for (int bounds = 0; bounds < maxDepth; bounds++)
    {
        SurfaceInteraction interaction;
        bool isIntersect = scene.Intersect(ray, interaction);

        if (bounds == 0)
        {
            if (isIntersect)
            {
                Li += beta * interaction.Le(-ray.dir);
            }
        }
        if (!isIntersect || bounds >= maxDepth)
        {
            break;
        }

        Li += beta * directLightIntegrator.UniformSampleOneLight(interaction, scene);

        Vector3f wi, currentW0 = -ray.dir;
        float currentPdf;
        BxDFType flag = ALL;
        Vector3f currentFr = interaction.bsdf->sample_fr(currentW0, wi, currentPdf, sampler->get2D(), flag);

        if (currentFr.isZero() || currentPdf == 0)
        {
            break;
        }

        // if (currentPdf < 0)
        // {
        //     std::cout << "here1"
        //               << " ";
        // }

        beta = beta * currentFr * abs(wi.dot(interaction.norm)) / currentPdf;
        ray = interaction.SpawnRay(wi);

        float contrib = RussianRoulette(beta.y());
        if (bounds > 3)
        {
            float q = 1 - RussianRoulette(beta.y());
            if (sampler->get1D() < q)
            {
                break;
            }
            beta /= 1 - q;
        }
    }

    return Li;
}

PathIntegrator::~PathIntegrator()
{
}
