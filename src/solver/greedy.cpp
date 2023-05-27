#include "greedy.hpp"

SNAKE::Direction SOLVER::GreedySolver::next_Direction(){
    //copy a snake
    
    SNAKE::Snake* snake_copy=getSnake()->getCopy();
    SNAKE::GridMap* map_copy=snake_copy->map;
    // //copy a map
    // SNAKE::GridMap* map_copy=new SNAKE::GridMap(*getMap());
    // SNAKE::Food* food_copy=new SNAKE::Food(*getFood());
    // snake_copy->setMap(map_copy);
    // food_copy->setMap(map_copy);
    // snake_copy->setFood(food_copy);
    // snake_copy->setFoodMap(map_copy);

    _path_solver->snake=this->snake;
    
    
    auto path_to_food=_path_solver->shortest_path_to_food();

    if (!path_to_food.empty()){
        snake_copy->move_along_path(path_to_food);
        if (map_copy->isfull()){
            return path_to_food[0];
        }
        _path_solver->snake=snake_copy;
        
        auto path_to_tail=_path_solver->longest_path_to_tail();
        if (path_to_tail.size()>1){
            return path_to_food[0];
        }
    }
    _path_solver->snake=this->snake;
    
    auto path_to_tail=_path_solver->longest_path_to_tail();
    if (path_to_tail.size()>1){
        return path_to_tail[0];
    }

    SOLVER::Pos head=this->snake->getHeadPoint();
    auto direc=this->snake->getDirection();
    int max_dist=-1;
    for (auto adj: head.all_adjacents()){
        if (this->getMap()->is_valid(adj.x,adj.y)){
            for (auto food: this->getFood()->food_set){
                int dist=adj.manhattan(food);
                if (dist>max_dist){
                    max_dist=dist;
                    direc=head.direction_to(adj);
                }
            }
        }
    }
    // free(snake_copy);
    return direc;
    
}