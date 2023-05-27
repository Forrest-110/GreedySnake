#include "map.hpp"
#include <iostream>

SNAKE::Direction SNAKE::opposite(SNAKE::Direction d){
    switch(d){
        case Direction::UP:
            return Direction::DOWN;
        case Direction::DOWN:
            return Direction::UP;
        case Direction::LEFT:
            return Direction::RIGHT;
        case Direction::RIGHT:
            return Direction::LEFT;
        default:
            return Direction::NONE;
    }
}



void SNAKE::GridMap::init(){
    this->score = 0;
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
    if (!(x < 0 || x >= size || y < 0 || y >= size))
        return map[x][y];
    else{
        std::cout<<x<<","<<y<<" out of range"<<std::endl;
        // exit(0);
        return CellType::OBSTACLE;
    }
}

int SNAKE::GridMap::getSize(){
    
    return size;
}

double SNAKE::GridMap::getGridSize(){
    return grid_size;
}

void SNAKE::GridMap::showMap() const{
    // std::cout << "Score: " << score << std::endl;
    for(int y=0;y<size;y++){
        for(int x=0;x<size;x++){
            std::cout << static_cast<int>(map[x][y]) << " ";
        }
        std::cout << std::endl;
    }
}