#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm

 */
 MyColorPicker::MyColorPicker(unsigned gap) {
   spacing = gap;

   c1 = HSLAPixel(180, .90, .50);
   c2 = HSLAPixel(180, 1, 0);
   c3 = HSLAPixel(3, .7, .3);
 }
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  //algorithm for changing the pixel colors
  if ((x + y) % 2 == 0) {
    return c2;
  } else if ((x + y) % 3 == 0 || (x + y) % 5 == 0) {
    return c1;
  } else {
    return c3;
  }
}
