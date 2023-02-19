/*
*  File: imageTileColorPicker.cpp
*  Implements the image tile color picker for CPSC 221 PA2.
*
*/

#include "imageTileColorPicker.h"

ImageTileColorPicker::ImageTileColorPicker(PNG& otherimage) {
  // complete your implementation below
  img_other = otherimage;
}

HSLAPixel ImageTileColorPicker::operator()(PixelPoint p) {
  // complete your implementation below
  size_t iterate_x = p.x / img_other.width();  // how many img_others are tiled before the pixel (x)
  size_t iterate_y = p.y / img_other.height(); // how many img_others are tiled before the pixel (y)

  size_t x_coord = p.x - img_other.width() * iterate_x;  // treat it as if it is in one img_other
  size_t y_coord = p.y - img_other.height() * iterate_y;  // treat it as if it is in one img_other

  return *(img_other.getPixel((unsigned int) x_coord, (unsigned int) y_coord));
}