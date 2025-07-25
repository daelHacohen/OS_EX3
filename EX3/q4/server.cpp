#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <fcntl.h>
#include <list>
#include <thread>
#include <string>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <mutex>
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








void handle(int client_socket);

list<Point> points;
int main() {
    int max_fd;
    int client_fd;
    //list<Point> points;

    int server_fd, client_socket;
    fd_set master_set, read_fds;
    sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    // יצירת socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        return 1;
    }

    // הגדרת כתובת השרת
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(9034); // פורט כמו של beej

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    // קישור (bind)
    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 1;
    }

    // האזנה (listen)
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        return 1;
    }
    
    FD_ZERO(&master_set);
    FD_SET(server_fd, &master_set);
    max_fd = server_fd;

    cout <<"waiting on 9034" << endl;
    //client_socket = accept(server_fd, (sockaddr*)&address, (socklen_t*)&addrlen);
    while (true)
    {
        read_fds = master_set;

        if (select(max_fd + 1, &read_fds, nullptr, nullptr, nullptr) < 0) {
            perror("select error");
            break;
        }


          for (int fd = 0; fd <= max_fd; ++fd) {
            if (!FD_ISSET(fd, &read_fds)) continue;

            if (fd == server_fd) {
                // לקוח חדש
                 client_fd = accept(server_fd, (sockaddr*)&address, &addrlen);
                if (client_fd >= 0) {
                    FD_SET(client_fd, &master_set);
                    if (client_fd > max_fd) max_fd = client_fd;
                    cout << "New client connected (fd=" << client_fd << ")\n";
                }
            } else {
                handle(fd);
            }
        }
    }
        //client_socket = accept(server_fd, (sockaddr*)&address, (socklen_t*)&addrlen);
        
    }
    

    

    


void handle(int client_socket){
    
    char buffer[1024] = {0};
    memset(buffer, 0, sizeof(buffer));
    
      
    
    int valread = read(client_socket, buffer, 1024);  // ← צריך לשמור את מספר הבייטים שהתקבלו
    string input;
    if (valread > 0) {
        input =string(buffer, valread); // יוצר מחרוזת בדיוק עם valread תווים
        cout << "got"  << input << endl;
    }



    
    size_t pos=input.find(' '); // מוצא את מיקום הרווח הראשון
        string before_space;
        string after_space ;
    if (pos != string::npos) {
         before_space = input.substr(0, pos);      // החלק שלפני הרווח
         after_space = input.substr(pos+1);
         
    }
    else{
        before_space=input;
    }

    if (before_space=="Newgraph")
    {
        int n= stoi(after_space);
    
        for (int i = 0; i < n; ++i) {
            int valread = read(client_socket, buffer, 1024);  // ← צריך לשמור את מספר הבייטים שהתקבלו
            string input;
            if (valread > 0) {
                input =string(buffer, valread); // יוצר מחרוזת בדיוק עם valread תווים
                cout << "got"  << input << endl;
            }
            int comma = input.find(',');
            double x = atof(input.substr(0, comma).c_str());
            double y = atof(input.substr(comma + 1).c_str());
            points.emplace_back(x, y);
        }

        cout << "my Points:\n";
        for (const auto& p : points){
        cout << p.first << "," << p.second << endl;
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
            cout << "my Points:\n";
            for (const auto& p : points){cout << p.first << "," << p.second << endl;}
            
    }
        
    if(before_space== "Removepoint"){ 
        int comma = after_space.find(',');
            double x = atof(after_space.substr(0, comma).c_str());
            double y = atof(after_space.substr(comma + 1).c_str());
            Point toRemove = {x,y};
            points.remove(toRemove);
            
    cout << "my Points:\n";
    for (const auto& p : points){
        cout << p.first << "," << p.second << endl;
        }}

    if (before_space=="stop")
    {
       return;
    }
    


}
