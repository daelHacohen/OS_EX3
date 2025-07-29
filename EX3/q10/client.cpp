#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

int main() {
    int sock = 0;
    sockaddr_in serv_addr;

    // יצירת socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket failed");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9034); // חייב להתאים לשרת

    // המרה של כתובת IP
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        return 1;
    }

    // התחברות לשרת
    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }
    while (true)
    {
        cout << "1) new commends:" << endl;
        cout << "2) Newgraph n"<< endl;
        cout << "3) CH"<< endl;
        cout << "4) Newpoint i,j"<< endl;
        cout << "5) Removepoint i,j"<< endl;
        cout << "6) stop"<< endl;

    
    string commend;
    getline(cin, commend);
    send(sock, commend.c_str(), commend.size(), 0);

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
            send(sock, line.c_str(), line.size(), 0);
        }
    }
     


    if (commend=="stop")
    {
        send(sock, commend.c_str(), commend.size(), 0);   
        close(sock);
        return 0;
    }
    

    
    }

   
}