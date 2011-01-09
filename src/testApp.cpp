#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

/*
//////////////////////////////////////////////
//	SETUP.
//////////////////////////////////////////////

void testApp :: setup() {
    ofSetVerticalSync( true );
    ofSetFrameRate( 60 );
    ofBackground( 0, 0, 0 );
//    screenWidth = 1024;
    screenWidth = 800;
//    screenHeight = 764;
    screenHeight = 600;
    cameraWidth		= 640;
    cameraHeight	= 480;

    initCamera();
    initImages();
    initMotion();
    initImageMask();
    initBlobTrack();
    CvSize size = cvSize(cameraWidth,cameraHeight);
    saveScreen.allocate(cameraWidth, cameraHeight, OF_IMAGE_COLOR);
    colorImg.allocate(cameraWidth,cameraHeight);
    doVideoWrite = false;
    writer = cvCreateVideoWriter(
                 "test.avi",
                 CV_FOURCC('M','J','P','G'),
                 15,
                 size);

    geoLayer = new GeometricLayer(screenWidth, screenHeight);
    orgLayer = new OrganicLayer(screenWidth, screenHeight);
    geoLayer->setup();
    orgLayer->setup();
}

void testApp :: initCamera() {

    camera.setVerbose( true );
    camera.initGrabber( cameraWidth, cameraHeight );
}

void testApp :: initMotion() {
    cameraColorImage.allocate( cameraWidth, cameraHeight );
    cameraGrayImage.allocate( cameraWidth, cameraHeight );
    cameraGrayPrevImage.allocate( cameraWidth, cameraHeight );
    cameraGrayDiffImage.allocate( cameraWidth, cameraHeight );
    cameraDiffFloatImage.allocate( cameraWidth, cameraHeight );
    cameraMotionFloatImage.allocate( cameraWidth, cameraHeight );

    cameraMotionFadeAmount = 0.95f;
    //cameraMotionFadeAmount = 0.80f;
}

void testApp :: initImageMask() {

    resizeImg.allocate( screenWidth, screenHeight );
    maskTexture.allocate( screenWidth, screenHeight, GL_RGBA );

    maskPixles = new unsigned char[ screenWidth * screenHeight * 4 ];
}

void testApp :: initImages() {
    oldTerra.loadImage("images/oldTerra.cc.jpg");
    newTerra.loadImage("images/newTerra.cc.jpg");
    newImgPixles = new unsigned char[ screenWidth * screenHeight * 4 ];
    newImgPixles		= newTerra.getPixels();
}

void testApp :: initBlobTrack() {
    bLearnBakground = true;
    threshold = 80;
}
//////////////////////////////////////////////
//	UPDATE.
//////////////////////////////////////////////

void testApp :: update() {
    updateCamera();

    if ( cameraNewFrame ) {
        updateMotion( camera.getPixels() );
        updateImageMask();
    }

    geoLayer->update();
    orgLayer->update();
}

void testApp :: updateCamera() {
    camera.grabFrame();
    cameraNewFrame = camera.isFrameNew();
}

void testApp :: updateMotion( unsigned char *pixels ) {
    cameraColorImage.setFromPixels( pixels, cameraWidth, cameraHeight );

    cameraGrayPrevImage	= cameraGrayImage;
    cameraGrayImage		= cameraColorImage;

    cameraGrayDiffImage.absDiff( cameraGrayImage, cameraGrayPrevImage );
    cameraGrayDiffImage.threshold( 30 );

    cameraDiffFloatImage	= cameraGrayDiffImage;
    cameraMotionFloatImage	*= cameraMotionFadeAmount;
    cameraMotionFloatImage	+= cameraDiffFloatImage;
    cameraMotionFloatImage.blur( 20 );

    // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
    // also, find holes is set to true so we will get interior contours as well....
    contourFinder.findContours(cameraGrayDiffImage, 20, (cameraWidth*cameraHeight)/3, 10, true);	// find holes
}

void testApp :: updateImageMask() {
    resizeImg.scaleIntoMe(cameraMotionFloatImage);
    motionPixles	= resizeImg.getPixels();

    for ( int i=0; i<screenWidth; i++ ) {
        for ( int j=0; j<screenHeight; j++ ) {
            int p = j * screenWidth + i;
            maskPixles[ p * 4 + 0 ] = newImgPixles[ p * 3 + 0 ];
            maskPixles[ p * 4 + 1 ] = newImgPixles[ p * 3 + 1 ];
            maskPixles[ p * 4 + 2 ] = newImgPixles[ p * 3 + 2 ];
            maskPixles[ p * 4 + 3 ] = motionPixles[ p ];
        }
    }

    maskTexture.loadData( maskPixles, screenWidth, screenHeight, GL_RGBA );
}

//////////////////////////////////////////////
//	DRAW.
//////////////////////////////////////////////

void testApp :: draw() {
    glDisable(GL_BLEND);

    ofSetupScreen();

    ofSetColor(0xFFFFFF);
    oldTerra.draw(0,0);
    // newTerra.draw(0,0);
    //drawCamera();
  //  orgLayer->draw();
    drawImageMask();
    geoLayer->seedFromBlob(&contourFinder, cameraWidth, cameraHeight);
    geoLayer->draw();
    drawMotion();

    contourFinder.draw(0,0,screenWidth, screenHeight);

    ofSetColor( 0xFF0000 );
    ofDrawBitmapString
    (
        "fps :: " + ofToString(ofGetFrameRate(), 2) + "\n\n",
        20,
        20
    );
    if (doVideoWrite) {
        IplImage * tempImg = cvCreateImage(
                                 cvSize(cameraWidth,cameraHeight),
                                 IPL_DEPTH_8U,
                                 3);
        saveScreen.grabScreen(screenWidth-cameraWidth,screenHeight-cameraHeight,cameraWidth,cameraHeight);
        colorImg.setFromPixels(saveScreen.getPixels(), cameraWidth,cameraHeight);
        cvCvtColor(colorImg.getCvImage(), tempImg, CV_RGB2BGR);
        cvWriteFrame(writer,tempImg);
    }
}

void testApp :: drawCamera() {
    ofSetColor( 0xFFFFFF );
    camera.draw( 0, 0, cameraWidth, cameraHeight );
}


void testApp :: drawMotion() {
    ofSetColor( 0xFFFFFF );
   // cameraMotionFloatImage.draw( 960, 480, 320, 240 );
    cameraMotionFloatImage.draw( 800, 0, 320, 240 );
}

void testApp :: drawMotionDebug() {
    //
}

void testApp :: drawImageMask() {
    ofEnableAlphaBlending();
    maskTexture.draw( 0, 0 );
    ofDisableAlphaBlending();
}

//////////////////////////////////////////////
//	HANDLERS.
//////////////////////////////////////////////

void testApp :: keyPressed( int key ) {

}

void testApp :: keyReleased( int key ) {

}

void testApp :: mouseMoved( int x, int y ) {

}

void testApp :: mouseDragged( int x, int y, int button ) {

}

void testApp :: mousePressed( int x, int y, int button ) {

}

void testApp :: mouseReleased( int x, int y, int button ) {
    doVideoWrite = !doVideoWrite;
}

void testApp :: windowResized( int w, int h ) {

}

void testApp::exit() {

    geoLayer->exit();
    orgLayer->exit();
    cvReleaseVideoWriter(&writer);
}
*/

