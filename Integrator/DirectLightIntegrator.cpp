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
    BxDFType flag = ALL;
    float lightPdf;
    Vector3f wi;
    VisibilityTester visibility;

    float tPdf = 0;

    Vector3f L0 = light->sample_Li(sampler->get2D(), lightPdf, wi, interaction, &visibility);

    if (lightPdf > 0)
    {
        float Pdf = interaction.bsdf->PDF(interaction.w0, wi, flag);
        Vector3f fr = interaction.bsdf->fr(interaction.w0, wi, flag);
        if (Pdf > 0 && !visibility.Occluded(scene))
        {
            float weight = PowerHeuristic(1, lightPdf, 1, Pdf);
            Li += fr * L0 * weight * abs(interaction.norm.dot(wi)) / lightPdf;
        }
    }

    //sample bxdf : something wrong with it!!!
    flag = ALL;
    float bsdfPdf;
    Vector3f fr = interaction.bsdf->sample_fr(interaction.w0, wi, bsdfPdf, sampler->get2D(), flag);
    bool isSpecular = false;
    if (flag & SPECULAR)
    {
        isSpecular = true;
    }
    fr = fr * abs(interaction.norm.dot(wi));

    if (bsdfPdf > 0)
    {
        float weight = 1;

        float lightPdf = light->Pdf_Li(wi, interaction);
        Ray ray = interaction.SpawnRay(wi);
        SurfaceInteraction itLi;
        bool foundItLi = scene.Intersect(ray, itLi);

        Vector3f L0(0, 0, 0);
        if (foundItLi && itLi.primitive->getAreaLight() == light.get())
        {
            L0 = itLi.Le(-wi);
        }
        VisibilityTester visibility(interaction, itLi);

        if (!isSpecular)
        {
            weight = PowerHeuristic(1, bsdfPdf, 1, lightPdf);
        }

        if (lightPdf > 0 && !visibility.Occluded(scene))
        {
            Li += fr * L0 * weight / bsdfPdf;
        }
    }

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
