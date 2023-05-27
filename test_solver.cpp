#include "map.hpp"
#include "visualize.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "object.hpp"
#include "game.hpp"
#include <conio.h>
using namespace SNAKE;
using namespace SOLVER;
using namespace std;
int main()
{
	
	GridMap map(10,0.1);

    
    Food food(&map);
    Object object(&map);
    
    

    Snake snake(&map,&food,5,5,Direction::UP,1);

    PathSolver path_solver(&snake);
	GreedySolver greedy_solver(&snake,&path_solver);
    
	Ai ai(&snake,&greedy_solver);
    Human human(&snake);
    GameManager game(&map,&food,&object,{&ai});
    VisualizeThread vis(&game,100);
    
    vis.start();
    
    game.start();
    
    // while (1);
    game.run();
    vis.stop();
}