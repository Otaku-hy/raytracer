#include "pbrt.hpp"
#include "OBJ_Loader.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "GeometryPrimitive.hpp"
#include "AreaLight.hpp"
#include "MatteMaterial.hpp"
#include "SpecularMaterial.hpp"
#include "PlasticMaterial.hpp"
#include "BSSRDF.hpp"
#include "Metal.hpp"
#include "SubsurfaceMaterial.hpp"
#include "MitchellFilter.hpp"
#include "PerspectiveCamera.hpp"
#include "StratifiedSampler.hpp"
#include "PathIntegrator.hpp"

// void SetModel(const std::string &name, std::vector<std::shared_ptr<Primitive>> &p, std::vector<std::shared_ptr<Light>> &lights)
// {
//     std::shared_ptr<Matrix4_4> P = std::make_shared<Matrix4_4>();
//     std::shared_ptr<Matrix4_4> O = std::make_shared<Matrix4_4>();

//     std::shared_ptr<Loader> model = std::make_shared<Loader>(name);

//     std::shared_ptr<TriangleMesh> mesh;
//     model->CreateTriangleMesh(mesh);
// }

void Preprocess(std::vector<std::shared_ptr<Primitive>> &p, std::vector<std::shared_ptr<Light>> &lights)
{
    std::shared_ptr<Loader> model1 = std::make_shared<Loader>("./Model/tallbox.obj");
    std::shared_ptr<Loader> model2 = std::make_shared<Loader>("./Model/shortbox.obj");
    std::shared_ptr<Loader> model3 = std::make_shared<Loader>("./Model/right.obj");
    std::shared_ptr<Loader> model4 = std::make_shared<Loader>("./Model/left.obj");
    std::shared_ptr<Loader> model5 = std::make_shared<Loader>("./Model/floor.obj");
    std::shared_ptr<Loader> model6 = std::make_shared<Loader>("./Model/light.obj");

    std::shared_ptr<TriangleMesh> mesh1, mesh2, mesh3, mesh4, mesh5, mesh6;
    model1->CreateTriangleMesh(mesh1);
    model2->CreateTriangleMesh(mesh2);
    model3->CreateTriangleMesh(mesh3);
    model4->CreateTriangleMesh(mesh4);
    model5->CreateTriangleMesh(mesh5);
    model6->CreateTriangleMesh(mesh6);

    std::shared_ptr<Matrix4_4> P = std::make_shared<Matrix4_4>();
    std::shared_ptr<Matrix4_4> O = std::make_shared<Matrix4_4>();

    Vector3f lightColor(8.0f * Vector3f(0.747f + 0.058f, 0.747f + 0.258f, 0.747f) + 15.6f * Vector3f(0.740f + 0.287f, 0.740f + 0.160f, 0.740f) + 18.4f * Vector3f(0.737f + 0.642f, 0.737f + 0.159f, 0.737f));

    for (int i = 0; i < mesh1->nTriangles; i++)
    {
        std::shared_ptr<Triangle> tri(new Triangle(mesh1, i, P, O));
        /* choose different material */
        std::shared_ptr<Material> m = std::make_shared<MatteMaterial>(Vector3f(0.84f, 0.85f, 0.88f), 20);
        // std::shared_ptr<Material> m = std::make_shared<Metal>(Vector3f(1, 1, 1),Vector3f(1.0,1.0,1.0),Vector3f(0.46094, 0.46094, 0.46094), Vector3f(2.9735, 2.9735, 2.9735), 0.015);
        std::shared_ptr<AreaLight> l = NULL;
        std::shared_ptr<GeometryPrimitive> gP(new GeometryPrimitive(tri, m, l));
        p.push_back(gP);
    }

    // 注释掉该物体
    for (int i = 0; i < mesh2->nTriangles; i++)
    {
        std::shared_ptr<Triangle> tri(new Triangle(mesh2, i, P, O));
        std::shared_ptr<Material> m = std::make_shared<MatteMaterial>(Vector3f(1.0, 1.0, 1.0), 20);
        // std::shared_ptr<Material> m = std::make_shared<SpecularMaterial>(Vector3f(1, 1, 1), 1.0, 1.5);
        std::shared_ptr<AreaLight> l = NULL;
        std::shared_ptr<GeometryPrimitive> gP(new GeometryPrimitive(tri, m, l));
        p.push_back(gP);
    }
    for (int i = 0; i < mesh3->nTriangles; i++)
    {
        std::shared_ptr<Triangle> tri(new Triangle(mesh3, i, P, O));
        std::shared_ptr<Material> m = std::make_shared<MatteMaterial>(Vector3f(0, 0.67f, 0), 0);
        std::shared_ptr<AreaLight> l = NULL;
        std::shared_ptr<GeometryPrimitive> gP(new GeometryPrimitive(tri, m, l));
        p.push_back(gP);
    }
    for (int i = 0; i < mesh4->nTriangles; i++)
    {
        std::shared_ptr<Triangle> tri(new Triangle(mesh4, i, P, O));
        std::shared_ptr<Material> m = std::make_shared<MatteMaterial>(Vector3f(0.69f, 0, 0), 0);
        std::shared_ptr<AreaLight> l = NULL;
        std::shared_ptr<GeometryPrimitive> gP(new GeometryPrimitive(tri, m, l));
        p.push_back(gP);
    }
    for (int i = 0; i < mesh5->nTriangles; i++)
    {
        std::shared_ptr<Triangle> tri(new Triangle(mesh5, i, P, O));
        std::shared_ptr<Material> m = std::make_shared<MatteMaterial>(Vector3f(0.84f, 0.85f, 0.88f), 0);
        std::shared_ptr<AreaLight> l = NULL;
        std::shared_ptr<GeometryPrimitive> gP(new GeometryPrimitive(tri, m, l));
        p.push_back(gP);
    }

    for (int i = 0; i < mesh6->nTriangles; i++)
    {
        std::shared_ptr<Triangle> tri(new Triangle(mesh6, i, P, O));
        std::shared_ptr<Material> m = std::make_shared<MatteMaterial>(Vector3f(1, 1, 1), 0);
        std::shared_ptr<AreaLight> l = std::make_shared<AreaLight>(tri, 1, lightColor);
        std::shared_ptr<GeometryPrimitive> gP(new GeometryPrimitive(tri, m, l));
        p.push_back(gP);
        lights.push_back(l);
    }

    // std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3f(370, 385.5, 350), 100);
    // std::shared_ptr<Material> m = std::make_shared<PlasticMaterial>(Vector3f(1, 1, 1), 1.0, 1.55, 1.413/2.0);
    // // std::shared_ptr<Material> m = std::make_shared<SpecularMaterial>(Vector3f(1, 1, 1), 1.0, 1.55);
    // std::shared_ptr<AreaLight> l = NULL;
    // std::shared_ptr<GeometryPrimitive> gP(new GeometryPrimitive(sphere, m, l));
    // p.push_back(gP);

    //取消注释
    // std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3f(130, 100, 225), 100);
    // // std::shared_ptr<Material> m = std::make_shared<PlasticMaterial>(Vector3f(1, 1, 1), 1.0, 1.5, 1.413/2.0);
    // // std::shared_ptr<Material> m = std::make_shared<SubsurfaceMaterial>(1.0, 1.3, 2.3, 0.03, 0.8, 120.0);
    // std::shared_ptr<Material> m = std::make_shared<Metal>(Vector3f(1, 1, 1),Vector3f(1.0,1.0,1.0),Vector3f(0.46094, 0.46094, 0.46094), Vector3f(2.9735, 2.9735, 2.9735), 0.06);
    // // std::shared_ptr<Material> m = std::make_shared<SpecularMaterial>(Vector3f(1, 1, 1), 1.0, 1.5);
    // std::shared_ptr<AreaLight> l = NULL;
    // std::shared_ptr<GeometryPrimitive> gP(new GeometryPrimitive(sphere, m, l));
    // p.push_back(gP);


    
    // std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3f(270, 270, 225), 120);
   
    // std::shared_ptr<Material> m = std::make_shared<Metal>(Vector3f(1, 1, 1),Vector3f(1.0,1.0,1.0),Vector3f(0.46094, 0.46094, 0.46094), Vector3f(2.9735, 2.9735, 2.9735), 0.08f);
    // // std::shared_ptr<Material> m = std::make_shared<SpecularMaterial>(Vector3f(1, 1, 1), 1.0, 1.5);
    // std::shared_ptr<AreaLight> l = NULL;
    // std::shared_ptr<GeometryPrimitive> gP(new GeometryPrimitive(sphere, m, l));
    // p.push_back(gP);
}

