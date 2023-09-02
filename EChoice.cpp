#include "EChoice.h"

std::istream &operator>>(std::istream &is, Choice &choice)
{
    char num;
    is >> num;

    switch (num)
    {
    case Choice::Start:
    case Choice::Stop:
    case Choice::Skip:
    case Choice::Restart:
    case Choice::Get_time:
    case Choice::Quit:
        choice = static_cast<Choice>(num);
        break;

    default:
        std::cout << "Cannot identify your choice...\n";
        choice = Choice::Unknown;
        break;
    }
    return is;
}