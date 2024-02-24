#include "Client.hpp"
#include "Message.hpp"

int main(int arc, char ** argv)
{
    // here we need to check if there are any argument but for lets suppose its OK
    Message msg{argv[1],argv[2]};
    Client client{msg};
    client.run();

    return 0;
}