#ifndef DESTROYER_H
#define DESTROYER_H

#include "Walker.h"


class Destroyer : public Walker {
public:
    Destroyer(CvArr * _pCvImage);
    virtual ~Destroyer();
    void start(float _x,float _y);
    void start();
protected:
private:
};

#endif // DESTROYER_H
