#include "game.hpp"
#include <conio.h>
#include <thread>
#include <chrono>
SNAKE::Direction SNAKE::Human::getNextDirection(){
    Direction nextdirection=snake->getDirection();
    if (_kbhit())
        {
            char c = getch();
            
            if (c==up){
                nextdirection=snake->changeDirection(Direction::UP);
            }else if (c==down){
                nextdirection=snake->changeDirection(Direction::DOWN);
            }else if (c==left){
                nextdirection=snake->changeDirection(Direction::LEFT);
            }else if (c==right){
                nextdirection=snake->changeDirection(Direction::RIGHT);
            }
            

            // switch (c)
            // {
            // case up:
            //     nextdirection=snake->changeDirection(Direction::UP);
            //     break;
            // case down:
            //     nextdirection=snake->changeDirection(Direction::DOWN);
            //     break;
            // case left:
            //     nextdirection=snake->changeDirection(Direction::LEFT);
            //     break;
            // case right:
            //     nextdirection=snake->changeDirection(Direction::RIGHT);
            //     break;
            // default:
            //     break;
            // }
        }
    return nextdirection;
}

SNAKE::Direction SNAKE::Ai::getNextDirection(){
    if (solver!=nullptr){
        return solver->next_Direction();
    }

    return SNAKE::Direction::UP;
}

void SNAKE::GameManager::start(int food_num,int object_num){
    this->isOver=false;
    this->map->init();
    this->food->generateNFoodRandomly(food_num);
    this->object->generateNObjectRandomly(object_num);
}



void SNAKE::GameManager::thread_run(SNAKE::BasePlayer* player){
    while (true)
    {
        
        SNAKE::Direction nextdirection=player->getNextDirection();
        bool eaten_food=player->snake->move(nextdirection);
        if (eaten_food){
            
            player->reset_goal();
        }
        if (player->snake->_isDead){
            std::cout<<"Player  is dead"<<std::endl;
            goto OVER;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    OVER:
        std::cout<<"Game Over"<<std::endl;
        end();
        
}

void SNAKE::GameManager::run(){
    if (players.size()==1){
    while (true)
    {
        for (auto player:players){
        SNAKE::Direction nextdirection=player->getNextDirection();
        
        bool eaten_food=player->snake->move(nextdirection);
        if (eaten_food){
            
            player->reset_goal();
        }
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
    }else{
        for (int i=0;i<players.size();i++){
            threads[i]=new std::thread(&GameManager::thread_run,this,players[i]);
            threads[i]->detach();
        }
    }
}

void SNAKE::GameManager::end(){
    this->isOver=true;
}

