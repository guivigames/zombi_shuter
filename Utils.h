#pragma once

#include <SFML/Graphics.hpp>

///< My definitions of SFML vector arithmetic.
template <typename T>
sf::Vector2<T> operator*(const sf::Vector2<T>& left, const sf::Vector2<T>& right);
template <typename T>
sf::Vector2<T> operator*(const sf::Vector2<T>& left, const T right);
template <typename T>
sf::Vector2i floor(const sf::Vector2<T>& vector);

///< Algorithms for object collition.
// CIRCLE/RECTANGLE
bool circleRect(float cx, float cy, float rad, float rx, float ry, float rw, float rh);
// CIRCLE/CIRCLE
bool circleCircle(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r);
// TRIANGLE/POINT
bool triPoint(float x1, float y1, float x2, float y2, float x3, float y3, float px, float py);