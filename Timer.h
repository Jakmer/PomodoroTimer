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
    char *buffer;                // tutaj pownien byc smart czy raw pointer
    std::thread interval_thread; //  ten watek tez powinien miec mutexa? jesli tak to czy tego samego co watki klasy Server?

    void start();

    void stop();

    void skip();

    void restart();

    void get_time();

    void quit(Choice &choice);

    void handle_time();

    void time(std::string &&label);

public:
    Timer(char (&buff)[1024]);

    void take_action();

    ~Timer();
};

#endif