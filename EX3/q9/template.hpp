#ifndef PROACTOR_HPP
#define PROACTOR_HPP

#include <thread>
#include <functional>
#include <atomic>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>

typedef void* (*proactorFunc)(int sockfd);

class Proactor {
private:
    int sockfd;
    std::atomic<bool> running;
    proactorFunc handler;

    std::thread proactorThread;
    pthread_t threadId;

public:
    Proactor();
    ~Proactor();

    pthread_t startProactor(int sockfd, proactorFunc threadFunc);
    int stopProactor(pthread_t tid);

private:
    void run();
};

#endif // PROACTOR_HPP
