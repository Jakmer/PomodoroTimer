#include "Client.hpp"
#include "Message.hpp"

int main(int arc, char **argv)
{
    Message msg;
    try
    {
        if (arc == 2)
        {
            msg = Message{argv[1], "White"};
        }
        else if (arc == 3)
        {
            msg = Message{argv[1], argv[2]};
        }
        else
        {
            throw std::runtime_error("CLient: Invalid number of args");
        }

        Client client{msg};
        client.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}