#ifndef CRACK_H
#define CRACK_H

#include "cv.h"
#include "ofTypes.h"
#include "ofGraphics.h"
#include "crackTypes.h"

// @todo (maia#1#): add crack lifeclass Crack {
public:
    Crack(cgrid_t *_pcgrid,CvArr * _pCvImage);
    virtual ~Crack();
    void setGrid(cgrid_t *_pcgrid);
    bool stillCracking;
    void setImagePtr(CvArr * _pCvImage);
    void update();
protected:
private:
    CvArr* m_pCvImage;
    void findStart();
    void startCrack(int _x, int _y, int _t);
    float m_x;
    float m_y;
    float m_t; // direction of travel in degrees
    float m_width; //width of the crack
    ofColor m_crackColor;
    cgrid_t *m_cgrid;
};

#endif // CRACK_H
