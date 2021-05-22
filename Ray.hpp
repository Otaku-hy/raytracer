#ifndef Ray_H
#define Ray_H
#include "lib/Eigen/Core"

using namespace Eigen;

class Ray
{
private:
    /* data */
public:
    Ray(Vector3f _origin, Vector3f _dir);
    ~Ray();

    Vector3f origin;
    Vector3f dir;
};

Ray::Ray(Vector3f _origin, Vector3f _dir)
{
    origin = _origin;
    dir = _dir;
}

Ray::~Ray()
{
}
#endif