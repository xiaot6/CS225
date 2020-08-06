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
  /** @todo [Part 1] */
  current = Point(-1,-1);
}

ImageTraversal::Iterator::Iterator(ImageTraversal & traversal, Point start, PNG png, double tolerance) {
  /** @todo [Part 1] */
  start_ = start;
  png_ = png;
  traversal_ = & traversal;
  current = start;
  visited = new bool*[png.width()];
  for(unsigned i = 0; i < png.width(); i++) {
    visited[i] = new bool[png.height()];
  }
  for(unsigned i = 0; i < png.width(); i++) {
    for (unsigned j = 0; j < png.height(); j++) {
      visited[i][j] = false;
    }
  }
  tolerance_ = tolerance;
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1]

    The pixel to the right, (x + 1),
    The pixel below, (y + 1), and
    The pixel to the left, (x - 1).
    The pixel above, (y - 1),
*/
  current = traversal_->pop();
  HSLAPixel start_pixel = png_.getPixel(start_.x, start_.y);
  //right
  if (current.x + 1 < png_.width()) {
    if (visited[current.x+1][current.y] == false) {
      if (calculateDelta(start_pixel,png_.getPixel(current.x+1, current.y) )<= tolerance_) {
        Point right(current.x + 1, current.y);
        traversal_->add(right);
      }
    }
  }
  //below
  if (current.y + 1 < png_.height()) {
    if (visited[current.x][current.y + 1] == false) {
      if (calculateDelta(start_pixel,png_.getPixel(current.x, current.y + 1 ))<= tolerance_) {
        Point below(current.x, current.y + 1);
        traversal_->add(below);
      }
    }
  }
  //left
  if (current.x >= 1) {
    if (visited[current.x-1][current.y] == false) {
      if (calculateDelta(start_pixel,png_.getPixel(current.x-1, current.y)) <= tolerance_  ) {
        Point left(current.x -1, current.y);
        traversal_->add(left);
      }
    }
  }
  //above
  if (current.y >= 1) {
    if (visited[current.x][current.y - 1] == false) {
      if (calculateDelta(start_pixel,png_.getPixel(current.x, current.y -1) )<= tolerance_) {
        Point above(current.x , current.y - 1);
        traversal_->add(above);
      }
    }
  }
  visited[current.x][current.y] = true;
  current = traversal_->peek();
  while(!traversal_->empty()) {
    if (visited[current.x][current.y] == true) {
      traversal_->pop();
      current= traversal_->peek();
    }
    else {
      break;
    }// if the new is visited
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
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (this->current == other.current) {
    return false;
  }
  return true;
}
