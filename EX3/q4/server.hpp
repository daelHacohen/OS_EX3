#ifndef GEOMETRY_UTILS_HPP
#define GEOMETRY_UTILS_HPP

#include <list>
#include <utility>
#include <cmath>
#include <algorithm>

typedef std::pair<double, double> Point;

// מכפלה וקטורית AB × AC
double cross(const Point& A, const Point& B, const Point& C);

// פונקציית מיון נקודות
bool pointCompare(const Point& a, const Point& b);

// חישוב מעטפת קמורה
std::list<Point> convexHull_list(std::list<Point>& points);

// חישוב שטח לפי Shoelace
double polygonArea(const std::list<Point>& poly);

#endif // GEOMETRY_UTILS_HPP
