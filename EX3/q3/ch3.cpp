#include"ch3.hpp"
#include <iostream>
#include <list>
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

// פונקציית מיון מותאמת ל־list
bool pointCompare(const Point& a, const Point& b) {
    return (a.first < b.first) || (a.first == b.first && a.second < b.second);
}

// מחשב את המעטפת הקמורה עם list בלבד
list<Point> convexHull_list(list<Point>& points) {
    points.sort(pointCompare); // מיון רשימה

    list<Point> hull;

    // חלק תחתון
    for (const auto& p : points) {
        while (hull.size() >= 2) {
            auto last = prev(hull.end());
            auto second_last = prev(last);
            if (cross(*second_last, *last, p) < 0)
                hull.pop_back();
            else break;
        }
        hull.push_back(p);
    }

    // חלק עליון
    size_t lower = hull.size();
    for (auto it = ++points.rbegin(); it != points.rend(); ++it) {
        while (hull.size() > lower) {
            auto last = prev(hull.end());
            auto second_last = prev(last);
            if (cross(*second_last, *last, *it) < 0)
                hull.pop_back();
            else break;
        }
        hull.push_back(*it);
    }

    hull.pop_back(); // הסר כפילות

    return hull;
}

// חישוב שטח לפי Shoelace
double polygonArea(const list<Point>& poly) {
    double area = 0;
    auto it1 = poly.begin();
    auto it2 = next(it1);

    while (it2 != poly.end()) {
        area += it1->first * it2->second - it2->first * it1->second;
        ++it1;
        ++it2;
    }

    // חיבור אחרון מול הראשון
    area += it1->first * poly.begin()->second - poly.begin()->first * it1->second;

    return abs(area) / 2.0;
}

int main() {

    list<Point> points;

    while (true)
    {
        cout << "1) new commends:" << endl;
        cout << "2) Newgraph n"<< endl;
        cout << "3) CH"<< endl;
        cout << "4) Newpoint i,j"<< endl;
        cout << "5) Removepoint i,j"<< endl;
    
    string commend;
    getline(cin, commend);
    size_t pos = commend.find(' '); // מוצא את מיקום הרווח הראשון
        string before_space;
        string after_space ;
    if (pos != string::npos) {
         before_space = commend.substr(0, pos);      // החלק שלפני הרווח
         after_space = commend.substr(pos+1);
         
    }
    else{
        before_space=commend;
    }

    if (before_space=="Newgraph")
    {
        int n= stoi(after_space);
    
        for (int i = 0; i < n; ++i) {
            string line;
            getline(cin, line);
            int comma = line.find(',');
            double x = atof(line.substr(0, comma).c_str());
            double y = atof(line.substr(comma + 1).c_str());
            points.emplace_back(x, y);
        }
    }
     
    
    if(before_space== "CH"){

        if(points.size()>0){
        list<Point> hull = convexHull_list(points);

        cout << "\nConvex Hull:\n";
        for (const auto& p : hull)
            cout << p.first << "," << p.second << endl;
        
        double area = polygonArea(hull);
        cout << "\nConvex Hull Area: " << area << endl;
        }
        else{
            cout<< "the gragh has no points."<<endl;
            cout<< "please enter points befor trying agein!"<<endl<<endl;
        }
        
    }
    if(before_space=="Newpoint"){
            int comma = after_space.find(',');
            double x = atof(after_space.substr(0, comma).c_str());
            double y = atof(after_space.substr(comma + 1).c_str());
            points.emplace_back(x, y);
    }
        
    if(before_space== "Removepoint"){ 
        int comma = after_space.find(',');
            double x = atof(after_space.substr(0, comma).c_str());
            double y = atof(after_space.substr(comma + 1).c_str());
            Point toRemove = {x,y};
            points.remove(toRemove);
        }
    }
    

  


 
    

    cout << "\nInput Points:\n";
    for (const auto& p : points)
        cout << p.first << "," << p.second << endl;
    
    
   

    
  
    
    return 0;
}