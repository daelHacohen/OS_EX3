#ifndef REACTOR_HPP
#define REACTOR_HPP

#include <unordered_map>
#include <sys/select.h>
#include <unistd.h>


template<typename FuncType>
class Reactor {

private:
    std::unordered_map<int, FuncType> callbacks;
    int max_fd;
    bool running;
public:
    Reactor();
    ~Reactor();

    void addFdToReactor(int fd, FuncType func);
    void removeFdFromReactor(int fd);
    void startReactor();
    void stopReactor();

};

// === מימוש ===

template<typename FuncType>
Reactor<FuncType>::Reactor() : max_fd(0), running(false) {}

template<typename FuncType>
Reactor<FuncType>::~Reactor() {
    stopReactor();
}

template<typename FuncType>
void Reactor<FuncType>::addFdToReactor(int fd, FuncType func) {
    callbacks[fd] = func;
    if (fd > max_fd) max_fd = fd;
}

template<typename FuncType>
void Reactor<FuncType>::removeFdFromReactor(int fd) {
    callbacks.erase(fd);
}

template<typename FuncType>
void Reactor<FuncType>::startReactor() {
    running = true;
    while (running) {
        fd_set readfds;
        FD_ZERO(&readfds);

        for (const auto& [fd, _] : callbacks) {
            FD_SET(fd, &readfds);
        }

        int activity = select(max_fd + 1, &readfds, nullptr, nullptr, nullptr);
        if (activity < 0) continue;

        for (const auto& [fd, func] : callbacks) {
            if (FD_ISSET(fd, &readfds)) {
                func(fd);
            }
        }
    }
}

template<typename FuncType>
void Reactor<FuncType>::stopReactor() {
    running = false;
}

#endif // REACTOR_HPP
