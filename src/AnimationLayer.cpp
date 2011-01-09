#include "AnimationLayer.h"

AnimationLayer::AnimationLayer() {
    //ctor
}
AnimationLayer::AnimationLayer(int _width, int _height) {
    //ctor
    m_width = _width;
    m_height = _height;
    m_alpha = 1;
    layerImage.allocate( m_width, m_height);
    maskTexture.allocate( m_width, m_height, GL_RGBA );
    maskPixles = new unsigned char[ m_width * m_height * 4 ];
}

AnimationLayer::~AnimationLayer() {
    //dtor
}

void AnimationLayer::setup() {


}

void AnimationLayer::update() {

}
void AnimationLayer::draw() {
    imgPixles		= layerImage.getPixels();
    for ( int i=0; i<m_width; i++ ) {
        for ( int j=0; j<m_height; j++ ) {
            int p = j * m_width + i;
            //y=0.299*R + 0.587*G + 0.114*B opencv BGR
            float tmpGrey = 0.0;
            maskPixles[ p * 4 + 0 ] = imgPixles[ p * 3 + 0 ];
            maskPixles[ p * 4 + 1 ] = imgPixles[ p * 3 + 1 ];
            maskPixles[ p * 4 + 2 ] = imgPixles[ p * 3 + 2 ];

            tmpGrey += 0.114*imgPixles[ p * 3 + 0 ];
            tmpGrey += 0.587*imgPixles[ p * 3 + 1 ];
            tmpGrey += 0.299*imgPixles[ p * 3 + 2 ];
            tmpGrey *= m_alpha;
            maskPixles[ p * 4 + 3 ] = tmpGrey;
        }
    }

    maskTexture.loadData( maskPixles, m_width, m_height, GL_RGBA );
    ofEnableAlphaBlending();
    maskTexture.draw(0,0);
    ofDisableAlphaBlending();

}
void AnimationLayer::exit() {

}
