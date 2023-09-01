#include <iostream>
#include "Server.h"
#include <cstring>
#include <mutex>

int main()
{
    try
    {   std::mutex mtx;
        Server server{mtx};
        server.startListening();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << strerror(errno) << '\n';
    }

    return 0;
}