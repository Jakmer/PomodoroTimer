#include "Server.hpp"

Server::Server() : isServerActive(true)
{
    setup();
}

void Server::setup()
{
    try
    {
        // creating socket
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            throw std::runtime_error("Server: Couldn't create socket");
        }

        // address specification
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8080);
        serverAddress.sin_addr.s_addr = INADDR_ANY;

        // binding socket
        if (bind(server_fd, (struct sockaddr *)&serverAddress,
                 sizeof(serverAddress)) == -1)
        {
            throw std::runtime_error("Server: Couldn't bind socket");
        }

        // listening for upcoming connections
        if (listen(server_fd, 5) == -1)
        {
            throw std::runtime_error("Server: Couldn't listen for connection");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        // TODO: do sth to not execute next functions
    }
}

void Server::acceptClients()
{
    while (isServerActive)
    {
        int client_fd;

        try
        {
            if ((client_fd = accept(server_fd, nullptr, nullptr)) == -1)
            {
                throw std::runtime_error("Server: Couldn't accept client socket");
            }

            clients.emplace_back(&Server::handleClient, this, std::ref(client_fd));
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void Server::commandHandler(std::string &&command)
{
    std::lock_guard<std::mutex> guard(timerMutex);

    if (command == "Start")
    {
        timer.start();
    }
    else if (command == "Stop")
    {
        timer.stop();
    }
    else if (command == "Skip")
    {
        timer.skip();
    }
    else if (command == "Restart")
    {
        timer.restart();
    }
    else if (command == "Close")
    {
        isServerActive = false;
    }
    else
    {
        // Invalid command
    }
}

void Server::timeDisplayer()
{
    while (isServerActive)
    {
        system("clear");
        std::lock_guard<std::mutex> guard(timerMutex);
        const std::string ANSI_ESCAPE = "\u001b[" + std::to_string(displayColor)+"m";
        std::cout << ANSI_ESCAPE<<"Time left: "<<timer.getTime()<<displayColor<<"\u001b[0m\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    }
}

void Server::executeCommands()
{

    while (isServerActive)
    {
        std::lock_guard<std::mutex> guard(commandMutex);
        if (!commands.empty())
        {
            Message msg{commands.front()};
            commands.pop();

            displayColor = msg.getColor();
            commandHandler(msg.getCommand());
        }
    }
}

void Server::run()
{
    std::thread t1(&Server::acceptClients, this);
    std::thread t2(&Server::executeCommands, this);
    std::thread t3(&Server::timeDisplayer, this);

    t1.join();
    t2.join();
    t3.join();
}

void Server::handleClient(int &client_fd)
{
    char buffer[BUFFER_SIZE];

    do
    {
        try
        {
            if (recv(client_fd, buffer, sizeof(buffer), 0) == -1)
            {
                throw std::runtime_error("Server: Couldn't receive request");
            }

            std::lock_guard<std::mutex> guard(commandMutex);
            commands.emplace(buffer);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    } while (errno == EAGAIN);
}

Server::~Server()
{
    for (auto &client : clients)
    {
        client.join();
    }
}