#ifndef REACTOR_HPP
#define REACTOR_HPP

#include <unordered_map>
#include <sys/select.h>
#include <unistd.h>

#include <functional>
typedef std::function<void(int)> reactorFunc;

//template<typename reactorFunc>
class Reactor {

private:
    std::unordered_map<int, reactorFunc> callbacks;
    int max_fd;
    bool running;
public:
    Reactor();
    ~Reactor();

    void addFdToReactor(int fd, reactorFunc func);
    void removeFdFromReactor(int fd);
    void startReactor();
    void stopReactor();

};


#endif // REACTOR_HPP
