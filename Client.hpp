#ifndef CLIENT
#define CLIENT
#include "Message.hpp"
#include <netinet/in.h>

class Client
{

private:
    int client_fd;
    sockaddr_in serverAddress; 
    Message msg;

    void setup();
    void request();
    void receive();

public:
    Client(Message &msg);
    void run();
};

#endif