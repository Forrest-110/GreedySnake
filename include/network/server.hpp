#pragma once

#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <SFML/Network.hpp>
#include <iostream>
#include "map.hpp"
#include "visualize.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "object.hpp"
#include "game.hpp"

namespace NETWORK {
    class Server {
    private:
        SNAKE::Snake* snake1;
        SNAKE::Snake* snake2;
        sf::TcpListener* listener;
        sf::TcpSocket* client;

    public:
        Server(SNAKE::Snake* _snake1, SNAKE::Snake* _snake2)
        : snake1(_snake1), snake2(_snake2), listener(nullptr), client(nullptr) {}

        void StartServer();
        void SentAndReceive();
        void Run();

        ~Server();
    };

    Server::~Server() {}

} // namespace NETWORK

#endif
