#include "OrganicLayer.h"

OrganicLayer::OrganicLayer(int _width,int _height):AnimationLayer( _width, _height)
{
//    //ctor
}

OrganicLayer::~OrganicLayer()
{
    //dtor
}
void OrganicLayer::update()
{
  CvPoint p1;
  p1.x = 50;
  p1.y = 50;
  CvScalar color = CV_RGB( 255,255,255 );
  cvCircle( layerImage.getCvImage(), p1, 20,color);


}
