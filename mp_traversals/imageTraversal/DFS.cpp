#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) { //xiao
  /** @todo [Part 1] */
  start_ = start;
  tolerance_ = tolerance;
  png_ = png;
  visited = new bool*[png.width()];
  for(unsigned i = 0; i < png.width(); i++) {
    visited[i] = new bool[png.height()];
  }
  for(unsigned i = 0; i < png.width(); i++) {
    for (unsigned j = 0; j < png.height(); j++) {
      visited[i][j] = false;
    }
  }
  point_s.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal* dfs = new DFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(*dfs, start_,png_, tolerance_);

}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  point_s.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  // std::cout<<"debugpop"<<std::endl;
  Point topop = point_s.top();
  point_s.pop();
  return topop;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  if (point_s.empty()) {
    return Point(-1,-1);
  }
  return point_s.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  if (point_s.empty()) {
    return true;
  }
  return false;
}
