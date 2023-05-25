#ifndef _VISUALIZE_HPP_
#define _VISUALIZE_HPP_

#include "map.hpp"
#include <thread>
#include <chrono>

namespace SNAKE{
class VisualizeThread{
    private:
        GridMap* map;
        int interval;
        bool running;
        std::thread* thread;
    public:
        VisualizeThread(GridMap* _map,int _interval=100){
            this->map = _map;
            this->interval = _interval;
            this->running = false;
        }
        void start(){
            this->running = true;
            this->thread = new std::thread(&VisualizeThread::run,this);
            this->thread->detach();
        }
        void stop(){
            this->running = false;
            
        }
        void run();
    
};
}

#endif