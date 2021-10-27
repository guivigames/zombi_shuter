#include "Utils.h"
#include <math.h>

///< My definitions of SFML vector arithmetic.

/// @brief multiply two vectors. 
template <typename T>
sf::Vector2<T> operator*(const sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
    T X = left.x * right.x;
    T Y = left.y * right.y;
    return sf::Vector2<T>(X,Y);
}

/// @brief multiply a vector and a scalar.
template <typename T>
sf::Vector2<T> operator*(const sf::Vector2<T>& left, const T right)
{
    T X = left.x * right;
    T Y = left.y * right;
    return sf::Vector2<T>(X,Y);
}

/// @brief return ths rounded down vector.
template <typename T>
sf::Vector2i floor(const sf::Vector2<T>& vector)
{
    int X = floor(vector.x);
    int Y = floor(vector.y);
    return sf::Vector2i(X,Y);
}

///< Algorithms for object collition.
// CIRCLE/RECTANGLE
bool circleRect(float cx, float cy, float rad, float rx, float ry, float rw, float rh) 
{
  // temporary variables to set edges for testing
  float testX = cx;
  float testY = cy;

  // which edge is closest?
  if (cx < rx)         testX = rx;      // test left edge
  else if (cx > rx+rw) testX = rx+rw;   // right edge
  if (cy < ry)         testY = ry;      // top edge
  else if (cy > ry+rh) testY = ry+rh;   // bottom edge

  // get distance from closest edges
  float distX = cx-testX;
  float distY = cy-testY;
  float distance = sqrt( (distX*distX) + (distY*distY) );

  // if the distance is less than the radius, collision!
  if (distance+0.01 < rad) {
    return true;
  }
  return false;
}
// CIRCLE/CIRCLE
bool circleCircle(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r) {

  // get distance between the circle's centers
  // use the Pythagorean Theorem to compute the distance
  float distX = c1x - c2x;
  float distY = c1y - c2y;
  float distance = sqrt( (distX*distX) + (distY*distY) );

  // if the distance is less than the sum of the circle's
  // radii, the circles are touching!
  if (distance <= c1r+c2r) {
    return true;
  }
  return false;
}
// TRIANGLE/POINT
bool triPoint(float x1, float y1, float x2, float y2, float x3, float y3, float px, float py) {

  // get the area of the triangle
  float areaOrig = abs( (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1) );

  // get the area of 3 triangles made between the point
  // and the corners of the triangle
  float area1 =    abs( (x1-px)*(y2-py) - (x2-px)*(y1-py) );
  float area2 =    abs( (x2-px)*(y3-py) - (x3-px)*(y2-py) );
  float area3 =    abs( (x3-px)*(y1-py) - (x1-px)*(y3-py) );

  // if the sum of the three areas equals the original,
  // we're inside the triangle!
  if (area1 + area2 + area3 == areaOrig) {
    return true;
  }
  return false;
}