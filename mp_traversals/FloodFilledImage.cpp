#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  image1 = new PNG(png);
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  ColorPicker* col = &colorPicker;
  ImageTraversal* trav = &traversal;
  //add onto color vector
  colors.push_back(col);
  //add onto traversal vector
  course.push_back(trav);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed pix1d on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image pix1d on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color pix1d on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  animation.addFrame(*image1);
  /** @todo [Part 2] */

  for (int i = 0; i < (int)course.size(); i++) {
    unsigned check = 0;
    ImageTraversal::Iterator begin = course[i]->begin();
    ImageTraversal::Iterator end = course[i]->end();
    //iterate through image
    for(ImageTraversal::Iterator it = begin; it != end; ++it) {
      if (check == frameInterval) {
        animation.addFrame(*image1);
        check = 0;
      }
      //get pixel
      cs225::HSLAPixel& pix1 = image1->getPixel((*it).x, (*it).y);
      //use algorithm for new pixel
      cs225::HSLAPixel nPix = colors[i]->getColor((*it).x, (*it).y);
      //change pixel in image to new pixel
      pix1.h = nPix.h;
      pix1.s = nPix.s;
      pix1.l = nPix.l;
      pix1.a = nPix.a;
      check++;
    }
  }
  animation.addFrame(*image1);
  return animation;
}
