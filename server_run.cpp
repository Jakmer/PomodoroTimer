#include <iostream>
#include "Server.h"
#include <cstring>

int main()
{
    try
    {
        Server server{};
        server.startListening();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << strerror(errno) << '\n';
    }

    return 0;
}