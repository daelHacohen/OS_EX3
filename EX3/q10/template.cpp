#include "template.hpp"

Proactor::Proactor() : sockfd(-1), running(false), handler(nullptr), threadId(0) {}

Proactor::~Proactor() {
    stopProactor(threadId);
}

pthread_t Proactor::startProactor(int sockfd, proactorFunc threadFunc) {
    this->sockfd = sockfd;
    this->handler = threadFunc;
    running = true;

    proactorThread = std::thread(&Proactor::run, this);
    threadId = proactorThread.native_handle();
    return threadId;
}

int Proactor::stopProactor(pthread_t tid) {
    if (tid != threadId) {
        std::cerr << "Invalid thread ID\n";
        return -1;
    }

    running = false;
    close(sockfd);

    if (proactorThread.joinable())
        proactorThread.join();

    return 0;
}

void Proactor::run() {
    while (running) {
        int clientSock = accept(sockfd, nullptr, nullptr);
        if (clientSock < 0) {
            if (!running) break;
            perror("accept");
            continue;
        }

        std::thread(handler, clientSock).detach();
    }
}

