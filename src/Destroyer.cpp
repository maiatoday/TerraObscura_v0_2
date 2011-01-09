#include "Destroyer.h"
#include "ofMath.h"

Destroyer::Destroyer(CvArr * _pCvImage):Walker( _pCvImage)  {
    //ctor
    m_pCvImage = _pCvImage;
    m_startSpray = 20;
    //start(m_x,m_y);
}

Destroyer::~Destroyer() {
    //dtor
}
void Destroyer::start() {
    start(m_x,m_y);
}
void Destroyer::start(float _x,float _y) {
//    m_x = ofRandom(0, WALKER_AREA_WIDTH-1);
//    m_y = ofRandom(0, WALKER_AREA_HEIGHT-1);
    m_x = _x;
    m_y = _y;
    m_rad = ofRandom(0.5,10.0);
    m_dia = ofRandom(0,5);
    useImageColour = false;
    m_pathColour.r =85;
    m_pathColour.g =85;
    m_pathColour.b =85;
//    m_pathColour.r =0;
//    m_pathColour.g =0;
//    m_pathColour.b =0;
    m_particleLife = MAX_PARTICLE_LIFE;
}
