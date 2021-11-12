#include "DirectLightIntegrator.hpp"

Vector3f DirectLightIntegrator::UniformSampleOneLight(SurfaceInteraction &interaction, const Scene &scene)
{
    int nlight = scene.lights.size();
    int lightNum = std::min(int(nlight * sampler->get1D()), nlight - 1);
    std::shared_ptr<Light> light = scene.lights[lightNum];

    return nlight * EstimateDirect(interaction, light, scene);
}

Vector3f DirectLightIntegrator::EstimateDirect(SurfaceInteraction &interaction, std::shared_ptr<Light> light, const Scene &scene)
{
    Vector3f Li(0, 0, 0);

    // sample light
    float lightPdf;
    Vector3f wi;
    VisibilityTester visibility;

    Vector3f L0 = light->sample_Li(sampler->get2D(), lightPdf, wi, interaction, &visibility);

    if (lightPdf > 0)
    {
        float Pdf = interaction.bsdf->PDF(interaction.w0, wi);
        Vector3f fr = interaction.bsdf->fr(interaction.w0, wi);
        if (Pdf > 0 && !visibility.Occluded(scene))
        {
            float weight = PowerHeuristic(1, lightPdf, 1, Pdf);
            Li += fr * L0 * weight * abs(interaction.norm.dot(wi)) / lightPdf;
        }
    }

    // sample bxdf
    float bxdfPdf;
    Vector3f fr = interaction.bsdf->sample_fr(interaction.w0, wi, bxdfPdf, sampler->get2D());
    if (bxdfPdf > 0)
    {
        float lightPdf = light->Pdf_Li(wi, interaction);
        Vector3f L0 = interaction.Le(-wi);

        Ray ray = interaction.SpawnRay(wi);
        SurfaceInteraction itLi;

        scene.Intersect(ray, itLi);
        VisibilityTester visibility(interaction, itLi);

        if (lightPdf > 0 && !visibility.Occluded(scene))
        {
            float weight = PowerHeuristic(1, bxdfPdf, 1, lightPdf);
            Li += fr * L0 * weight * abs(interaction.norm.dot(wi)) / bxdfPdf;
        }
    }

    // std::cout << "\n\n\n";

    return Li;
}

Vector3f DirectLightIntegrator::Li(Ray &ray, const Scene &scene)
{
    Vector3f L(0, 0, 0);
    SurfaceInteraction interaction;
    if (!scene.Intersect(ray, interaction))
    {
        // add envirment luminous in the future
        return L;
    }
    L += interaction.Le(-ray.dir);
    L += UniformSampleOneLight(interaction, scene);

    return L;
}

DirectLightIntegrator::~DirectLightIntegrator()
{
}
