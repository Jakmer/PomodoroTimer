#include "Timer.hpp"

Timer::Timer() : isRunning(false), pomodoro(0), remaining_time(WORK), intervalThread(&Timer::handleTime, this)
{
}

void Timer::handleTime()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        if (isRunning)
        {
            remaining_time -= std::chrono::milliseconds(50);

            if (std::chrono::duration_cast<std::chrono::milliseconds>(remaining_time).count() <= 0)
            {
                skip();
            }
        }
    }
}

void Timer::start()
{
    isRunning = true;
}

void Timer::stop()
{
    isRunning = false;
}

void Timer::skip()
{
    pomodoro++;
    isRunning = false;
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
}

void Timer::restart()
{
    isRunning = false;
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
}

std::string Timer::getTime()
{
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(remaining_time).count();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(remaining_time % std::chrono::minutes(1)).count();

    auto minutes_str = std::to_string(minutes);
    auto seconds_str = std::to_string(seconds);

    auto response = minutes_str + "m " + seconds_str + "s";

    return response;
}

Timer::~Timer()
{
    intervalThread.join();
}