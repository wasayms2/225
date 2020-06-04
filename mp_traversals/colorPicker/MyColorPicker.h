#pragma once

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  HSLAPixel getColor(unsigned x, unsigned y);
  MyColorPicker(unsigned gap);

private:
  unsigned spacing;
  //three different pixels to color image with
  HSLAPixel c1;
  HSLAPixel c2;
  HSLAPixel c3;
};
