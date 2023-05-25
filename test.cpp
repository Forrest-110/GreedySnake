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
    food.generateNFoodRandomly(2);
    Snake snake(&map,&food,5,5,Direction::UP,1);
    vis.start();
    // while (true){
    //     char c=getch();
    //     switch (c){
    //         case 'w':
    //             snake.move(Direction::UP);
    //             break;
    //         case 's':
    //             snake.move(Direction::DOWN);
    //             break;
    //         case 'a':
    //             snake.move(Direction::LEFT);
    //             break;
    //         case 'd':
    //             snake.move(Direction::RIGHT);
    //             break;
    //         default:
    //             break;
    //     }
    //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    while (true)
    {
        Direction nextdirection=snake.getDirection();
        if (_kbhit())
        {
            char c = getch();
            
            switch (c)
            {
            case 'w':
                nextdirection=snake.changeDirection(Direction::UP);
                break;
            case 's':
                nextdirection=snake.changeDirection(Direction::DOWN);
                break;
            case 'a':
                nextdirection=snake.changeDirection(Direction::LEFT);
                break;
            case 'd':
                nextdirection=snake.changeDirection(Direction::RIGHT);
                break;
            default:
                break;
            }
        }
        snake.move(nextdirection);
        if (snake.isDead)
        {
            vis.stop();
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
}