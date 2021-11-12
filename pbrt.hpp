#ifndef PBRT_H
#define PBRT_H

#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <limits.h>
#include <fstream>
#include <sstream>

#include "lib/Eigen/Eigen"

#include "Utils/Utils.hpp"
#include "Utils/MatrixFunctions.hpp"
#include "Utils/MonteCarloSamples.hpp"
#include "Utils/SphericalCoordFuncs.hpp"

using namespace Eigen;

class Scene;
class Shape;
class Primitive;
class Light;
class AreaLight;
class VisibilityTester;
class BxDF;
class BSDF;
class Interaction;
class SurfaceInteraction;
class Material;
class Filter;
class Camera;
class Intergrator;
class Sampler;
class Ray;
class BVHAccel;
class Bound3D;
class Material;
class MatteMaterial;
class bucketInfo;

const int nBuckets = 12;
const int sortBit = 6;
const int sortTime = 3 * mortonBit / sortBit;
const int filterTableWidth = 16;

#endif