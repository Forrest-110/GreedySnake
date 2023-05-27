#pragma once
#ifndef _FOOD_HPP_
#define _FOOD_HPP_

#include "map.hpp"
#include <unordered_set>
namespace SNAKE{




class Food{
    private:
        GridMap* map;
        public:
        std::unordered_set<Point,PointHash> food_set;
    public:
        Food(GridMap* _map){
            this->map = _map;
            food_set.clear();
        };
        void setMap(GridMap* m){
            map=m;
        }
        bool generateFoodAtXY(int x, int y);
        bool generateFoodRandomly();
        bool generateNFoodRandomly(int n);
        bool removeFoodAtXY(int x, int y);
        bool removeFoodRandomly();
        bool removeNFoodRandomly(int n);
        void setFoodSetFromMap(){
            food_set.clear();
            for (int i=0;i<map->getSize();i++){
                for (int j=0;j<map->getSize();j++){
                    if (map->getCell(i,j)==CellType::Food){
                        food_set.insert(Point(i,j));
                    }
                }
            }
        }

};


}

#endif