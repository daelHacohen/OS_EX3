#ifndef CONVEX_HULL_HPP
#define CONVEX_HULL_HPP

#include <vector>
#include <utility>

typedef std::pair<double, double> Point;

// מכריז על הפונקציות בלבד

double cross(const Point& A, const Point& B, const Point& C);

std::vector<Point> convexHull(std::vector<Point>& points);

double polygonArea(const std::vector<Point>& poly);

#endif // CONVEX_HULL_HPP
