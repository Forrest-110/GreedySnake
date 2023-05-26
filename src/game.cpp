#include "game.hpp"
#include <conio.h>
#include <thread>
#include <chrono>
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
    //TODO: implement this function
    return SNAKE::Direction::NONE;
}

void SNAKE::GameManager::start(){
    this->isOver=false;
    this->map->init();
    this->food->generateNFoodRandomly(2);
    this->object->generateNObjectRandomly(2);
}

void SNAKE::GameManager::run(){
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

void SNAKE::GameManager::end(){
    this->isOver=true;
}