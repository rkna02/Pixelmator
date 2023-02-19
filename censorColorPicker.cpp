/*
*  File: censorColorPicker.cpp
*  Implements the censor color picker for CPSC 221 PA2.
*
*/

#include "censorColorPicker.h"

#include <math.h> // gives access to sqrt function

/*
*  Useful function for computing the Euclidean distance between two PixelPoints
*/
double PointDistance(PixelPoint a, PixelPoint b) {
  unsigned int diff_x, diff_y;
  if (a.x > b.x)
    diff_x = a.x - b.x;
  else
    diff_x = b.x - a.x;
  if (a.y > b.y)
    diff_y = a.y - b.y;
  else
    diff_y = b.y - a.y;
  return sqrt(diff_x * diff_x + diff_y * diff_y);
}

CensorColorPicker::CensorColorPicker(unsigned int b_width, PixelPoint ctr, unsigned int rad, PNG& inputimage)
{
  // complete your implementation below
  blockwidth = b_width;
  center = ctr;
  radius = rad;
  img = inputimage;
  blockyimg = img;

  // outer for loop: for each mozaic block
  for (unsigned int x_outer = 0; x_outer < blockyimg.width(); x_outer = x_outer + blockwidth) {
    for (unsigned int y_outer = 0; y_outer < blockyimg.height(); y_outer = y_outer + blockwidth) {
      // inner for loop: for each individual pixel
      HSLAPixel *pixel;
      PixelPoint point_outer(x_outer, y_outer, *(blockyimg.getPixel(x_outer, y_outer)));


      // compute the average values of the mozaic block if it does not exceed the radius 
      // +15 to take account if center is on the right half of image
      if (PointDistance(point_outer, center) <= radius + 2*blockwidth) {
        double h_avg = 0;
        double s_avg = 0;
        double l_avg = 0;
        double a_avg = 0;

        for (unsigned int x_inner = 0; x_inner < blockwidth; x_inner++) {
          for (unsigned int y_inner = 0; y_inner < blockwidth; y_inner++) {
            h_avg = h_avg + (img.getPixel(x_outer + x_inner, y_outer + y_inner))->h;
            s_avg = s_avg + (img.getPixel(x_outer + x_inner, y_outer + y_inner))->s;
            l_avg = l_avg + (img.getPixel(x_outer + x_inner, y_outer + y_inner))->l;
            a_avg = a_avg + (img.getPixel(x_outer + x_inner, y_outer + y_inner))->a;
          }
        }

        // finalize average values
        h_avg = h_avg / (blockwidth * blockwidth);
        s_avg = s_avg / (blockwidth * blockwidth);
        l_avg = l_avg / (blockwidth * blockwidth);
        a_avg = a_avg / (blockwidth * blockwidth);

        // start assigning pixels to blockimg
        for (unsigned int x_inner = 0; x_inner < blockwidth; x_inner++) {
          for (unsigned int y_inner = 0; y_inner < blockwidth; y_inner++) {
            // only change if in range
            PixelPoint point_inner(x_outer + x_inner, y_outer + y_inner, *(blockyimg.getPixel(x_outer, y_outer)));
            if (PointDistance(point_inner, center) <= radius) {
              pixel = blockyimg.getPixel(x_outer + x_inner, y_outer + y_inner);
              pixel->h = h_avg;
              pixel->s = s_avg;
              pixel->l = l_avg;
              pixel->a = a_avg;
            }
          }
        }
      }

    }
  }

}

HSLAPixel CensorColorPicker::operator()(PixelPoint p)
{
  // complete your implementation below
  return *(blockyimg.getPixel(p.x, p.y));
}
