#include "Client.hpp"
#include <unistd.h>

void Client::setup()
{
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        throw std::runtime_error("Client: Couldn't create socket");
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (connect(client_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        throw std::runtime_error("Client: Couldn't connect server");
    }
}

Client::Client(Message &msg) : msg(msg)
{
    setup();
}

void Client::receive()
{
    char *buffer{};

    try
    {
        do
        {
            if (recv(client_fd, buffer, sizeof(buffer), 0) == -1)
            {
                throw std::runtime_error("Client: Couldn't receive message");
            }
        } while (errno == EAGAIN);

        msg = Message(buffer);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what();
    }
}

void Client::request()
{
    char *buffer{msg.serialize()};

    try
    {
        do
        {
            if (send(client_fd, buffer, sizeof(buffer), 0) == -1)
            {
                throw std::runtime_error("Client: Couldn't send message");
            }
        } while (errno == EAGAIN);

    }
    catch (std::exception &e)
    {
        std::cerr << e.what();
    }
}

void Client::run()
{
    request(); // for now, client sends only 1 command taken from program arguments
}

Client::~Client()
{
    close(client_fd);
}
