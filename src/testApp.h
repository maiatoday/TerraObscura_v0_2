#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

};

#endif
/*
#include "ofMain.h"
#include "ofxOpenCv.h"

#include "cv.h"
#include "highgui.h"

#include "OrganicLayer.h"
#include "GeometricLayer.h"

class testApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void exit();

    void initCamera();
    void initMotion();
    void initImageMask();
    void initImages();
    void initBlobTrack();

    void updateCamera();
    void updateMotion( unsigned char *pixels );
    void updateImageMask();

    void drawCamera();
    void drawMotion();
    void drawMotionDebug();
    void drawImageMask();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);

    int screenWidth;
    int screenHeight;

    ofVideoGrabber camera;
    int cameraWidth;
    int cameraHeight;
    bool cameraNewFrame;

    ofImage oldTerra;
    ofImage newTerra;
    ofxCvFloatImage resizeImg;

    ofxCvColorImage			cameraColorImage;
    ofxCvGrayscaleImage		cameraGrayImage;
    ofxCvGrayscaleImage		cameraGrayPrevImage;
    ofxCvGrayscaleImage		cameraGrayDiffImage;
    ofxCvFloatImage			cameraDiffFloatImage;
    ofxCvFloatImage			cameraMotionFloatImage;
    float cameraMotionFadeAmount;

    ofxCvContourFinder 	contourFinder;
    int 				threshold;
    bool				bLearnBakground;

    ofTexture maskTexture;
    unsigned char *maskPixles;
    unsigned char *videoPixels;
    unsigned char *motionPixles;
    unsigned char *newImgPixles;

    bool doVideoWrite;
    ofImage saveScreen;
    ofxCvColorImage colorImg;
    CvVideoWriter * writer;

    OrganicLayer * orgLayer;
    GeometricLayer * geoLayer;
};
*/
