#ifndef Aggregate_H
#define Aggregate_H

#include "../Primitive/Primitive.hpp"

class Aggregate : public Primitive
{
private:
    /* data */
public:
    Aggregate() = default;
    ~Aggregate();
};

Aggregate::~Aggregate()
{
}


#endif