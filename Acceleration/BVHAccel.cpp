#include "BVHAccel.hpp"

BVHAccel::BVHAccel(std::vector<std::shared_ptr<Primitive>> &p, splitMethod method, int maxPrim, int &cnt) : primitive(p), maxPrimInNode(maxPrim)
{
    size_t i = -1;
    for (auto e : primitive)
    {
        pInfo.push_back(primitiveInfo(e->worldBound(), ++i));
    }

    int totalNode = 0;
    std::vector<std::shared_ptr<Primitive>> ordered_primitive;

    BVHNode *root;

    if (method == HLBVH)
    {
        root = HLBVHBuild(totalNode, ordered_primitive);
    }
    else
    {
        root = recursiveBuild(0, primitive.size(), totalNode, method, ordered_primitive);
    }

    cnt = totalNode;

    primitive = ordered_primitive;

    linearBVH = std::vector<LinearBVHNode>(totalNode);

    int orgin = 0;
    flattenBVHTree(root, orgin);
}

BVHNode *BVHAccel::recursiveBuild(int start, int end, int &nodeCount, splitMethod method, std::vector<std::shared_ptr<Primitive>> ordered_primitive)
{
    BVHNode *node = new BVHNode();

    Bound3D b;
    for (int i = start; i < end; i++)
    {
        b = Union(b, pInfo[i].bound);
    }

    int nPrimitive = end - start;
    if (nPrimitive == 1)
    {
        nodeCount++;
        node->leafNode(nPrimitive, ordered_primitive.size(), b);
        for (int i = start; i < end; i++)
            ordered_primitive.push_back(primitive[pInfo[i].primIndex]);
    }
    else
    {
        Bound3D centerBound;
        for (int i = start; i < end; i++)
        {
            centerBound = Union(centerBound, pInfo[i].center);
        }
        int axis = centerBound.maxExtent();
        if (centerBound.pMin[axis] == centerBound.pMax[axis])
        {
            nodeCount++;
            node->leafNode(nPrimitive, ordered_primitive.size(), b);
            for (int i = start; i < end; i++)
                ordered_primitive.push_back(primitive[pInfo[i].primIndex]);
        }
        else
        {
            int mid = 0;
            float cBoundcenter = (centerBound.pMin[axis] + centerBound.pMax[axis]) / 2.0;
            if (method == MIDPOINT)
            {
                mid = partition(start, end, cBoundcenter, axis);
            }
            else if (method == EQUAL)
            {
                mid = (start + end) / 2;
                std::nth_element(&pInfo[start], &pInfo[mid], &pInfo[end - 1] + 1, [axis](const primitiveInfo &a, const primitiveInfo &b)
                                 { return a.center[axis] < b.center[axis]; });
            }
            else if (method == SAH)
            {
                if (nPrimitive <= 4)
                {
                    mid = (start + end) / 2;
                    std::nth_element(&pInfo[start], &pInfo[mid], &pInfo[end - 1] + 1, [axis](const primitiveInfo &a, const primitiveInfo &b)
                                     { return a.center[axis] < b.center[axis]; });
                }
                else
                {
                    //init bucket;
                    for (int i = start; i < end; i++)
                    {
                        int b = nBuckets * centerBound.offset(pInfo[i].center)[axis];
                        if (b == nBuckets)
                            b--;
                        bucket[b].count++;
                        bucket[b].bound = Union(bucket[b].bound, pInfo[i].bound);
                    }
                    //compute cost
                    float cost[nBuckets];
                    for (int i = 0; i < nBuckets - 1; i++)
                    {
                        Bound3D b0, b1;
                        int cnt0 = 0;
                        int cnt1 = 0;
                        for (int j = 0; j <= i; j++)
                        {
                            cnt0++;
                            b0 = Union(b0, bucket[j].bound);
                        }
                        for (int j = i + 1; j < nBuckets; j++)
                        {
                            cnt1++;
                            b1 = Union(b1, bucket[j].bound);
                        }

                        cost[i] = 0.125 + (b0.surfaceArea() * cnt0 + b1.surfaceArea() * cnt1) / b.surfaceArea();
                    }
                    //min cost
                    int splitBucket;
                    float minCost = cost[0];
                    for (int i = 1; i < nBuckets - 1; i++)
                    {
                        if (cost[i] < minCost)
                        {
                            minCost = cost[i];
                            splitBucket = i;
                        }
                    }
                    //either leaf or split
                    float leafCost = nPrimitive;
                    if (nPrimitive > maxPrimInNode || minCost < leafCost)
                    {
                        primitiveInfo *pmid = std::partition(&pInfo[start], &pInfo[end - 1] + 1, [&](const primitiveInfo &p)
                                                             {
                                                                 int b = nBuckets * centerBound.offset(p.center)[axis];
                                                                 if (b == nBuckets)
                                                                     b--;
                                                                 return b < splitBucket;
                                                             });
                        mid = pmid - &pInfo[0];
                    }
                    else
                    {
                        nodeCount++;
                        node->leafNode(nPrimitive, ordered_primitive.size(), b);
                        for (int i = start; i < end; i++)
                        {
                            ordered_primitive.push_back(primitive[pInfo[i].primIndex]);
                        }
                    }
                }
            }
            if (node->nPrimitive == 0)
            {
                nodeCount++;

                node->interiorNode(recursiveBuild(start, mid, nodeCount, method, ordered_primitive), recursiveBuild(mid, end, nodeCount, method, ordered_primitive), axis, b);
            }
        }
    }
    return node;
}

