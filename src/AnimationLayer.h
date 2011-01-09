#ifndef ANIMATIONLAYER_H
#define ANIMATIONLAYER_H

#include "ofxOpenCv.h"

#include "cv.h"
//#include "highgui.h"

//test tagging

class AnimationLayer {
public:
    AnimationLayer(int _width,int _height);
    AnimationLayer();
    virtual ~AnimationLayer();
    void setup();
    void update();
    void draw();
    void exit();
protected:
    ofxCvColorImage			layerImage;
    int m_width;
    int m_height;
    float m_alpha;
    ofTexture maskTexture;
    unsigned char *maskPixles;
    unsigned char *imgPixles;
private:
};

#endif // ANIMATIONLAYER_H
