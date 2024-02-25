#ifndef TIMER
#define TIMER
#include <iostream>
#include <chrono>
#include <thread>

class Timer
{
private:
    const std::chrono::minutes WORK{25};
    const std::chrono::minutes SHORT_BREAK{5};
    const std::chrono::minutes LONG_BREAK{20};

    bool isRunning;
    std::thread intervalThread;
    std::chrono::duration<int, std::milli> remaining_time;
    int pomodoro;

public:
    Timer();
    void start();
    void stop();
    void skip();
    void restart();
    std::string getTime();
    void handleTime();
    ~Timer();
};

#endif
