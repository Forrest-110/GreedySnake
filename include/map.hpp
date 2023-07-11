#pragma once
#ifndef _MAP_HPP_
#define _MAP_HPP_

//#include "snake.hpp"
#include <vector>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
namespace SNAKE{

enum class CellType{
        EMPTY,
        OBSTACLE,
        FOOD,
        WALL,
        OCCUPIED,
    };


class Point{
    public:
    int x;
    int y;
    CellType type;
    bool operator==(const Point& p) const{
        return (x==p.x && y==p.y && type==p.type);
    }
    Point():x(0),y(0),type(CellType::EMPTY){};
    Point(int x, int y, CellType type):x(x),y(y),type(type){};
    Point(int x,int y):x(x),y(y),type(CellType::EMPTY){};
};
struct PointHash {
    std::size_t operator()(const Point & v) const {
        std::hash<int> hasher;
        std::size_t seed = 0;
        int i=v.x;
        seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        i=v.y;
        seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        i=int(v.type);
        seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        return seed;
    }
};
enum class Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE,
};
Direction opposite(Direction d);

Direction GetRandomDirection();
class BaseMap{
public:
    int size;
public:
    BaseMap():size(0){};
    BaseMap(int size):size(size){};
    virtual void init(){;};
    virtual void update(){;};
    virtual void initui(){;};
};

class GridMap: public BaseMap{
    private:
        std::vector<std::vector<CellType>> map;
        
        double grid_size;
        std::queue<std::pair<Point,CellType>> update_queue;
    public:
    int score;
        GridMap():BaseMap(),grid_size(0),score(0){;};
        
        GridMap(int size, double grid_size):BaseMap(size),grid_size(grid_size),score(0){
            map.resize(size);
            for(int i=0;i<size;i++){
                map[i].resize(size);
            }
        };
        void init();
        void update();
        void initui();
        GridMap(int size,double grid_size,std::unordered_set<Point,PointHash> obstacles):GridMap(size,grid_size){
            
            
            this->init();
            
            for (auto &it : obstacles){
                setCell(it.x,it.y,CellType::OBSTACLE);
            }
            
            this->update();
            
        }
        
        int capacity(){
            int ret=0;
            for (int i=0;i<size;i++){
                for (int j=0;j<size;j++){
                    if (map[i][j]==CellType::EMPTY)
                    ret++;
                }
            }
            return ret;
        }
        
        void reset(){
            init();
        };
        void setCell(int x, int y, CellType type);
        void setCellwoUpdate(int x, int y, CellType type){
            if (is_inrange(x,y))
            map[x][y]=type;
            
        }
        CellType getCell(int x, int y);
        int getSize();
        double getGridSize();
        void showMap(SNAKE::Point head1, SNAKE::Point head2, SNAKE::Direction dir1, SNAKE::Direction dir2) const;
        bool is_inrange(int x, int y){
            if (x < 0 || x >= size || y < 0 || y >= size)
            {
                return false;
            }
            return true;
        }
        bool is_valid(int x, int y)
        {
            if (x < 0 || x >= size || y < 0 || y >= size)
            {
                return false;
            }
            bool ret = ((this->getCell(x, y) != CellType::EMPTY) && (this->getCell(x, y) != CellType::FOOD));

            return !ret;
        }
        bool isfull(){
            for (int i=0;i<size;i++){
                for (int j=0;j<size;j++){
                    if (this->getCell(i,j)==CellType::EMPTY || this->getCell(i,j)==CellType::FOOD){
                        return false;
                    }
                }
            }
            return true;
        }


};

}
#endif