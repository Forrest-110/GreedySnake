#include "map.hpp"
using namespace SNAKE;
int main(){
    GridMap map(10,0.1);
    map.init();
    map.setCell(1,1,CellType::FOOD);
    map.showMap();
}