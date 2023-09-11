#ifndef TIMER_H
#define TIMER_H
#include "EChoice.h"
#include <iostream>
#include <cstring>
#include <chrono>
#include <memory>
#include <thread>

class Timer
{
    const std::chrono::minutes WORK{25};
    const std::chrono::minutes SHORT_BREAK{5};
    const std::chrono::minutes LONG_BREAK{20};

    std::chrono::duration<int, std::milli> remaining_time;
    bool is_active, stop_flag;
    int pomodoro;               
    std::thread interval_thread;

    void start();

    void stop();

    void skip();

    void restart();

    void quit();

    void handle_time();

    std::string get_time();

public:
    Timer();

    std::string take_action(Choice &choice);

    ~Timer();
};

#endif