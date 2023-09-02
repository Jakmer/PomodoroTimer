#include <iostream>
#include "Client.h"
#include "EChoice.h"
#include <cstring>

int main()
{
    try
    {
        Choice choice;

        Client client{};
        client.connect_to_server();

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
            std::cout << "4. Get time\n";
            std::cout << "6. Quit\n";

            std::cout << "Enter (1-5) : ";
            std::cin >> choice;

            system("clear");

            switch (choice)
            {
            case Unknown:
                std::cout << "Cannot identify your choice...\n";
                break;
            case Start:
            case Stop:
            case Skip:
            case Restart:
            case Get_time:
                client.send_to_server(choice);
                client.receive_from_server();
                break;

            case Quit:
                client.send_to_server(choice);
                return 0;

            default:
                break;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << strerror(errno) << '\n';
    }

    return 0;
}