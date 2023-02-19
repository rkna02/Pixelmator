/*
*  File: negativeColorPicker.cpp
*  Implements the negative color picker for CPSC 221 PA2.
*
*/

#include "negativeColorPicker.h"

NegativeColorPicker::NegativeColorPicker(PNG& inputimg)
{
  // complete your implementation below
  img = inputimg;
}

HSLAPixel NegativeColorPicker::operator()(PixelPoint p)
{
  // complete your implementation below
  HSLAPixel *pixel = img.getPixel(p.x, p.y);
 
  //compute the luminance
  pixel->l = 1 - pixel->l;
 
  //computer the hue
  pixel->h = pixel->h + 180;
  if (pixel->h >= 360) {
    pixel->h = pixel->h - 360;
  }

  return *pixel;
}
