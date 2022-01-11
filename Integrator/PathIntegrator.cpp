#include "PathIntegrator.hpp"

Vector3f PathIntegrator::Li(Ray &ray, const Scene &scene)
{
    Vector3f beta = Vector3f(1, 1, 1), Li = Vector3f(0, 0, 0);

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

        if (interaction.bsdf)
        {
            Li += beta * DirectLightIntegrator::UniformSampleOneLight(interaction, scene, this->camera, this->sampler);

            Vector3f wi, currentW0 = -ray.dir;
            float currentPdf;
            BxDFType flag = ALL;
            Vector3f currentFr = interaction.bsdf->sample_fr(currentW0, wi, currentPdf, sampler->get2D(), flag);

            if (currentFr.isZero() || currentPdf == 0)
            {
                break;
            }

            beta = beta * currentFr * std::abs(wi.dot(interaction.norm)) / currentPdf;

            ray = interaction.SpawnRay(wi);
        }

        if (interaction.bssrdf)
        {
            SurfaceInteraction iti;
            Vector3f wi, currentW0 = -ray.dir;
            float subscatterPdf;
            Vector3f subscatterFr = interaction.bssrdf->Sample_S(scene, currentW0, iti, subscatterPdf, sampler->get2D());

            if (subscatterPdf == 0 || subscatterFr.isZero())
            {
                if (subscatterFr.isZero())
                {
                    // std::cout  << "here" << std::endl;
                }
                break;
            }

            beta = beta * subscatterFr / subscatterPdf;
            // std::cout << beta << std::endl;
            Vector3f Vtest = DirectLightIntegrator::UniformSampleOneLight(iti, scene, this->camera, this->sampler);
            Li += beta * Vtest;
            // std::cout << "Vtest: " << Vtest[0] << std::endl;
            //           << std::endl;
            // std::cout << Li << std::endl;

            float adaptorPdf;
            BxDFType flag = ALL;
            Vector3f adaptorFr = iti.bsdf->sample_fr(iti.w0, wi, adaptorPdf, sampler->get2D(), flag);

            if (adaptorPdf == 0 || adaptorFr.isZero())
            {
                break;
            }

            beta = beta * adaptorFr * std::abs(wi.dot(iti.norm)) / adaptorPdf;
            ray = iti.SpawnRay(wi);
        }

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
