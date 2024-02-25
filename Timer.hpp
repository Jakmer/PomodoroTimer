#ifndef TIMER
#define TIMER
#include <iostream>

class Timer
{
public:
    void start();
    void stop();
    void skip();
    void restart();
    std::string getTime();
};

#endif
