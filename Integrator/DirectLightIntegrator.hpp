#ifndef DirectLightIntegrator_H
#define DirectLightIntegrator_H

#include "SamplerIntegrator.hpp"
#include "../Scene/Scene.hpp"
#include "../Light/Visibility.hpp"
#include "../Material/BSDF.hpp"
#include "../Material/BSSRDF.hpp"
#include "../Interaction/SurfaceInteraction.hpp"


class DirectLightIntegrator : public SamplerIntegrator
{
private:
    /* data */
public:
    DirectLightIntegrator(std::shared_ptr<Camera> _camera,
                          std::shared_ptr<Sampler> _sampler, int _maxDepth) : SamplerIntegrator(_camera, _sampler), maxDepth(_maxDepth){};
    ~DirectLightIntegrator();

    Vector3f Li(Ray &ray, const Scene &scene) override;

    Vector3f UniformSampleOneLight(SurfaceInteraction &interaction, const Scene &scene);
    Vector3f EstimateDirect(SurfaceInteraction &interaction, std::shared_ptr<Light> light, const Scene &scene);

    int maxDepth;
};

#endif