int BVHAccel::partition(int start, int end, float pivot, int axis)
{
    int head = start;
    int rear = end - 1;

    while (head < rear)
    {
        while (pInfo[head].center[axis] <= pivot && head < rear)
            head++;
        while (pInfo[rear].center[axis] > pivot && rear > head)
            rear--;

        if (head < rear)
        {
            std::swap(pInfo[head], pInfo[rear]);
        }
    }

    return head;
}

BVHAccel::~BVHAccel()
{
}

void BVHAccel::radixSort(std::vector<primitiveMorton> &v)
{
    std::vector<primitiveMorton> tmp = v;

    for (int i = 1; i < sortTime; i++)
    {
        int mortonBucket[(1 << sortBit)] = {0};
        int outIndex[(1 << sortBit)] = {0};

        int lowBit = i * sortBit;
        int mask = (1 << sortBit) - 1;
        std::vector<primitiveMorton> in = (i & 1) ? v : tmp;
        std::vector<primitiveMorton> out = in;

        for (int i = 0; i < in.size(); i++)
        {
            mortonBucket[(in[i].mortonCode >> lowBit) & mask]++;
        }
        outIndex[0] = 0;
        for (int i = 1; i < (1 << sortBit); i++)
        {
            outIndex[i] = outIndex[i - 1] + mortonBucket[i - 1];
        }
        for (int i = 0; i < in.size(); i++)
        {
            out[outIndex[(in[i].mortonCode >> lowBit) & mask]] = in[i];
            outIndex[(in[i].mortonCode >> lowBit) & mask]++;
        }
        (i & 1) ? tmp = out : v = out;
    }
}

BVHNode *BVHAccel::emitNode(int &nodeCount, int maskBit, std::vector<primitiveMorton> &MortonInfo, std::vector<std::shared_ptr<Primitive>> &ordered_primitive, const int &firstMortonOffset, const int &nPrimitive)
{
    if (maskBit == -1 || nPrimitive <= maxPrimInNode)
    {
        BVHNode *node = new BVHNode();
        Bound3D bound;

        for (int i = 0; i < nPrimitive; i++)
        {
            bound = Union(primitive[MortonInfo[i + firstMortonOffset].primIndex]->worldBound(), bound);
        }

        node->leafNode(nPrimitive, firstMortonOffset, bound);

        for (int i = 0; i < nPrimitive; i++)
        {
            ordered_primitive.push_back(primitive[MortonInfo[i + firstMortonOffset].primIndex]);
        }
        nodeCount++;
        return node;
    }
    else
    {
        uint32_t mask = (1 >> maskBit);
        if ((MortonInfo[firstMortonOffset].mortonCode & mask) == (MortonInfo[firstMortonOffset + nPrimitive - 1].mortonCode & mask))
        {
            return emitNode(nodeCount, maskBit - 1, MortonInfo, ordered_primitive, firstMortonOffset, nPrimitive);
        }
        else
        {
            int splitIndex;
            int searchStart = firstMortonOffset;
            int searchEnd = firstMortonOffset + nPrimitive - 1;
            while (searchStart + 1 != searchEnd)
            {
                int mid = (searchStart + searchEnd) / 2;
                if ((MortonInfo[mid].mortonCode & mask) != (MortonInfo[searchEnd].mortonCode & mask))
                {
                    searchStart = mid;
                }
                else
                {
                    searchEnd = mid;
                }
            }
            splitIndex = searchStart;

            BVHNode *node = new BVHNode();
            node->interiorNode(emitNode(nodeCount, maskBit - 1, MortonInfo, ordered_primitive, firstMortonOffset, splitIndex - firstMortonOffset + 1), emitNode(nodeCount, maskBit - 1, MortonInfo, ordered_primitive, splitIndex + 1, nPrimitive - splitIndex + firstMortonOffset - 1), maskBit % 3);
            nodeCount++;
            return node;
        }
    }
}

