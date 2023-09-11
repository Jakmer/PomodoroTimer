#include <iostream>
#include "Server.h"
#include <cstring>
#include <mutex>

int main()
{
    try
    { 
        Server server ;
        server.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << strerror(errno) << '\n';
        return 1;
    }
    catch(...)
    {
        std::cerr << "Default exception" << strerror(errno) << '\n';
        return 1;
    }

    return 0;
}