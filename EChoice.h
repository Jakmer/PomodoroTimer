#ifndef CHOICE_H
#define CHOICE_H
#include <iostream>


enum Choice
{
    Start = '1',
    Stop,
    Skip,
    Restart,
    Get_time,
    Quit,
    Unknown
};

std::istream &operator>>(std::istream &is, Choice &choice);

std::ostream &operator<<(std::ostream &os, Choice &choice);

#endif