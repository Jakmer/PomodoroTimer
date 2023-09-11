#include "Server.h"

void Server::handle_client(int &&client_fd)
{
    const size_t SIZE = 1024;
    char buffer[SIZE];
    Choice choice;
    Timer timer{};

    do
    {

        int bytesReceived = recv(client_fd, buffer, sizeof(choice), 0);
        if (errno == EAGAIN)
            continue;
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

        choice = static_cast<Choice>(buffer[0]);

        strcpy(buffer, timer.take_action(choice).c_str());

        if (send(client_fd, &buffer, sizeof(buffer), 0) == -1)
        {
            if (errno == EAGAIN)
                continue;
            throw std::runtime_error("Error sending to server: ");
        }
    } while (choice != Quit);

    std::cout
        << "Client [" << client_fd << "] disconnected\n";
    close(client_fd);
}

Server::Server()
{
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        throw std::runtime_error("Error creating socket: ");
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        throw std::runtime_error("Error binding to address: ");
    }

    if (listen(server_fd, 5) == -1)
    {
        throw std::runtime_error("Error listening for connections: ");
    }
    std::cout << "Server listening for incoming connections..." << std::endl;
}

Server::~Server()
{
    for (auto &thread : client_threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
    close(server_fd);
}

void Server::run()
{
    while (true)
    {
        int client_fd = accept(server_fd, nullptr, nullptr);

        if (client_fd == -1)
        {
            close(client_fd);
            throw std::runtime_error("Error accepting client connection: ");
        }
        std::cout << "Client [" << client_fd << "] connected" << std::endl;
        client_threads.emplace_back(&Server::handle_client, this, client_fd);
    }
}