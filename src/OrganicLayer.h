#ifndef ORGANICLAYER_H
#define ORGANICLAYER_H

#include "AnimationLayer.h"


class OrganicLayer : public AnimationLayer {
public:
    OrganicLayer(int _width,int _height);
    virtual ~OrganicLayer();
    void update();
protected:
private:
};

#endif // ORGANICLAYER_H
