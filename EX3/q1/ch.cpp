#include"ch.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <chrono>
using namespace std::chrono;
using namespace std;

typedef pair<double, double> Point;

// מכפלה וקטורית AB × AC
double cross(const Point& A, const Point& B, const Point& C) {
    return (B.first - A.first) * (C.second - A.second) -
           (B.second - A.second) * (C.first - A.first);
}

// מחשב את המעטפת הקמורה
vector<Point> convexHull(vector<Point>& points) {
    // מיון לפי x ואז y
    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return (a.first < b.first) || (a.first == b.first && a.second < b.second);
    });

    vector<Point> hull;

    // חלק תחתון
    for (const auto& p : points) {
        while (hull.size() >= 2 &&
               cross(hull[hull.size()-2], hull[hull.size()-1], p) < 0)
            hull.pop_back();
        hull.push_back(p);
    }

    // חלק עליון
    size_t lower_size = hull.size();
    for (int i = points.size() - 2; i >= 0; --i) {
        while (hull.size() > lower_size &&
               cross(hull[hull.size()-2], hull[hull.size()-1], points[i]) < 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    if (hull.size() > 1)
        hull.pop_back(); // מסירים חזרה כפולה

    return hull;
}

// חישוב שטח פוליגון לפי נוסחת Shoelace
double polygonArea(const vector<Point>& poly) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += poly[i].first * poly[j].second - poly[j].first * poly[i].second;
    }
    return abs(area) / 2.0;
}

int main() {
    int n;
    cout << "Enter number of vertex:" << endl;
    cin >> n;
    vector<Point> points;
    cin.ignore(); // מדלג על '\n'

    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line); // קורא שורה בפורמט "x,y"

        int commaPos = line.find(',');
        string x_str = line.substr(0, commaPos);
        string y_str = line.substr(commaPos + 1);

        double x = atof(x_str.c_str());
        double y = atof(y_str.c_str());

        points.push_back({x, y});
    }

 auto start = high_resolution_clock::now(); // זמן התחלה
 
    for (int i = 0; i < 100000; i++)
    {
   
    
    // הדפסת הנקודות שהוזנו
    cout << "\nPoints:\n";
    for (const auto& p : points) {
        cout << p.first << "," << p.second << endl;
    }

    // חישוב המעטפת הקמורה
    vector<Point> hull = convexHull(points);

    // הדפסת המעטפת הקמורה
    cout << "\nConvex Hull:\n";
    for (const auto& p : hull) {
        cout << p.first << "," << p.second << endl;
    }

    // חישוב שטח
    double area = polygonArea(hull);
    cout << "\nConvex Hull Area: " << area << endl;
    }
    auto stop = high_resolution_clock::now(); // זמן סיום

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Run time: " << duration.count() << " milliseconds" << endl;
    return 0;
}