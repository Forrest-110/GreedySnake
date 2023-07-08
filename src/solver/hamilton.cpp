#include "hamilton.hpp"

void SOLVER::HamiltonSolver::build_cycle(){
    //build a hamiltonian cycle on the map
    auto path=_path_solver->longest_path_to_tail();
    auto curr=this->snake->getHeadPoint();
    
    int count=0;
    for (auto &dir:path){
        _table[curr.x][curr.y].idx=count;
        _table[curr.x][curr.y].direc=dir;
        curr=SOLVER::Pos(curr).adjacent(dir);
        count++;
    }
    curr=this->snake->getTail();
    for (int i=0;i<this->snake->getLength()-1;i++){
        _table[curr.x][curr.y].idx=count;
        _table[curr.x][curr.y].direc=this->snake->getDirection();
        curr=SOLVER::Pos(curr).adjacent(this->snake->getDirection());
        count++;

    }
    
}

SNAKE::Direction SOLVER::HamiltonSolver::next_Direction(){
    auto head=this->snake->getHeadPoint();
    
    auto next_dir=_table[head.x][head.y].direc;
    int capacity=this-> getMap()->capacity();
    if (_shortcuts && this->snake->getLength()<capacity/2){
        SOLVER::Pos *food=new SOLVER::Pos();
        auto path=_path_solver->shortest_path_to_food(food);
        if (!path.empty()){
            auto tail=this->snake->getTail();
            auto next=SOLVER::Pos(head).adjacent(path[0]);
            auto tail_idx=_table[tail.x][tail.y].idx;
            auto head_idx=_table[head.x][head.y].idx;
            auto next_idx=_table[next.x][next.y].idx;
            auto food_idx=_table[food->x][food->y].idx;
            if (!(path.size()==1&& abs(food_idx-tail_idx)==1)){
                auto head_idx_rel=relative_distance(tail_idx,head_idx,capacity);
                auto next_idx_rel=relative_distance(tail_idx,next_idx,capacity);
                auto food_idx_rel=relative_distance(tail_idx,food_idx,capacity);
                if (next_idx_rel>head_idx_rel&&next_idx_rel<food_idx_rel){
                    next_dir=path[0];
                }
            }
        }
    }
    return next_dir;
}