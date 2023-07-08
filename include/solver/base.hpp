#ifndef _BASE_HPP_
#define _BASE_HPP_
#include "map.hpp"
#include "snake.hpp"
#include "food.hpp"
#include <iostream>
namespace SOLVER{

    class Pos: public SNAKE::Point{
        public:
        Pos():SNAKE::Point(){};
        Pos(int x, int y, SNAKE::CellType type):SNAKE::Point(x,y,type){};
        Pos(int x,int y):SNAKE::Point(x,y){};
        Pos(SNAKE::Point p):SNAKE::Point(p){};
        bool operator==(const Pos& p) const{
            return (x==p.x && y==p.y);
        }
        bool operator!=(const Pos& p) const{
            return (x!=p.x || y!=p.y);
        }
        bool operator<(const Pos& p) const{
            return std::tie(x, y) < std::tie(p.x, p.y);
        }
        bool operator>(const Pos& p) const{
            return std::tie(x, y) > std::tie(p.x, p.y);
        }
        Pos operator+(const Pos& p) const{
            return Pos(x+p.x,y+p.y);
        }
        Pos operator-(const Pos& p) const{
            return Pos(x-p.x,y-p.y);
        }
        Pos operator-() const{
            return Pos(-x,-y);
        }
        int manhattan(const Pos& p) const{
            return abs(x-p.x)+abs(y-p.y);
        }
        SNAKE::Direction direction_to(Pos &adjacent_pos);
        Pos adjacent(SNAKE::Direction d);
        std::vector<Pos> all_adjacents();


    };
    class PosHash{
        public:
        std::size_t operator()(const Pos& p) const{
            return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
        }
    };


    class BaseSolver{
        public:
        // SNAKE::GridMap* map;
        SNAKE::Snake *snake;
        // SNAKE::Food *food;
        public:
        BaseSolver(SNAKE::Snake* snake):snake(snake){};
        // ~BaseSolver(){
        //     delete map;
        //     delete food;
        //     delete snake;
        // };
        SNAKE::Food* getFood(){return snake->food;};
        SNAKE::Snake* getSnake(){return snake;};
        SNAKE::GridMap* getMap(){return snake->map;};
        virtual SNAKE::Direction next_Direction()=0;
        virtual void reset_goal()=0;
    };


}

#endif