#ifndef SamplerIntegrator_H
#define SamplerIntegrator_H

#include "Integrator.hpp"

#include "../Scene/Scene.hpp"
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

    virtual Vector3f Li(Ray &ray, const Scene &scene) = 0;

    std::shared_ptr<Camera> camera;
    std::shared_ptr<Sampler> sampler;
};

#endif
