#include "visualize.hpp"

void SNAKE::VisualizeThread::run()
{
    while (this->running)
    {
        this->map->showMap();
        std::this_thread::sleep_for(std::chrono::milliseconds(this->interval));
    }
}