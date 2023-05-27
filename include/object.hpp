#pragma once
#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_
#include "map.hpp"
#include <unordered_set>
namespace SNAKE{

class Object{
    private:
        GridMap* map;
        std::unordered_set<Point,PointHash> object_set;
    public:
        Object(GridMap* _map){
            this->map = _map;
            object_set.clear();
        };
        bool generateObjectAtXY(int x, int y);
        bool generateObjectRandomly();
        bool generateNObjectRandomly(int n);
        bool removeObjectAtXY(int x, int y);
        bool removeObjectRandomly();
        bool removeNObjectRandomly(int n);
        bool isGoodObject();
        void filterObject();
        void setObjectSetFromMap(){
            object_set.clear();
            for (int i=0;i<map->getSize();i++){
                for (int j=0;j<map->getSize();j++){
                    if (map->getCell(i,j)==CellType::OBSTACLE){
                        object_set.insert(Point(i,j));
                    }
                }
            }
        }

};


}

#endif