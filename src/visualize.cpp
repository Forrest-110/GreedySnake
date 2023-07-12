#include "visualize.hpp"
#include <cstdlib>
sf::RenderWindow window;
void SNAKE::VisualizeThread::run()
{
    static bool first = true;
    while (this->running)
    {
        
        if (first)
        {
            this->game->map->initui();
            this->game->map->showMap(
                this->snake1->getHeadPoint(), 
                this->snake2->getHeadPoint(), 
                this->snake1->getDirection(), 
                this->snake2->getDirection()
            );
            first = false;
        }
        this->game->map->update();
        // std::system("clear");
        for (auto player : this->game->players)
        {
            
            std::cout << "Score: " << player->snake->getScore() << std::endl;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                this->running = false;
            }
        }
        this->game->map->showMap(
            this->snake1->getHeadPoint(), 
            this->snake2->getHeadPoint(), 
            this->snake1->getDirection(), 
            this->snake2->getDirection()
        );
        std::this_thread::sleep_for(std::chrono::milliseconds(this->interval));
    }
}