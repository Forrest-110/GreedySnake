#include "client.hpp"
using namespace SNAKE;
void NETWORK::Client::StartClient()
{
    if ((*socket).connect("127.0.0.1", 5000) != sf::Socket::Done)
    {
        std::cout << "Failed to connect to server." << std::endl;
    }

    std::cout << "Connected to server!" << std::endl;
}

void NETWORK::Client::SentAndReceive()
{
    // 检查是否需要接收服务器端传来的Snake1的信息
    sf::Packet receivePacket;
    if ((*socket).receive(receivePacket) == sf::Socket::Done)
    {
        std::string receivedData;
        receivePacket >> receivedData;

        // 解析接收到的Snake1信息并更新客户端的Snake1对象
        // 这里假设Snake信息是字符串形式，每个属性之间用逗号分隔
        // 根据实际情况修改解析的方式
        (*snake1).update(receivedData);
    }

    // 将客户端的Snake2信息发送给服务器端
    sf::Packet sendPacket;
    sendPacket << (*snake2).toString(); // 将Snake2信息打包为Packet
    (*socket).send(sendPacket); // 发送Packet给服务器端
}

void NETWORK::Client::Run()
{
    while (true)
    {
        SentAndReceive();
    }
}