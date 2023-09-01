#ifndef SERVER_H
#define SERVER_H
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include "EChoice.h"
#include <thread>
#include <vector>
#include <mutex>
#include "Timer.h"

class Server
{
private:
    int server_fd;
    sockaddr_in server_address;
    std::vector<std::thread> client_threads;
    std::mutex &mtx;

    void handle_client(int &&client_fd)
    {
        std::lock_guard<std::mutex> lock(mtx);
        
        const size_t SIZE = 1024;
        char buffer[SIZE];
        
        Timer timer {buffer};

        while (buffer[0] != Quit)
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
        
            timer.take_action();

            if (send(client_fd, &buffer, sizeof(buffer), 0) == -1)
            {
                throw std::runtime_error("Error sending to server: ");
            }
        }
        std::cout << "Client [" << client_fd << "] disconnected\n";
    }

public:
    Server(std::mutex &mtx):mtx(mtx)
    {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1)
        {
            throw std::runtime_error("Error creating socket: ");
        }

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(8090);
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

    ~Server()
    {
        close(server_fd);
        for (auto &thread : client_threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }

    void startListening()
    {
        while (true)    // jak wylaczyc serwer?
        {
            int client_fd = accept(server_fd, nullptr, nullptr);
            std::cout << "fd " << client_fd << std::endl;
            if (client_fd == -1)
            {
                throw std::runtime_error("Error accepting client connection: ");
            }
            std::cout << "Client ["<<client_fd<<"] connected" << std::endl;
            client_threads.emplace_back(&Server::handle_client, this, client_fd);
        }
    }
};

#endif