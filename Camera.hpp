#ifndef Camera_H
#define Camera_H
#include "lib/Eigen/Eigen"
#include "Utils.hpp"
#include <vector>
using namespace Eigen;

Vector3f screen[480][260];

class Camera
{
private:
    /* data */
public:
    Camera(Vector3f _pos, Vector3f _lookPos, Vector3f _up, int _width, int _height, int _SPP);
    ~Camera();
    void image_color();

    Vector3f pos;
    Vector3f cameraDir;
    Vector3f up;
    Vector3f horizon;

    int SPP;

    int width;
    int height;

    Matrix3f translate;
};

Camera::Camera(Vector3f _pos, Vector3f _lookPos, Vector3f _up, int _width, int _height, int _SPP)
{
    pos = _pos;
    cameraDir = (_pos - _lookPos).normalized();
    horizon = _up.cross(cameraDir);
    up = cameraDir.cross(horizon);

    SPP = _SPP;

    width = _width;
    height = _height;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            screen[i][j] = Vector3f(0, 0, 0);
        }
    }

    translate<<
        horizon.x(),up.x(),cameraDir.x(),
        horizon.y(),up.y(),cameraDir.y(),
        horizon.z(),up.z(),cameraDir.z();
}

Camera::~Camera()
{
}

void Camera::image_color()
{
    std::cout << "P3\n"
              << width << ' ' << height << "\n255\n";

    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            gamma_correct(screen[i][height - 1 - j]);
            int ir = static_cast<int>(255.999 * screen[i][height - 1 - j].x());
            int ig = static_cast<int>(255.999 * screen[i][height - 1 - j].y());
            int ib = static_cast<int>(255.999 * screen[i][height - 1 - j].z());

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}

#endif