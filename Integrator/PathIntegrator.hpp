#ifndef PathIntegrator_H
#define PathIntegrator_H

#include "../pbrt.hpp"
#include "SamplerIntegrator.hpp"
#include "DirectLightIntegrator.hpp"

class PathIntegrator : public SamplerIntegrator
{
private:
    /* data */
public:
    PathIntegrator(std::shared_ptr<Camera> _camera, std::shared_ptr<Sampler> _sampler, int _maxDepth) : SamplerIntegrator(_camera, _sampler), maxDepth(_maxDepth){};
    
    ~PathIntegrator() override;
    Vector3f Li(Ray &ray, const Scene &scene) override;

    int maxDepth;
};

#endif