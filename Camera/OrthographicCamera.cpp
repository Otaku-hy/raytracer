#include "OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(Film *_film, Bound3D bound) : Camera(_film)
{
    Matrix4f translateToOrigin;
    Matrix4f translateToNDC;
    Matrix4f scale;

    scale << 1.0f / bound.edges.a, 0, 0, 0,
        0, 1.0f / bound.edges.b, 0, 0,
        0, 0, 1.0f / bound.edges.c, 0,
        0, 0, 0, 1;
    translateToOrigin << 1, 0, 0, -(bound.pMin[0] + bound.pMax[0]) / 2.0f,
        0, 1, 0, -(bound.pMin[1] + bound.pMax[1]) / 2.0f,
        0, 0, 1, -(bound.pMin[2] + bound.pMax[2]) / 2.0f,
        0, 0, 0, 1;
    translateToNDC << 1, 0, 0, 0.5,
        0, 1, 0, 0.5,
        0, 0, 1, 0.5,
        0, 0, 0, 1;
    ortho = translateToNDC * scale * translateToOrigin;
}

OrthographicCamera::~OrthographicCamera()
{
}
