#include "server.hpp"

int StartServer()
{
    sf::TcpListener listener;
    sf::TcpSocket client;

    if (listener.listen(5000) != sf::Socket::Done)
    {
        std::cout << "Failed to bind socket to port 5000." << std::endl;
        return -1;
    }

    std::cout << "Server is running and listening on port 5000." << std::endl;

    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cout << "Failed to accept client connection." << std::endl;
        return -1;
    }

    std::cout << "Client connected!" << std::endl;

    char buffer[1024];
    std::size_t received;

    if (client.receive(buffer, sizeof(buffer), received) != sf::Socket::Done)
    {
        std::cout << "Failed to receive message." << std::endl;
        return -1;
    }

    std::cout << "Received message from client: " << buffer << std::endl;

    std::string message = "Hello, client!";
    if (client.send(message.c_str(), message.length() + 1) != sf::Socket::Done)
    {
        std::cout << "Failed to send message." << std::endl;
        return -1;
    }

    std::cout << "Message sent to client: " << message << std::endl;

    client.disconnect();
    listener.close();

    return 0;
}