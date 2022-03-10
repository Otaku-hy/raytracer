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
#include <map>
#include <optional>
#include <ctime>

#include "Eigen/Eigen"

#include "Utils/Utils.hpp"
#include "Utils/MatrixFunctions.hpp"
#include "Utils/MonteCarloSamples.hpp"
#include "Utils/SphericalCoordFuncs.hpp"
#include "Utils/FresnelFunctions.hpp"

using namespace Eigen;

class Scene;
class Shape;
class Primitive;
class Light;
class AreaLight;
class VisibilityTester;
class BxDF;
class BSDF;
class BSSRDF;
class BssrdfAdaptor;
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
class SpecularMaterial;
class PlasticMaterial;
class Metal;
class SubsurfaceMaterial;
class bucketInfo;

const int nBuckets = 12;
const int sortBit = 6;
const int sortTime = 3 * mortonBit / sortBit;
const int filterTableWidth = 16;
const int bssrdfCDFTableWidth = 20;  

const float cdfTable[bssrdfCDFTableWidth] = {0,0.1,0.2,0.35,0.45,0.6,0.75,0.95,1.1,1.3,1.55,1.8,2.1,2.45,2.9,3.4,4.05,4.85,6.05,8.15}; // table for d = 1

#endif