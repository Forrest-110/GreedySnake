#include "map.hpp"
#include "visualize.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "object.hpp"
#include "game.hpp"
#include <conio.h>
using namespace SNAKE;
using namespace SOLVER;
int main(){
    
    GridMap map(10,0.1);
    Food food(&map);
    Object object(&map);

    std::cout<<"Welcome to Snake Game"<<std::endl;
    std::cout<<"Choose Game Mode"<<std::endl;
    std::cout<<"Single Player: 1"<<std::endl;
    std::cout<<"Multi Player: 2"<<std::endl;
    std::cout<<"AI: 3"<<std::endl;
    int mode;
    std::cin>>mode;

    if (mode==1){
        Snake snake(&map,&food,5,5,Direction::UP,1);
        Human human(&snake);
        GameManager game(&map,&food,&object,{&human});
        VisualizeThread vis(&game,100);
        vis.start();
        game.start();
        game.run();
        vis.stop();
    }else if (mode==3){
        Snake snake(&map,&food,5,5,Direction::UP,1);
        PathSolver path_solver(&snake);
	    GreedySolver greedy_solver(&snake,&path_solver);
    
	    Ai ai(&snake,&greedy_solver);
        
        GameManager game(&map,&food,&object,{&ai});
        VisualizeThread vis(&game,100);
        
    
        vis.start();
    
        game.start();
    
        // while (1);
        game.run();
        vis.stop();
    }else{
        Snake snake1(&map,&food,3,3,Direction::RIGHT,1);
        Snake snake2(&map,&food,6,6,Direction::LEFT,1);
        Human human1(&snake1,'w','s','a','d');
        Human human2(&snake2,'i','k','j','l');
        GameManager game(&map,&food,&object,{&human1,&human2});
        VisualizeThread vis(&game,100);
        vis.start();
        game.start();
        game.run();
        game.stop();
        vis.stop();
        
    }

    
    
}
