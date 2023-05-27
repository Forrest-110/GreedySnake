#include "game.hpp"
#include <conio.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
SNAKE::Direction SNAKE::Human::getNextDirection(){
    Direction nextdirection=snake->getDirection();
    if (_kbhit())
        {
            char c = getch();
            
            switch (c)
            {
            case 'w':
                nextdirection=snake->changeDirection(Direction::UP);
                break;
            case 's':
                nextdirection=snake->changeDirection(Direction::DOWN);
                break;
            case 'a':
                nextdirection=snake->changeDirection(Direction::LEFT);
                break;
            case 'd':
                nextdirection=snake->changeDirection(Direction::RIGHT);
                break;
            default:
                break;
            }
        }
    return nextdirection;
}

SNAKE::Direction SNAKE::Ai::getNextDirection(){
    if (greedy_solver!=nullptr){
        return greedy_solver->next_Direction();
    }

    return SNAKE::Direction::UP;
}

void SNAKE::GameManager::start(){
    this->isOver=false;
    this->map->init();
    this->food->generateNFoodRandomly(2);
    this->object->generateNObjectRandomly(2);
    std::cout<<"Enter Game Mode: "<<std::endl;
    std::cout<<"1. Single Player"<<std::endl;
    std::cout<<"2. Multi Player"<<std::endl;
    int _mode;
    std::cin>>_mode;
    if (_mode==1){
        this->numPlayers=1;
        this->mode=GameMode::SinglePlayer;
    }
    else if (_mode==2){
        this->numPlayers=2;
        this->mode=GameMode::MultiPlayer;
    }
    else{
        std::cout<<"Invalid Input"<<std::endl;
        return;
    }
    if (this->mode==GameMode::MultiPlayer){
        std::cout<<"Enter IP Address of Server: "<<std::endl;
        std::string ip;
        std::cin>>ip;
        std::cout<<"Enter Port Number of Server: "<<std::endl;
        int port;
        std::cin>>port;
        this->server.initServerSocket(ip,port);
        this->server.acceptConnection(this->map.getSize(),this->map.getGridSize());
    }
}

void SNAKE::GameManager::run_single_player(){
    while (true)
    {
        for (auto player:players){
        SNAKE::Direction nextdirection=player->getNextDirection();
        player->snake->move(nextdirection);
        if (player->snake->_isDead){
            std::cout<<"Player  is dead"<<std::endl;
            goto OVER;
            break;
        }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    OVER:
        std::cout<<"Game Over"<<std::endl;
        end();
}

void SNAKE::GameManager::run_multi_player(){
    ;
}

void SNAKE::GameManager::run(){
    if (this->mode==GameMode::SinglePlayer){
        run_single_player();
    }
    else if (this->mode==GameMode::MultiPlayer){
        run_multi_player();
    }
}

void SNAKE::GameManager::end(){
    this->isOver=true;
    if (this->mode==GameMode::MultiPlayer){
        this->server.closeSocket();
    }
}


SNAKE::ClientManager(){
    std::cout<<"Enter IP Address of Server: "<<std::endl;
    std::string ip;
    std::cin>>ip;
    std::cout<<"Enter Port Number of Server: "<<std::endl;
    int port;
    std::cin>>port;

    this->client.initClientSocket(ip,port);
    this->client.connectToServer();
    this->client.readMessage();
    this->map=this->client.parseMapData(this->client.read_buffer);
    this->food=SNAKE::Food(&this->map);
    this->food.setFoodSetFromMap();
    this->object=SNAKE::Object(&this->map);
    this->object.setObjectSetFromMap();

    std::cout<<"Enter Player Name: "<<std::endl;
    std::cin>>name;
    
    mainSnake=SNAKE::Snake(&this->map,&this->food,3,3,SNAKE::Direction::RIGHT,1);
    anotherSnake=SNAKE::Snake(&this->map,&this->food,7,7,SNAKE::Direction::LEFT,1);

    mainPlayer=SNAKE::Player(&mainSnake);
    anotherPlayer=SNAKE::Player(&anotherSnake);

    this->isOver=false;
    
}

void SNAKE::ClientManager::handleMessageFromServer(std::string message){
    SOCKET::SnakeData data=this->client.parseSnakeData(message);
    if (data.name==this->name){
        ;
    }
    else{
        SNAKE::Direction nextdirection=data.dir;
        anotherPlayer.snake->move(nextdirection);
        if (anotherPlayer.snake->_isDead){
            std::cout<<"Player  is dead"<<std::endl;
            this->isOver=true;
        }
    }
}

void SNAKE::ClientManager::start(){
    this->isOver=false;
}

void SNAKE::ClientManager::run(){
    while (true)
    {
        SNAKE::Direction nextdirection=this->mainPlayer.getNextDirection();
        mainPlayer.snake->move(nextdirection);
        if (mainPlayer.snake->_isDead){
            std::cout<<"Player  is dead"<<std::endl;
            goto OVER;
            break;
        }
        SOCKET::SnakeData data(this->name,mainPlayer.snake.score,mainPlayer.snake.getHeadPoint().x,mainPlayer.snake.getHeadPoint().y,mainPlayer.snake.getDirection());
        this->client.sendMessage(data.toString());
        this->client.readMessage();
        handleMessageFromServer(this->client.read_buffer);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    OVER:
        std::cout<<"Game Over"<<std::endl;
        end();
}