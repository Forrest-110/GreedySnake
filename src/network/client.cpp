#include "client.hpp"

int StratClient()
{
    sf::TcpSocket socket;

    if (socket.connect("127.0.0.1", 5000) != sf::Socket::Done)
    {
        std::cout << "Failed to connect to server." << std::endl;
        return -1;
    }

    std::cout << "Connected to server!" << std::endl;

    std::string message = "Hello, server!";
    if (socket.send(message.c_str(), message.length() + 1) != sf::Socket::Done)
    {
        std::cout << "Failed to send message." << std::endl;
        return -1;
    }

    std::cout << "Message sent to server: " << message << std::endl;

    char buffer[1024];
    std::size_t received;

    if (socket.receive(buffer, sizeof(buffer), received) != sf::Socket::Done)
    {
        std::cout << "Failed to receive message." << std::endl;
        return -1;
    }

    std::cout << "Received message from server: " << buffer << std::endl;

    socket.disconnect();

    return 0;
}