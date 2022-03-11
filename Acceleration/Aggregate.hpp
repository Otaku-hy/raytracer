#ifndef Aggregate_H
#define Aggregate_H

class Aggregate
{
private:
    /* data */
public:
    Aggregate();
    ~Aggregate();

    bool intersect();
    void getAreaLight();
    void getMaterial();
    void worldBound();
};

#endif