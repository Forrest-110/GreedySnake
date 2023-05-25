#include "map.hpp"
#include <iostream>
void SNAKE::GridMap::init(){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if (i==0 || j==0 || i==size-1 || j==size-1)
                map[i][j] = CellType::WALL;
            else
                map[i][j] = CellType::EMPTY;
            // map[i][j] = CellType::EMPTY;
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
    for(int y=0;y<size;y++){
        for(int x=0;x<size;x++){
            std::cout << static_cast<int>(map[x][y]) << " ";
        }
        std::cout << std::endl;
    }
}