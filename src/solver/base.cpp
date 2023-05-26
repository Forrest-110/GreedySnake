#include "base.hpp"

SNAKE::Direction SOLVER::Pos::direction_to(SOLVER::Pos &adjacent_pos){
    if(adjacent_pos.x==x){
        if(adjacent_pos.y==y+1){
            return SNAKE::Direction::DOWN;
        }else if(adjacent_pos.y==y-1){
            return SNAKE::Direction::UP;
        }
    }else if(adjacent_pos.y==y){
        if(adjacent_pos.x==x+1){
            return SNAKE::Direction::RIGHT;
        }else if(adjacent_pos.x==x-1){
            return SNAKE::Direction::LEFT;
        }
    }
    return SNAKE::Direction::NONE;
}

SOLVER::Pos SOLVER::Pos::adjacent(SNAKE::Direction d){
    if (d==SNAKE::Direction::UP){
        return Pos(x,y-1);
    }else if (d==SNAKE::Direction::DOWN){
        return Pos(x,y+1);
    }else if (d==SNAKE::Direction::LEFT){
        return Pos(x-1,y);
    }else if (d==SNAKE::Direction::RIGHT){
        return Pos(x+1,y);
    }else{
        std::cerr<<"Error: Invalid direction"<<std::endl;
        exit(0);
    }
}

std::vector<SOLVER::Pos> SOLVER::Pos::all_adjacents(){
    std::vector<SOLVER::Pos> adjacents;
    adjacents.push_back(Pos(x,y-1));
    adjacents.push_back(Pos(x,y+1));
    adjacents.push_back(Pos(x-1,y));
    adjacents.push_back(Pos(x+1,y));
    return adjacents;
}

