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
    
    ~DirectLightIntegrator() override;
    Vector3f Li(Ray &ray, const Scene &scene) override;

    static Vector3f UniformSampleOneLight(SurfaceInteraction &interaction, const Scene &scene, std::shared_ptr<Camera> camera,
                                          std::shared_ptr<Sampler> sampler);
    static Vector3f EstimateDirect(SurfaceInteraction &interaction, std::shared_ptr<Light> light, const Scene &scene, std::shared_ptr<Camera> camera,
                                   std::shared_ptr<Sampler> sampler);

    int maxDepth;
};

#endif
