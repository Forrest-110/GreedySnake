#ifndef _FOOD_HPP_
#define _FOOD_HPP_

#include "map.hpp"
#include <unordered_set>
namespace SNAKE{



class Food{
    private:
        GridMap* map;
        std::unordered_set<Point> food_set;
    public:
        Food(GridMap* _map){
            this->map = _map;
            food_set.clear();
        };
        bool generateFoodAtXY(int x, int y);
        bool generateFoodRandomly();
        bool generateNFoodRandomly(int n);
        bool removeFoodAtXY(int x, int y);
        bool removeFoodRandomly();
        bool removeNFoodRandomly(int n);


};


}

#endif