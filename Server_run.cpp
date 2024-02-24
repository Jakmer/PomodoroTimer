#include "Server.hpp"

int main()
{
    try
    {
        Server server{};
        server.run();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}