#ifndef BVHAccel_H
#define BVHAccel_H

#include "../pbrt.hpp"
// #include "Aggregate.hpp"
#include "BVHStruct.hpp"
#include "Bounds.hpp"
#include "../Primitive/Primitive.hpp"

enum splitMethod
{
    MIDPOINT,
    EQUAL,
    SAH,
    HLBVH
};

class BVHAccel
{
private:
    /* data */
public:
    BVHAccel() = default;
    BVHAccel(std::vector<std::shared_ptr<Primitive>> &p, splitMethod method, int maxPrim, int &cnt);

    ~BVHAccel();

    BVHNode *recursiveBuild(int start, int end, int &nodeCount, splitMethod method, std::vector<std::shared_ptr<Primitive>> ordered_primitive);
    BVHNode *HLBVHBuild(int &nodeCount, std::vector<std::shared_ptr<Primitive>> &ordered_primitive);

    int partition(int start, int end, float pivot, int axis);

    void radixSort(std::vector<primitiveMorton> &v);
    BVHNode *emitNode(int &nodeCount, int maskBit, std::vector<primitiveMorton> &MortonInfo, std::vector<std::shared_ptr<Primitive>> &ordered_primitive, const int &firstMortonOffset, const int &nPrimitive);
    BVHNode *SAHupperNode(int &nodeCount, int start, int end, std::vector<primitiveInfo> &nodeInfo, std::vector<BVHNode *> treeLet);

    int flattenBVHTree(BVHNode *node, int &currentIndex);

    bool Intersect(const Ray &ray, SurfaceInteraction &interaction);
    bool IntersectP(Ray &ray);

    int maxPrimInNode;
    std::vector<primitiveInfo> pInfo;
    std::vector<primitiveMorton> MortonInfo;
    std::vector<std::shared_ptr<Primitive>> primitive;

    std::vector<LinearBVHNode> linearBVH;
    bucketInfo bucket[nBuckets];
};

#endif