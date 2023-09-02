#ifndef CLIENT_H
#define CLIENT_H
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include "EChoice.h"

class Client
{
private:
    int client_fd;
    sockaddr_in server_address;
    char buffer[1024];

public:
    Client();

    void connect_to_server();

    void receive_from_server();

    void send_to_server(Choice &choice);

    ~Client();

    friend std::istream &operator>>(std::istream &is, Choice &choice);
};

#endif