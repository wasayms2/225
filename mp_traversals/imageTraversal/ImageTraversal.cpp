#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}


/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  //
  traversal = NULL;
  point1 = Point(unsigned(-1), unsigned(-1));
  traversed = new bool[1];


  /** @todo [Part 1] */
}
ImageTraversal::Iterator::Iterator(PNG & image, Point p, ImageTraversal & trav, double tol) {

  traversal = &trav;
  start = p;
  image1 = &image;
  tolerance = tol;
  // tolerance = tol;
  point1 = traversal->peek();
  double dimension = image1->width() * image1->height();
  //create boolean array used to check if been to the point
  traversed = new bool[dimension];
  for (unsigned i = 0; i < dimension; i++) {
    traversed[i] = 0;
  }

}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  // check if been to the point, within calculateDelta, and if it exists
  if(!traversal -> empty()){
    point1 = traversal -> pop();
    //check right of pixel

    traversed[point1.x+point1.y*image1 -> width()] = true;
    HSLAPixel & p2 = image1 -> getPixel(start.x, start.y);
    if(point1.x + 1 < image1 -> width()){
      HSLAPixel & p1 = image1 -> getPixel(point1.x + 1, point1.y);
      //check if within tolerance
      if(calculateDelta(p1, p2) < tolerance){
        traversal -> add(Point(point1.x + 1, point1.y));
      }
    }
    //check above pixel
    if(point1.y + 1 < image1 -> height()){
      HSLAPixel & p5 = image1 -> getPixel(point1.x, point1.y + 1);
      //check if within tolerance
      if(calculateDelta(p5, p2) < tolerance){
        traversal -> add(Point(point1.x, point1.y + 1));
      }
    }
    //check left of pixel
    if(int(point1.x) - 1 >= 0){
      HSLAPixel & p4 = image1 -> getPixel(point1.x - 1, point1.y);
      //check if within tolerance
      if(calculateDelta(p4, p2) < tolerance){
        traversal -> add(Point(point1.x - 1, point1.y));
      }
    }
    //check below pixel
    if(int(point1.y) - 1 >= 0){
      HSLAPixel & p3 = image1 -> getPixel(point1.x, point1.y - 1);
      //check if within tolerance
      if(calculateDelta(p3, p2) < tolerance){
        traversal -> add(Point(point1.x, point1.y - 1));
      }
    }
    point1 = traversal -> peek();
    //check if already been to the point/pixel
    while(traversed[point1.x + point1.y * image1 -> width()] == true){
      traversal -> pop();
      point1 = traversal -> peek();
      if(int(point1.x) == -1 && int(point1.y) == -1){
        this -> point1 = Point(-1,-1);
        traversal -> pop();
        return * this;
      }
    }
  }
return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return Point(point1.x, point1.y);
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  //use operator within Point class
  if(this->point1 < other.point1) {
    return true;
  } else if (other.point1 < this->point1) {
    return true;
  } else {
    return false;
  }

}
