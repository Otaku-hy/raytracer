#ifndef BVHStruct_H
#define BVHStruct_H

#include "pbrt.hpp"
#include "Bounds.hpp"

struct BVHNode
{
    Bound3D bound;
    BVHNode *lchild, *rchild;
    int firstPOffset, splitAxis, nPrimitive;

    void leafNode(int n, int first, const Bound3D &b)
    {
        lchild = rchild = NULL;
        nPrimitive = n;
        firstPOffset = first;
        bound = b;
    }

    void interiorNode(BVHNode *lc, BVHNode *rc, int axis, const Bound3D &b)
    {
        lchild = lc;
        rchild = rc;
        splitAxis = axis;
        bound = b;
    }
    void interiorNode(BVHNode *lc, BVHNode *rc, int axis)
    {
        lchild = lc;
        rchild = rc;
        bound = Union(lc->bound, rc->bound);
        splitAxis = axis;
    }
};

struct primitiveInfo
{
    Vector3f center;
    Bound3D bound;
    size_t primIndex;

    primitiveInfo(Bound3D b, size_t _primIndex) : bound(b), center((b.pMin + b.pMax) / 2.0), primIndex(_primIndex){};
};

struct bucketInfo
{
    int count = 0;
    Bound3D bound;
};

struct primitiveMorton
{
    int primIndex;
    uint32_t mortonCode;

    primitiveMorton(int _index, uint32_t _mortonCode) : primIndex(_index), mortonCode(_mortonCode){};
};

struct HLBVHtreeLet
{
    int nPrimitve;
    int firstMOffset;
    HLBVHtreeLet(int _nPrimitive, int _offset) : nPrimitve(_nPrimitive), firstMOffset(_offset){};
};

struct LinearBVHNode
{
    Bound3D bound;
    int primitivesOffset;
    int secondChildOffset;

    uint16_t nPrimitve;
    uint8_t splitAxis;
};

#endif
