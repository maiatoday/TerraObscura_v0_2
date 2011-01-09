#include "Walker.h"
#include "ofMath.h"

Walker::Walker(CvArr * _pCvImage) {
    //ctor
    m_pCvImage = _pCvImage;
    m_startSpray = 20;
    float xx = ofRandom(0, WALKER_AREA_WIDTH-1);
    float yy = ofRandom(0, WALKER_AREA_HEIGHT-1);
    m_x = ofRandom(xx-m_startSpray, xx+m_startSpray);
    m_y = ofRandom(yy-m_startSpray, yy+m_startSpray);
// @todo (maia#1#): constrain m_x and m_y
    m_rad = ofRandom(0.1,1);
    m_dia = ofRandom(0,5);
    useImageColour = true;
    m_particleLife = MAX_PARTICLE_LIFE;

}

Walker::~Walker() {
    //dtor
}

void Walker::start() {
    start(m_x,m_y);
}

void Walker::start(float _x, float _y) {
//	//println("particleLife before"+particleLife);
    m_particleLife = MAX_PARTICLE_LIFE;
    //println("particleLife "+particleLife);
    m_x = ofRandom(_x-m_startSpray, _x+m_startSpray);
    m_y = ofRandom(_y-m_startSpray, _y+m_startSpray);
    m_rad = ofRandom(0.1,1);
    m_dia = ofRandom(0,5);
    if (useImageColour) {
        m_pathColour = someColor();
    }
}

void Walker::step() {
//    m_x += ofRandom(-m_dia,m_dia);
//    m_y += ofRandom(-m_dia,m_dia);
    step(m_x,m_y);
}

void Walker::step(float _x,float _y) {
    m_particleLife--;
    if (m_particleLife > (MIN_PARTICLE_LIFE*0.25)) {
        m_fac += ofRandom(0, 10) * 0.015;
        m_wobble = 0.2 * m_rad * cos(m_fac);

        m_x += ofRandom(-m_dia,m_dia);
//        m_x = _x;

        m_y += ofRandom(-m_dia,m_dia);
//        m_x = _y;

//    if((m_y<(0 - m_rad*2)) || (m_y>(WALKER_AREA_HEIGHT+m_rad*2)) ||
//      (m_x<(0 - m_rad*2)) || (m_x>(WALKER_AREA_WIDTH+m_rad*2)))
//      init();
//        float tempAlpha = particleLife;
//        tempAlpha/=MAX_PARTICLE_LIFE;
//        tempAlpha *= 255;
        cvCircle( m_pCvImage,
                  cvPoint(m_x,m_y),
                  m_rad,
                  CV_RGB( m_pathColour.r,m_pathColour.g,m_pathColour.b),
                  CV_FILLED);
    } else if (m_particleLife == 0) {
        start();
    }
}


void Walker::getPosition(float &_xx, float &_yy)
{
    _xx = m_x;
    _yy = m_y;
}

ofColor Walker::someColor() {
    ofColor retColor;
    retColor.r = 255;
    retColor.g = 0;
    retColor.b = 0;
    return retColor;
}


void Walker::setPathColour(ofColor _color) {
    m_pathColour = _color;
}
