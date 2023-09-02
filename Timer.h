#ifndef TIMER_H
#define TIMER_H
#include "EChoice.h"
#include <iostream>
#include <cstring>
#include <chrono>
#include <memory>

class Timer
{
    const std::chrono::minutes WORK{25};
    const std::chrono::minutes SHORT_BREAK{5};
    const std::chrono::minutes LONG_BREAK{20};

    std::chrono::duration<int, std::milli> remaining_time;
    bool is_active, stop_flag;
    int pomodoro;
    char *buffer; // tutaj pownien byc smart czy raw pointer
    std::thread interval_thread;    //  ten watek tez powinien miec mutexa? jesli tak to czy tego samego co watki klasy Server?

public:
    Timer(char (&buff)[1024]) : is_active(false), pomodoro(0), buffer(buff), interval_thread(&Timer::handle_time, this), stop_flag(false), remaining_time(WORK)
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
            break;
        case Quit:
            quit(choice);
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
        time("Start");
    }

    void stop()
    {
        is_active = false;
        time("Stop");
    }

    void skip()
    {
        pomodoro++;
        is_active = false;
        if (pomodoro % 2 == 0)
        {
            remaining_time = WORK;
        }
        else
        {
            // w s w s w s w l
            // 0 1 2 3 4 5 6 7
            if ((pomodoro + 1) % 8 == 0)
            {
                remaining_time = LONG_BREAK;
            }
            else
            {
                remaining_time = SHORT_BREAK;
            }
        }
        time("Skip");
    }

    void restart()
    {
        is_active = false;
        time("Restart");
    }

    void get_time()
    {
        time("Get time");
    }

    void quit(Choice &choice)
    {
        buffer[0] = choice;
        stop_flag = true;
    }

    void handle_time()
    {
        while (!stop_flag)
        {
            if (is_active)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));

                remaining_time -= std::chrono::milliseconds(50);

                if (std::chrono::duration_cast<std::chrono::milliseconds>(remaining_time).count() <= 0)
                {
                    skip();
                }
            }
        }
    }

    void time(std::string &&label)
    {
        int minutes = std::chrono::duration_cast<std::chrono::minutes>(remaining_time).count();
        int seconds = std::chrono::duration_cast<std::chrono::seconds>(remaining_time % std::chrono::minutes(1)).count();

        std::string minutes_str = std::to_string(minutes);
        std::string seconds_str = std::to_string(seconds);

        std::string response = label+" - time left: "+minutes_str + "m " + seconds_str + "s";

        strcpy(buffer, response.c_str());
    }

    ~Timer()
    {
        interval_thread.join();
    }
};

#endif