/*
* File:        testPriority.cpp
* Description: Basic test cases for CPSC 221 2021W2 PA2 - PriorityNeighbours
*              Add your own code to this!
*
* Date:        2022-02-10 22:32
*
*/

#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"

#include "cs221util/HSLAPixel.h"
#include "cs221util/PNG.h"

#include "pixelpoint.h"
#include "priority.h"

using namespace cs221util;
using namespace std;

TEST_CASE("PriorityNeighbours::insertion_removal_isempty", "[weight=1][part=priority]") {
  //cout << "Testing PriorityNeighbours..." << endl;
  PriorityNeighbours pn(HSLAPixel(180, 0.5, 0.5));
  vector<PixelPoint> result;
  vector<PixelPoint> expected;

  // declare a few PixelPoint objects
  // feel free to add to/change these to test your special conditions!
  PixelPoint pp1(3, 4, HSLAPixel(175, 0.5, 0.5)); // priority #1, short distance from reference point
  PixelPoint pp2(30, 45, HSLAPixel(120, 0.25, 0.75)); // priority #2, longer distance from reference point
  PixelPoint pp3(35, 45, HSLAPixel(120, 0.25, 0.75)); // priority #3, same distance as pp2 and same y-coordinate
  PixelPoint pp4(16, 12, HSLAPixel(30, 0.9, 0.1)); // priority #4, long distance from reference point

  expected.push_back(pp1);
  expected.push_back(pp2);
  expected.push_back(pp3);
  expected.push_back(pp4);

  // put the PixelPoint objects into your PriorityNeighbours collection in some order
  // (feel free to change the insertion order)
  pn.Insert(pp4);
  pn.Insert(pp1);
  pn.Insert(pp3);
  pn.Insert(pp2);

  while (!pn.IsEmpty()) {
    result.push_back(pn.Remove());
  }

  cout << "result[0]:" << endl;
  cout << result[0].x << " ";
  cout << result[0].y << " ";
  cout << result[0].color.h << " ";
  cout << result[0].color.s << " ";
  cout << result[0].color.l << " ";
  cout << result[0].color.a << endl;

  cout << "result[1]" << endl;
  cout << result[1].x << endl;
  cout << result[1].y << endl;
  cout << result[1].color.h << endl;
  cout << result[1].color.s << endl;
  cout << result[1].color.l << endl;
  cout << result[1].color.a << endl;

  cout << "result[2]" << endl;
  cout << result[2].x << endl;
  cout << result[2].y << endl;
  cout << result[2].color.h << endl;
  cout << result[2].color.s << endl;
  cout << result[2].color.l << endl;
  cout << result[2].color.a << endl;

  cout << "result[3]" << endl;
  cout << result[3].x << endl;
  cout << result[3].y << endl;
  cout << result[3].color.h << endl;
  cout << result[3].color.s << endl;
  cout << result[3].color.l << endl;
  cout << result[3].color.a << endl;
  
  //REQUIRE(result == expected);
}