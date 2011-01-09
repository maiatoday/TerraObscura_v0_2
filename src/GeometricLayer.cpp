#include "GeometricLayer.h"

GeometricLayer::GeometricLayer(int _width,int _height):AnimationLayer( _width, _height) {
    //ctor
    m_alpha = 0.85;
    restartCracks();
    for (int ii = 0; ii < MAX_DESTROYER_COUNT; ii++) {
        destroyers[ii] = new Destroyer(layerImage.getCvImage());
        destroyers[ii]->start();
    }
}


GeometricLayer::~GeometricLayer() {
    //dtor
}

void GeometricLayer::update() {
// @todo (maia#1#): figure out when to restart crack image
    for (int ii = 0; ii<num; ii++) {
        cracks[ii]->update();
        if (!cracks[ii]->stillCracking) {
            makeCrack();
        }
    }

    for (int ii = 0; ii < MAX_DESTROYER_COUNT; ii++) {
        destroyers[ii]->step();
        float tmpxx,tmpyy;
        destroyers[ii]->getPosition(tmpxx,tmpyy);
        //blotGrid(tmpxx,tmpyy);

    }
    layerImage.flagImageChanged();
}
//cracked world methods
void GeometricLayer::makeCrack() {
    if (num<MAX_CRACKS) {
        // make a new crack instance
        cracks[num] = new Crack(&cgrid,layerImage.getCvImage());
        num++;
    }
}

void GeometricLayer::restartCracks() {

    // erase crack grid
    for (int y=0; y<CRACK_AREA_HEIGHT; y++) {
        for (int x=0; x<CRACK_AREA_WIDTH; x++) {
            cgrid[x][y] = 10001;
        }
    }

    // make 16 random crack seeds
    for (int k=0; k<16; k++) {
        int i = int(ofRandom(0,CRACK_AREA_WIDTH-1));
        int j = int(ofRandom(0,CRACK_AREA_HEIGHT-1));
        cgrid[i][j]=ofRandom(0,360);
    }
// make just five cracks
    num = 0;
    for (int k=0; k<7; k++) {
        makeCrack();
    }
}

void GeometricLayer::seedFromBlob(ofxCvContourFinder *_blobContours, int _width, int _height) {
    m_pblobContours = _blobContours;
    ofColor tmpColor;
    tmpColor.r = 128;
    tmpColor.g = 0;
    tmpColor.b = 128;
//    tmpColor.r = 0;
//    tmpColor.g = 0;
//    tmpColor.b = 0;

    for (unsigned int ii=0; (ii<m_pblobContours->blobs.size())&&(ii < MAX_DESTROYER_COUNT); ii++) {
        int tmpx = (m_pblobContours->blobs[ii].centroid.x/_width)*WALKER_AREA_WIDTH;
        int tmpy= (m_pblobContours->blobs[ii].centroid.y/_height)*WALKER_AREA_HEIGHT;
        //convert camera dimensions to destroyer dimensions
        destroyers[ii]->start(tmpx,tmpy);
        destroyers[ii]->setPathColour(tmpColor);
        destroyers[ii]->step(tmpx,tmpy);
    }
}


void GeometricLayer::blotGrid(unsigned int _xx, unsigned int _yy, int _dia)
{
    if (_dia > 30) _dia = 30;
    if (_dia < 2) _dia = 2;
    for (int y=-_dia/2; y<_dia/2; y++) {
        for (int x=-_dia/2; x<_dia/2; x++) {
            cgrid[_xx + x][_yy + y] = 10001;
        }
    }

}
