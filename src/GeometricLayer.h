#ifndef GEOMETRICLAYER_H
#define GEOMETRICLAYER_H

#include "AnimationLayer.h"
#include "crackTypes.h"
#include "Crack.h"
#include "Destroyer.h"

#define MAX_DESTROYER_COUNT (100)

class GeometricLayer : public AnimationLayer {
public:
    GeometricLayer(int _width,int _height);
    virtual ~GeometricLayer();
    void update();
    void restartCracks();
    void seedFromBlob( ofxCvContourFinder *_blobContours,int _width, int _height);
protected:
private:
    int num;
    void makeCrack();
// grid of cracks
    cgrid_t cgrid;
    void blotGrid(unsigned int _xx, unsigned int _yy, int _dia = 5);
    Crack * cracks[MAX_CRACKS];
    Destroyer * destroyers[MAX_DESTROYER_COUNT];
    ofxCvContourFinder *m_pblobContours;
};

#endif // GEOMETRICLAYER_H
