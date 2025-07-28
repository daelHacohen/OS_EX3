#include <unordered_map>
#include <sys/select.h>
#include <unistd.h>
#include "reactor.hpp"
#include <functional>

Reactor::Reactor() : max_fd(0), running(false) {}


Reactor::~Reactor() {
    stopReactor();
}


void Reactor::addFdToReactor(int fd, reactorFunc func) {
    callbacks[fd] = func;
    if (fd > max_fd) max_fd = fd;
}


void Reactor::removeFdFromReactor(int fd) {
    callbacks.erase(fd);
}


void Reactor::startReactor() {
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

void Reactor::stopReactor() {
    running = false;
}

