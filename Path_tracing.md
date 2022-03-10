### A deep understanding of Path Tracing algorithm

##### basic formula

First, we know the basic radiometry equilibrium:
$$
L(p,\omega_0) = L_e(p,\omega_0) + \int_{S^2}L(\omega_i)fr(p,\omega_i,\omega_0)cos\theta_id\omega
$$
Since evaluating the whole scene with every solid angel seems a little bit difficult, so we only evaluating the scene where the object exists(i.e. there exists light or shapes):
$$
L(p,\omega_0) = L_e(p,\omega_0) + \int_AL_e(p_2\rightarrow p_1)fr(p_2 \rightarrow p_1 \rightarrow p_0)G(p_2,p_1)dA +\\ \int_A\int_AL_e(p_3\rightarrow p_2)fr(p_3\rightarrow p_2 \rightarrow p_1)G(p_3,p_2)fr(p_2 \rightarrow p_1 \rightarrow p_0)G(p_2,p_1)dAdA + ...
$$
Here, $G(p_i,p_{i-1}) = \frac {V(p_i,p_{i-1})cos\theta_{p_i}cos\theta_{p_{i-1}}} {dis^2(p_i,p_{i-1})}$, $p_0$ means the position on the camera, that is, the value after computing using pathtracing will finally write on this position on the film. Then $p_1$ means the first intersect point in the scene and so on. So, the equation can be considered as the sum contribution of all point in the scene (i.e. we can get the idea that the first term of the equation means the inherent emission of $p_0$,then the second term of the equation means the radiance contribution by one time reflection ...)

##### integral over path

Then, we can definite that $P(p_i)$ give the contribution with i vertices on the ray(here we define the first intersect position as the first vertex,and the last position on the light as the ith vertex ,and:
$$
P(p_i) = \int\int ...\int_{i-1}L_e(p_i\rightarrow p_{i-1})fr(p_i\rightarrow p_{i-1}\rightarrow p_{i-2})G(p_i,p_{i-1}) \\\cross \prod_{j=2}^{i-1}fr(p_j\rightarrow p_{j-1}\rightarrow p_{j-2})G(p_j,p_{i-1}) dA(p_i)dA(p_{i-1})...
$$
So the equation we derived before can rewrite in a brief form:
$$
L(p_1\rightarrow p_0) = \sum_{i=1}^{\infty}P(p_i)
$$

##### sampling

But it still hard to process integral in graphics, so we also use Morte Carlo to make it eaiser to evaluate.

Considering a light path, we randomly select the $j_{th}$( j = 1,2 ...) vertex on the surface of any object. As the result, the PDF for the path can be written as:
$$
P_A(p_i)=\frac{A_j}{\sum_{j}A_j}\frac{1}{A_j}=\frac{1}{\sum_{j}A_j}
$$
In fact, sampling path in this manner can cause some fateful problem. So we will improve this manner to solve some problems.

##### incremental path construction

Here, for the i~th~ vertex, we sampled the BSDF, generating a ray from p~i~ to the next vertex p~i+1~.

Since the light transpot equation is an integral over the surface area, so the PDF for BSDF should be converted from solid angle form to area form:
$$
P_A = P_\omega \frac{cos\theta_i}{||p_i - p_{i-1}||^2}
$$
Because the term $G(p_i,p_{i-1})$ term cancel out the $P_A$ term, the value of the Monte Carlo for the path is:
$$
P(p_i) = \frac{L_e(p_i\rightarrow p_{i-1})fr(p_i\rightarrow p_{i-1}\rightarrow p_{i-2})G(p_i,p_{i-1})}{p_A(p_i)} \\\cross \prod_{j=2}^{i-1}\frac{fr(p_j\rightarrow p_{j-1}\rightarrow p_{j-2})cos\theta_j}{P_\omega(p_j,p_{j-1})}
$$

##### implementation

For the implementation,  we use the pdf of direct light from previous chapter, that is, the  multiple importance sampling. Also, we will reuse the point in the path so that we don't need to choose others points in the scene to compute $P(p_i)$ .

Here's the code:

```c++
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

        if (!interaction.bsdf)
        {
            bounds--;
            break;
        }

        Li += beta * directLightIntegrator.UniformSampleOneLight(interaction, scene);

        Vector3f wi, currentW0 = -ray.dir;
        float currentPdf;
        Vector3f currentFr = interaction.bsdf->sample_fr(currentW0, wi, currentPdf, sampler->get2D());

        if (currentFr.isZero() || currentPdf == 0)
        {
            break;
        }
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
```



