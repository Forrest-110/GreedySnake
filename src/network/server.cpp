#include "server.hpp"
using namespace SNAKE;



void NETWORK::Server::StartServer()
{
    sf::TcpListener listener;
    sf::TcpSocket client;

    if (listener.listen(5000) != sf::Socket::Done)
    {
        std::cout << "Failed to bind socket to port 5000." << std::endl;
    }

    std::cout << "Server is running and listening on port 5000." << std::endl;

    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cout << "Failed to accept client connection." << std::endl;
    }

    std::cout << "Client connected!" << std::endl;
}

void NETWORK::Server::SentAndReceive(){
        // 将服务器端的Snake1信息发送给客户端
        sf::Packet sendPacket;
        sendPacket << (*snake1).toString(); // 将Snake1信息打包为Packet
        (*client).send(sendPacket); // 发送Packet给客户端

        // 检查是否需要接收客户端传来的Snake2的信息
        sf::Packet receivePacket;
        if ((*client).receive(receivePacket) == sf::Socket::Done) {
            std::string receivedData;
            receivePacket >> receivedData;

            // 解析接收到的Snake2信息并更新服务器端的Snake2对象
            // 这里假设Snake信息是字符串形式，每个属性之间用逗号分隔
            // 根据实际情况修改解析的方式
            //std::vector<std::string> data = parseSnakeData(receivedData);
            (*snake2).update(receivedData);
        }
}

void NETWORK::Server::Run()
{
    while (true)
    {
        SentAndReceive();
    }
}