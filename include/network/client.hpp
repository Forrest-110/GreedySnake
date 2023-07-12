#pragma once

#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <SFML/Network.hpp>
#include <iostream>
#include "map.hpp"
#include "visualize.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "object.hpp"
#include "game.hpp"

namespace NETWORK {
    class Client {
    private:
        SNAKE::Snake* snake1; // 使用引用类型的成员变量，以便与游戏线程和可视化线程共享同一个 Snake 对象
        SNAKE::Snake* snake2; // 使用引用类型的成员变量，以便与游戏线程和可视化线程共享同一个 Snake 对象
        sf::TcpSocket* socket; // 使用引用类型的成员变量，以便与服务端共享同一个套接字对象

    public:
        Client(SNAKE::Snake* _snake1, SNAKE::Snake* _snake2, sf::TcpSocket* _socket)
        : snake1(_snake1), snake2(_snake2), socket(_socket) {};

        void StartClient();
        void SentAndReceive();
        void Run();

        ~Client();
    };

    Client::~Client() {}

} // namespace NETWORK

#endif
