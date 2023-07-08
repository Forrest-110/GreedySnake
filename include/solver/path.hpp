#ifndef _PATH_HPP_
#define _PATH_HPP_

#include "base.hpp"
#include <deque>
#include <climits>
namespace SOLVER{

class _TableCell{
    public:
    Pos parent;
    int dist;
    bool visit;
    public:
    void reset(){
        parent=Pos();
        dist=INT_MAX;
        visit=false;
    }
    _TableCell():parent(Pos()),dist(INT_MAX),visit(false){};
    friend std::ostream& operator<<(std::ostream& os, const _TableCell& cell){
        os<<"("<<cell.parent.x<<","<<cell.parent.y<<","<<cell.dist<<","<<cell.visit<<")";
        return os;
    }
};

class PathSolver:public BaseSolver{
    public:
    std::vector<std::vector<_TableCell>> table;
    public:
    PathSolver():BaseSolver(nullptr){};
    PathSolver(SNAKE::Snake *snake):BaseSolver(snake){
        SNAKE::GridMap *map=getMap();
        
        if(!map){
            
            throw std::runtime_error("map is nullptr");
        }
        
        
        
        table.resize(map->getSize());
        for(int i=0;i<map->getSize();i++){
            table[i].resize(map->getSize());
            for(int j=0;j<map->getSize();j++){
                
                table[i][j].reset();
            }
        }
        
        
    }

    std::vector<std::vector<_TableCell>> getTable(){
        return table;
    }



    std::deque<SNAKE::Direction> shortest_path_to(Pos des);
    std::deque<SNAKE::Direction> longest_path_to(Pos des);
    std::deque<SNAKE::Direction> longest_path_to_tail();
    std::deque<SNAKE::Direction> shortest_path_to_food(Pos *foodpoint=nullptr);
    std::deque<SNAKE::Direction> path_to(Pos des, bool longest=false);


    void reset_table(){
        for(int i=0;i<table.size();i++){
            for(int j=0;j<table.size();j++){
                table[i][j].reset();
            }
        }
    }
    std::deque<SNAKE::Direction> build_path(Pos src,Pos des){
        std::deque<SNAKE::Direction> path;
        Pos tmp=des;
        while (tmp!=src){
            Pos parent=table[tmp.x][tmp.y].parent;
            path.push_front(parent.direction_to(tmp));
            tmp=parent;
        }
        return path;
    }

    bool is_valid(Pos src){
        return (getMap()->is_valid(src.x,src.y))&&(!(table[src.x][src.y].visit));
    }

    SNAKE::Direction next_Direction(){
        return SNAKE::Direction::NONE;
    }
    void reset_goal(){
        ;
    }





    };

};





#endif