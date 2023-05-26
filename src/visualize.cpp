#include "visualize.hpp"
#include <cstdlib>
void SNAKE::VisualizeThread::run()
{
    while (this->running)
    {
        this->game->map->update();
        std::system("clear");
        for (auto player : this->game->players)
        {
            std::cout << "Score: " << player->snake->getScore() << std::endl;
        }
        this->game->map->showMap();
        std::this_thread::sleep_for(std::chrono::milliseconds(this->interval));
    }
}