BVHNode *BVHAccel::SAHupperNode(int &nodeCount, int start, int end, std::vector<primitiveInfo> &nodeInfo, std::vector<BVHNode *> treeLet)
{
    if (end - start == 1)
    {
        return treeLet[nodeInfo[start].primIndex];
    }
    Bound3D bound;
    for (int i = start; i < end; i++)
    {
        bound = Union(nodeInfo[i].bound, bound);
    }
    Bound3D centerBound;
    for (int i = start; i < end; i++)
    {
        centerBound = Union(nodeInfo[i].center, centerBound);
    }
    int axis = centerBound.maxExtent();
    for (int i = start; i < end; i++)
    {
        int b = nBuckets * centerBound.offset(nodeInfo[i].center)[axis];
        if (b == nBuckets)
            b--;
        bucket[b].count++;
        bucket[b].bound = Union(nodeInfo[i].bound, bucket[b].bound);
    }
    int cost[nBuckets];
    for (int i = 0; i < nBuckets - 1; i++)
    {
        Bound3D b0, b1;
        int cnt0, cnt1;
        for (int j = 0; j <= i; j++)
        {
            cnt0++;
            b0 = Union(b0, bucket[j].bound);
        }
        for (int j = i + 1; j < nBuckets; j++)
        {
            cnt1++;
            b1 = Union(b1, bucket[j].bound);
        }
        cost[i] = 0.125 + (b0.surfaceArea() * cnt0 + b1.surfaceArea() * cnt1) / bound.surfaceArea();
    }
    int splitIndex;
    float minCost = cost[0];
    for (int i = 0; i < nBuckets; i++)
    {
        if (cost[i] < minCost)
        {
            minCost = cost[i];
            splitIndex = i;
        }
    }

    int split;
    int leafCost = nodeInfo.size();
    BVHNode *node = new BVHNode();

    primitiveInfo *pmid = std::partition(&nodeInfo[start], &nodeInfo[end - 1] + 1, [&](const primitiveInfo &p)
                                         {
                                             int b = nBuckets * centerBound.offset(p.center)[axis];
                                             if (b == nBuckets)
                                                 b--;
                                             return b < splitIndex;
                                         });
    split = pmid - &nodeInfo[0];

    node->interiorNode(SAHupperNode(nodeCount, start, split, nodeInfo, treeLet), SAHupperNode(nodeCount, split, end, nodeInfo, treeLet), axis, bound);
    nodeCount++;
    return node;
}

