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
    Client()
    {
        client_fd = socket(AF_INET, SOCK_STREAM, 0); /* takie cos powinno byc w init list czy w ciele konstrukotra? */
        if (client_fd == -1)
        {
            throw std::runtime_error("Error creating socket: ");
        }
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(8080);
        inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
    }

    void connect_to_server()
    {
        if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
        {
            throw std::runtime_error("Error connecting to server: ");
        }
    }

    void receive_from_server()
    {
        int bytesReceived = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0)
        {
            if (bytesReceived == 0)
            {
                throw std::runtime_error("Disconnected: ");
            }
            else
            {
                throw std::runtime_error("Error receiving data: ");
            }
        }
        if(buffer[0]==Quit)
        {
            delete this;
        }
        std::cout<<buffer<<"\n";
    }

    void send_to_server(Choice &choice)
    {
        if (send(client_fd, &choice, sizeof(choice), 0) == -1)
        {
            throw std::runtime_error("Error sending to server: ");
        }
    }

    ~Client()
    {
        close(client_fd);
    }

    friend std::istream &operator>>(std::istream &is, Choice &choice);
};

#endif