#include "Timer.h"

Timer::Timer() : is_active(false), pomodoro(0), interval_thread(&Timer::handle_time, this), stop_flag(false), remaining_time(WORK)
{
}

std::string Timer::take_action(Choice &choice)
{

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
        break;
    case Quit:
        quit();
        break;
    default:

        throw std::runtime_error("Unrecognised action in timer: ");
        return "";
        break;
    }

    return get_time();
}

void Timer::start()
{
    is_active = true;
    get_time();
}

void Timer::stop()
{
    is_active = false;
    get_time();
}

void Timer::skip()
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
    get_time();
}

void Timer::restart()
{
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
    get_time();
}

void Timer::quit()
{
    stop_flag = true;
}

void Timer::handle_time()
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

std::string Timer::get_time()
{
    int minutes = std::chrono::duration_cast<std::chrono::minutes>(remaining_time).count();
    int seconds = std::chrono::duration_cast<std::chrono::seconds>(remaining_time % std::chrono::minutes(1)).count();

    std::string minutes_str = std::to_string(minutes);
    std::string seconds_str = std::to_string(seconds);

    std::string response = minutes_str + "m " + seconds_str +"s";

    return response;
}

Timer::~Timer()
{
    interval_thread.join();
}