BVHNode *BVHAccel::HLBVHBuild(int &nodeCount, std::vector<std::shared_ptr<Primitive>> &ordered_primitive)
{
    //find max bounding
    Bound3D centerBound;
    for (int i = 0; i < primitive.size(); i++)
    {
        centerBound = Union(centerBound, pInfo[i].center);
    }
    //init mortonInfo
    for (int i = 0; i < primitive.size(); i++)
    {
        MortonInfo.push_back(primitiveMorton(i, encodeMorton(mortonScale * centerBound.offset(pInfo[i].center))));
    }
    //radix sort
    radixSort(MortonInfo);

    //gen treelet
    std::vector<HLBVHtreeLet> treeLetToBuild;

    int s = 0;
    int e = 1;
    uint32_t mask = 0b00111111111111000000000000000000;

    while (e <= MortonInfo.size())
    {
        if (e == MortonInfo.size() || ((MortonInfo[s].mortonCode & mask) != (MortonInfo[e].mortonCode & mask)))
        {
            int nPrimitive = e - s;
            treeLetToBuild.push_back(HLBVHtreeLet(nPrimitive, s));
            s = e;
            e++;
        }
        else
            e++;
    }

    std::vector<BVHNode *> finishedBuild;
    for (int i = 0; i < treeLetToBuild.size(); i++)
    {
        int originMaskBit = 29 - 12;
        BVHNode *node = emitNode(nodeCount, originMaskBit, MortonInfo, ordered_primitive, treeLetToBuild[i].firstMOffset, treeLetToBuild[i].nPrimitve);
        finishedBuild.push_back(node);
    }

    //SAH build upper tree -> root node
    std::vector<primitiveInfo> nodeInfo;
    for (int i = 0; i < finishedBuild.size(); i++)
    {
        nodeInfo.push_back(primitiveInfo(finishedBuild[i]->bound, i));
    }

    return SAHupperNode(nodeCount, 0, finishedBuild.size(), nodeInfo, finishedBuild);
}
int BVHAccel::flattenBVHTree(BVHNode *node, int &currentIndex)
{
    linearBVH[currentIndex].bound = node->bound;
    linearBVH[currentIndex].nPrimitve = node->nPrimitive;

    int nodeIndex = currentIndex;
    ++currentIndex;
    if (node->nPrimitive == 0)
    {

        linearBVH[nodeIndex].splitAxis = node->splitAxis;
        flattenBVHTree(node->lchild, currentIndex);
        int childIndex = flattenBVHTree(node->rchild, currentIndex);
        linearBVH[nodeIndex].secondChildOffset = childIndex;
    }
    else
    {
        linearBVH[nodeIndex].primitivesOffset = node->firstPOffset;
    }

    return nodeIndex;
}

bool BVHAccel::Intersect(const Ray &ray, SurfaceInteraction &interaction)
{
    bool intersected = false;
    int currentNode = 0;

    int nodeStack[64];
    int top = 0;

    nodeStack[top++] = 0;

    while (top != 0)
    {
        LinearBVHNode *node = &linearBVH[nodeStack[top - 1]];
        top--;

        if (node->bound.IntersectP(ray))
        {
            // std::cout << nodeStack[top];
            if (node->nPrimitve == 0)
            {
                nodeStack[top++] = node->secondChildOffset;
                nodeStack[top++] = (++currentNode);
            }
            else
            {
                currentNode = nodeStack[top - 1];
                // std::cout << node->nPrimitve << " " << node->primitivesOffset << " ";
                for (int i = 0; i < node->nPrimitve; i++)
                {

                    if (primitive[node->primitivesOffset + i]->Intersect(ray, interaction))
                    {
                        intersected = true;
                    }
                }
            }
        }
        else
        {
            currentNode = nodeStack[top - 1];
        }
    }

    return intersected;
}

bool BVHAccel::IntersectP(Ray &ray)
{
    bool intersected = false;
    int currentNode = 0;

    int nodeStack[64];
    int top = 0;

    nodeStack[top++] = 0;

    while (top != 0)
    {
        LinearBVHNode *node = &linearBVH[nodeStack[top - 1]];
        top--;

        if (node->bound.IntersectP(ray))
        {
            // std::cout << nodeStack[top];
            if (node->nPrimitve == 0)
            {
                nodeStack[top++] = node->secondChildOffset;
                nodeStack[top++] = (++currentNode);
            }
            else
            {
                currentNode = nodeStack[top - 1];
                // std::cout << node->nPrimitve << " " << node->primitivesOffset << " ";
                for (int i = 0; i < node->nPrimitve; i++)
                {

                    if (primitive[node->primitivesOffset + i]->IntersectP(ray))
                    {
                        intersected = true;
                    }
                }
            }
        }
        else
        {
            currentNode = nodeStack[top - 1];
        }
    }

    return intersected;
}