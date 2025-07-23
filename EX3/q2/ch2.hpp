#ifndef CONVEX_HULL_HPP2
#define CONVEX_HULL_HPP2

#include <vector>
#include <utility>

typedef std::pair<double, double> Point;

// מכריז על הפונקציות בלבד

double cross(const Point& A, const Point& B, const Point& C);

std::vector<Point> convexHull(std::vector<Point>& points);

double polygonArea(const std::vector<Point>& poly);

#endif // CONVEX_HULL_HPP
