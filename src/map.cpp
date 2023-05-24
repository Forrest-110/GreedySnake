#include "map.hpp"
#include <iostream>
void SNAKE::GridMap::init(){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            map[i][j] = CellType::EMPTY;
        }
    }
}

void SNAKE::GridMap::update(){
    while(!update_queue.empty()){
        auto p = update_queue.front();
        update_queue.pop();
        map[p.first.x][p.first.y] = p.second;
    }
}

void SNAKE::GridMap::setCell(int x, int y, CellType type){
    update_queue.push(std::make_pair(Point{x,y,type},type));
}

SNAKE::CellType SNAKE::GridMap::getCell(int x, int y){
    return map[x][y];
}

int SNAKE::GridMap::getSize(){
    return size;
}

double SNAKE::GridMap::getGridSize(){
    return grid_size;
}

void SNAKE::GridMap::showMap() const{
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            std::cout << static_cast<int>(map[i][j]) << " ";
        }
        std::cout << std::endl;
    }
}