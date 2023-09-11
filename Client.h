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
    Choice choice;

    void connect_to_server();

    std::string receive_from_server();

    void send_to_server(Choice &choice);

public:
    Client();

    void run();

    ~Client();

    friend std::istream &operator>>(std::istream &is, Choice &choice);
};

#endif