#ifndef __EUCLIDIAN_H__
#define __EUCLIDIAN_H__

#include "heuristic.h"

class EuclidianDistance : public Heuristic
{
public:
    EuclidianDistance(Mine mine);

private:
    double distance(const Room* x, const Room* y) const;
    void measure(Mine mine);
};

#endif