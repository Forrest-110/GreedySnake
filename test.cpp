#include "map.hpp"
#include "visualize.hpp"
#include "food.hpp"
#include "snake.hpp"
#include <conio.h>
using namespace SNAKE;
int main(){
    GridMap map(10,0.1);
    VisualizeThread vis(&map,100);
    map.init();
    Food food(&map);
    food.generateNFoodRandomly(5);
    Snake snake(&map,&food,5,5,Direction::UP,1);
    vis.start();
    while (true)
    {
        if (_kbhit())
        {
            char c = _getch();
            switch (c)
            {
            case 'w':
                snake.changeDirection(Direction::UP);
                break;
            case 's':
                snake.changeDirection(Direction::DOWN);
                break;
            case 'a':
                snake.changeDirection(Direction::LEFT);
                break;
            case 'd':
                snake.changeDirection(Direction::RIGHT);
                break;
            default:
                break;
            }
        }
        snake.move();
        if (snake.isDead)
        {
            vis.stop();
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
}