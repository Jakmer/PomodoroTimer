#include "Client.h"

Client::Client()
{
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1)
    {
        throw std::runtime_error("Error creating socket: ");
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
}

void Client::connect_to_server()
{
    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        throw std::runtime_error("Error connecting to server: ");
    }
}

std::string Client::receive_from_server()
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
    if (buffer[0] == Quit)
    {
        delete this;
    }

    return static_cast<std::string>(buffer);
}

void Client::send_to_server(Choice &choice)
{
    if (send(client_fd, &choice, sizeof(choice), 0) == -1)
    {
        throw std::runtime_error("Error sending to server: ");
    }
}

void Client::run()
{

    connect_to_server();

    std::cout << "-------------------------------------------\n";
    std::cout << "---------WELCOME TO POMODORO TIMER----------\n";
    std::cout << "-------------------------------------------\n";

    while (true)
    {
        std::cout << "=====MENU=====\n";
        std::cout << "1. Start\n";
        std::cout << "2. Stop\n";
        std::cout << "3. Skip\n";
        std::cout << "4. Restart\n";
        std::cout << "5. Get time\n";
        std::cout << "6. Quit\n";

        std::cout << "Enter (1-6) : ";
        std::cin >> choice;

        system("clear");

        switch (choice)
        {
        case Unknown:
            std::cerr << "Cannot identify your choice...\n";
            break;
        case Start:
        case Stop:
        case Skip:
        case Restart:
        case Get_time:
            send_to_server(choice);

            std::cout << choice << ": " << receive_from_server() << '\n';

            if (errno == EAGAIN)
                continue;
            break;

        case Quit:
            send_to_server(choice);
            return;

        default:
            break;
        }
    }
}

Client::~Client()
{
    close(client_fd);
}