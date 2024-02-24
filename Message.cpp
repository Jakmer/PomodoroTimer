#include "Message.hpp"

int Message::colorAnalyzer(char *color)
{
    return 0; // int equivalent of ansi color
}

void Message::deserialize(char *serialized_msg)
{
    if (false)
    {
        throw std::runtime_error("Invalid message");
    }
}

Message::Message(char *serialized_msg)
{
    deserialize(serialized_msg);
}

Message::Message(char *command, char *color) : command(command)
{
    this->color = colorAnalyzer(color);
}

Message::Message(Message &msg) : command(msg.getCommand()), color(msg.getColor())
{
}

std::string Message::getCommand()
{
    return command;
}

int Message::getColor()
{
    return color;
}

char *Message::serialize()
{
    // cant be bigger than 1024 chars
    char *buffer;

    return buffer;
}