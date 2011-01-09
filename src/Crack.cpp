#include "Crack.h"
#include "ofMath.h"

Crack::Crack(cgrid_t *_pcgrid,CvArr * _pCvImage) {
    //ctor
    m_cgrid = _pcgrid;
    m_pCvImage = _pCvImage;
    m_width = 1;
    m_crackColor.r = 255;
    m_crackColor.g = 255;
    m_crackColor.b = 255;
    stillCracking = false;
    // find placement along existing crack
    findStart();
}
Crack::~Crack() {
    //dtor
}
void Crack::setGrid(cgrid_t *_pcgrid) {
    m_cgrid = _pcgrid;
}
void Crack::setImagePtr(CvArr * _pCvImage) {
    m_pCvImage = _pCvImage;
}

void Crack::findStart() {
    // pick random point
    int px=0;
    int py=0;

    // shift until crack is found
    bool found=false;
    int timeout = 0;
    while ((!found) || (timeout++>1000)) {
        px = int(ofRandom(0, CRACK_AREA_WIDTH));
        py = int(ofRandom(0, CRACK_AREA_HEIGHT));
        if ((*m_cgrid)[px][py]<10000) {
            found=true;
        }
    }

    if (found) {
        // start crack
        int a = int((*m_cgrid)[px][py]);
        if (ofRandom(0,100)<50) {
            a-=90+int(ofRandom(-2,2.1));
        } else {
            a+=90+int(ofRandom(-2,2.1));
        }
        startCrack(px,py,a);
    } else {
        //ofLog("timeout: "+timeout);
    }
}


void Crack::startCrack(int _x, int _y, int _t) {
    m_x=_x;
    m_y=_y;
    m_t=_t;//%360;
    m_x+=0.61*cos(m_t*PI/180);
    m_y+=0.61*sin(m_t*PI/180);
    stillCracking = true;
}

void Crack::update() {
    // continue cracking
    //m_x+=0.42*cos(m_t*PI/180);
    m_x+=cos(m_t*PI/180);
    //m_y+=0.42*sin(m_t*PI/180);
    m_y+=sin(m_t*PI/180);

    // bound check
    float z = 0.33;
    int cx = int(m_x+z*ofRandomf());  // add fuzz
    int cy = int(m_y+z*ofRandomf());

    // draw crack
    cvCircle( m_pCvImage,
              cvPoint(cx,cy),
              m_width,
              CV_RGB( m_crackColor.r,m_crackColor.g,m_crackColor.b),
              m_width);

    if ((cx>=0) && (cx<CRACK_AREA_WIDTH) && (cy>=0) && (cy<CRACK_AREA_HEIGHT)) {
        // safe to check
        if (((*m_cgrid)[cx][cy]>10000) || (abs((*m_cgrid)[cx][cy]-m_t)<5)) {
            // continue cracking
            (*m_cgrid)[cx][cy]=int(m_t);
            stillCracking = true;
        } else if (abs((*m_cgrid)[cx][cy]-m_t)>2) {
            // crack encountered (not self), stop cracking and start again somewhere else
            findStart();
            stillCracking = false;
        }
    } else {
        // out of bounds, stop cracking and start again somewhere else
        findStart();
        stillCracking = false;
    }
}
