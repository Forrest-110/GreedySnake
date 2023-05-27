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
    public:
        VisualizeThread(GameManager* _game,int _interval=100){
            this->game = _game;
            this->interval = _interval;
            this->running = false;
            this->thread=nullptr;
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
                this->game->map->showMap();
            }
        }
        void run();
    
};
}

#endif