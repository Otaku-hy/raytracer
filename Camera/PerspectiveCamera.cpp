#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(Film *_film, float zNear, float zFar, float aspect_ratio, float fov) : Camera(_film)
{
    float height = 2 * tan(radians(fov / 2.0)) * -zNear;
    float width = aspect_ratio * height;

    Matrix4f perspectiveMat, ortho, translateToNDC;
    perspectiveMat << zNear, 0, 0, 0,
        0, zNear, 0, 0,
        0, 0, (zNear + zFar), -zNear * zFar,
        0, 0, 1, 0;

    ortho << 1.0 / width, 0, 0, 0,
        0, 1.0 / height, 0, 0,
        0, 0, 1.0 / (zNear - zFar), -(zNear + zFar) / (2.0 * (zNear - zFar)),
        0, 0, 0, 1;

    translateToNDC << 1, 0, 0, 0.5,
        0, 1, 0, 0.5,
        0, 0, 1, 0.5,
        0, 0, 0, 1;

    perspective(translateToNDC * ortho * perspectiveMat);
    NDC(translateToNDC);
    orthoM(ortho);

    viewPort.inverse();
    perspective.inverse();
    NDC.inverse();
    orthoM.inverse();
}

PerspectiveCamera::~PerspectiveCamera()
{
}

float PerspectiveCamera::GenerateRay(Ray &ray, cameraSample &sample)
{
    Vector3f rasterPos = Vector3f(sample.pFilm[0], sample.pFilm[1], 1.0);
    Vector3f worldPos = rasterToWorld(rasterPos);

    Vector3f dir = (worldPos - cameraPos).normalized();
    // std::cout << dir << std::endl;

    ray.origin = cameraPos;
    ray.dir = dir;

    return 1;
}

Vector3f PerspectiveCamera::rasterToWorld(Vector3f &v) // must repair!!!!
{
    // std::cout << perspective * viewPort * Vector3to4(v, POS) << std::endl;
    return Vector4to3(view * perspective * viewPort * Vector3to4(v, POS));
}