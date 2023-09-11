#include <iostream>
#include "Client.h"
#include "EChoice.h"
#include <cstring>

int main()
{
    try
    {
        Client client{};
        client.run();
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