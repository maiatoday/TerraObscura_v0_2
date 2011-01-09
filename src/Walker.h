#ifndef WALKER_H
#define WALKER_H

#include "cv.h"
#include "ofTypes.h"

#define MAX_PARTICLE_LIFE (700)
#define MIN_PARTICLE_LIFE (500)
#define WALKER_AREA_WIDTH (800)
#define WALKER_AREA_HEIGHT (600)

class Walker {
public:
    Walker(CvArr * _pCvImage);
    virtual ~Walker();
    void start();
    void start(float _x,float int_y);
    void step();
    void step(float _x,float int_y);
    void setPathColour(ofColor _color);
    void getPosition(float &_xx, float &_yy);
protected:
    CvArr* m_pCvImage;
    float m_y;
    float m_x;
    float m_rad;
    float m_dia;
    ofColor m_pathColour;
    unsigned int m_particleLife;
    int m_startSpray;
    bool useImageColour;
private:
    float m_wobble;
    float m_fac;
    ofColor someColor();
};

#endif // WALKER_H
