#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <vector>
#include <queue>
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
};

class BaseMap{
private:
    int size;
public:
    BaseMap():size(0){};
    BaseMap(int size):size(size){};
    virtual void init(){;};
    virtual void update(){;};
};

class GridMap: public BaseMap{
    private:
        std::vector<std::vector<CellType>> map;
        int size;
        double grid_size;
        std::queue<std::pair<Point,CellType>> update_queue;
    public:
        GridMap():BaseMap(),size(0),grid_size(0){;};
        GridMap(int size, double grid_size):BaseMap(size),size(size),grid_size(grid_size){
            map.resize(size);
            for(int i=0;i<size;i++){
                map[i].resize(size);
            }
        };
        void init();
        void update();
        void reset(){
            init();
        };
        void setCell(int x, int y, CellType type);
        CellType getCell(int x, int y);
        int getSize();
        double getGridSize();
        void showMap() const;
};

}
#endif