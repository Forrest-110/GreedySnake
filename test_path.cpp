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

#include <assert.h>

void test_shortest(){
    GridMap map(7,0.1);
    map.init();
    
    Food food(&map);
    Object object(&map);
    
    food.generateFoodAtXY(5,5);
    
    Snake snake(&map,&food,Direction::RIGHT,1,{{3,2},{2,2},{1,2}});

    PathSolver path_solver(&snake);

    map.update();
    
    auto act_path=path_solver.shortest_path_to_food();
    act_path=path_solver.shortest_path_to_food();
    auto exp_path=vector<Direction>{Direction::RIGHT,Direction::RIGHT,Direction::DOWN,Direction::DOWN,Direction::DOWN};
    assert(act_path.size()==exp_path.size());
    for (int i=0;i<act_path.size();i++){
        assert(act_path[i]==exp_path[i]);
    }
    assert(path_solver.getTable()[1][5].dist==5);
    assert(path_solver.getTable()[1][5].dist=path_solver.getTable()[5][5].dist);
    assert(path_solver.shortest_path_to(snake.getTail()).empty());
    
    // Ai ai(&snake,&greedy_solver);
    // Human human(&snake);
    // GameManager game(&map,&food,&object,{&ai});
    // VisualizeThread vis(&game,100);
    
    // vis.start();
    
    // game.start();
    
    // // while (1);
    // game.run();
    // vis.stop();
}


void test_longest(){
    GridMap map(6,0.1);
    map.init();
    
    Food food(&map);
    Object object(&map);
    
    food.generateFoodAtXY(4,4);
    
    Snake snake(&map,&food,Direction::RIGHT,1,{{3,1},{2,1},{1,1}});

    PathSolver path_solver(&snake);

    map.update();
    auto act_path=path_solver.longest_path_to_tail();
    act_path=path_solver.longest_path_to_tail();
    auto exp_path=vector<Direction>{Direction::RIGHT,
    Direction::DOWN,
    Direction::DOWN,
    Direction::DOWN,
    Direction::LEFT,
    Direction::LEFT,
    Direction::LEFT,
    Direction::UP,
    Direction::RIGHT,
    Direction::RIGHT,
    Direction::UP,
    Direction::LEFT,
    Direction::LEFT,
    Direction::UP
    };
    std::cout<<act_path.size()<<std::endl;
    assert(map.getCell(snake.getTail().x,snake.getTail().y)==CellType::OCCUPIED);
    assert(act_path.size()==exp_path.size());
    for (int i=0;i<act_path.size();i++){
        assert(act_path[i]==exp_path[i]);
    }
    assert(path_solver.longest_path_to(snake.getTail()).empty());
}


int main(){
    test_shortest();
    test_longest();
    return 0;
}