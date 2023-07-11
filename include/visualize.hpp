#pragma once
#ifndef _VISUALIZE_HPP_
#define _VISUALIZE_HPP_

#include "game.hpp"
#include <thread>
#include <chrono>

namespace SNAKE{
class VisualizeThread{
    private:
        GameManager *game;
        int interval;
        bool running;
        std::thread* thread;
        SNAKE::Snake *snake1;
        SNAKE::Snake *snake2;
    public:
        VisualizeThread(GameManager* _game,int _interval=100){
            this->game = _game;
            this->interval = _interval;
            this->running = false;
            this->thread=nullptr;
        }
        VisualizeThread(GameManager* _game,SNAKE::Snake *_snake,int _interval=100){
            this->game = _game;
            this->interval = _interval;
            this->running = false;
            this->thread=nullptr;
            this->snake1=_snake;
        }
        VisualizeThread(GameManager* _game,SNAKE::Snake *_snake1,SNAKE::Snake *_snake2,int _interval=100){
            this->game = _game;
            this->interval = _interval;
            this->running = false;
            this->thread=nullptr;
            this->snake1=_snake1;
            this->snake2=_snake2;
        }
        void start(){
            
            this->running = true;
            this->thread =new std::thread(&VisualizeThread::run,this);
            this->thread->detach();
        }
        void stop(){
            
            this->running = false;
            if (this->game->isOver){
                this->game->map->update();
                // std::system("clear");
                for (auto player : this->game->players)
                {
                    std::cout << "Score: " << player->snake->getScore() << std::endl;
                }
                this->game->map->showMap(
                    this->snake1->getHeadPoint(), 
                    this->snake2->getHeadPoint(), 
                    this->snake1->getDirection(), 
                    this->snake2->getDirection()
                );
            }
        }
        void run();
    
};
}

#endif