void Init(std::vector<std::shared_ptr<Primitive>> &p, std::vector<std::shared_ptr<Light>> &lights)
{
    int nodeCount = 0;
    BVHAccel BVH(p, SAH, 256, nodeCount);


    //选择filter
    std::shared_ptr<Filter> filter(new MitchellFilter(Vector2f(2.0f, 2.0f), 1 / 3.0f, 1 / 3.0f));
    // std::shared_ptr<Filter> filter(new GaussianFilter(Vector2f(2.0f, 2.0f), 1.413f));

    Film *film = new Film(Vector2i(800, 800), "image.ppm", filter);
    std::shared_ptr<Camera> camera(new PerspectiveCamera(film, -0.1, -5000.0, 125.0 / 125.0, 38.0));
    camera->setViewMat(Vector3f(278, 273, -800), Vector3f(278, 273, 100), Vector3f(0, 1, 0));
    std::shared_ptr<StratifiedSampler> stratified_sampler = std::make_shared<StratifiedSampler>(5, 5, true);
    stratified_sampler->AddSampler2D("raySample");
    Scene scene(std::make_shared<BVHAccel>(BVH), lights);
    //选择integrator
    std::shared_ptr<Integrator> integrator = std::make_shared<PathIntegrator>(camera, stratified_sampler, 7);
    // std::shared_ptr<Integrator> integrator = std::make_shared<DirectLightIntegrator>(camera, stratified_sampler, 3);
    integrator->Render(scene);
}

int main()
{
    srand(time(NULL));
    std::vector<std::shared_ptr<Primitive>> p;
    std::vector<std::shared_ptr<Light>> light;

    Preprocess(p, light);

    Init(p, light);

}