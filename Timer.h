#ifndef TIMER_H
#define TIMER_H
#include "EChoice.h"
#include <iostream>
#include <cstring>
#include <chrono>
#include <memory>

enum Action
{
    work,
    short_break,
    long_break
};

class Timer
{
    const std::chrono::minutes WORK{25};
    const std::chrono::minutes SHORT_BREAK{5};
    const std::chrono::minutes LONG_BREAK{20};

    std::chrono::steady_clock current_time;

    bool is_active;
    Action action_switch;
    int pomodoro;
    char *buffer;  //tutaj pownien byc smart czy raw pointer

public:
    Timer(char (&buff)[1024]) : is_active(false), action_switch(work), pomodoro(0), buffer(buff)
    {
        
    }

    void take_action()
    {
        Choice choice = static_cast<Choice>(buffer[0]);

        switch (choice)
        {
        case Start:
            start();
            break;
        case Stop:
            stop();
            break;
        case Skip:
            skip();
            break;
        case Restart:
            restart();
            break;
        case Get_time:
            get_time();
            strcpy(buffer, "Response");
            break;
        case Quit:
            buffer[0] = choice;
            break;
        default:

            throw std::runtime_error("Unrecognised action in timer: ");
            return;
            break;
        }
    }

    void start()
    {
        is_active = true;
    }

    void stop()
    {
        is_active = false;
    }

    void skip()
    {
        pomodoro++;
        is_active = false;
    }

    void restart()
    {
        is_active = false;
    }

    void get_time()
    {
    }
};

#endif